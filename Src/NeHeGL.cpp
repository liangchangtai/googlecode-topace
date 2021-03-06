/***********************************************
*                                              *
*    Jeff Molofee's Revised OpenGL Basecode    *
*  Huge Thanks To Maxwell Sayles & Peter Puck  *
*            http://nehe.gamedev.net           *
*                     2001                     *
*                                              *
***********************************************/

#include <direct.h>
#include <windows.h>													// Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include <stdio.h>	
#include <math.h>	
#include "NeHeGL.h"														// Header File For The NeHeGL Basecode
#include "ARB_MULTISAMPLE.h"

BOOL DestroyWindowGL (GL_Window* window);
BOOL CreateWindowGL (GL_Window* window);
#define WM_TOGGLEFULLSCREEN (WM_USER+1)									// Application Define Message For Toggling

static BOOL g_isProgramLooping;											// Window Creation Loop, For FullScreen/Windowed Toggle																		// Between Fullscreen / Windowed Mode
static BOOL g_createFullScreen;											// If TRUE, Then Create Fullscreen
int windowswidth=800;
int windowsheight=600;
int windowsbits=16;
bool BisFullScreen=FALSE;
int ACver=36;
int (__stdcall *hglSwapBuffers)(void *);
HMODULE gl_dll=false;

void TerminateApplication (GL_Window* window)							// Terminate The Application
{
	PostMessage (window->hWnd, WM_QUIT, 0, 0);							// Send A WM_QUIT Message
	g_isProgramLooping = FALSE;											// Stop Looping Of The Program
}

void ToggleFullscreen (GL_Window* window)								// Toggle Fullscreen/Windowed
{
	PostMessage (window->hWnd, WM_TOGGLEFULLSCREEN, 0, 0);				// Send A WM_TOGGLEFULLSCREEN Message
}

void ReshapeGL (int width, int height)									// Reshape The Window When It's Moved Or Resized
{
	winwidth=width;
	winheight=height;
	glViewport (0, 0, (GLsizei)(width), (GLsizei)(height));				// Reset The Current Viewport
	glMatrixMode (GL_PROJECTION);										// Select The Projection Matrix
	glLoadIdentity ();													// Reset The Projection Matrix
	gluPerspective (60.0f, (GLfloat)(width)/(GLfloat)(height),			// Calculate The Aspect Ratio Of The Window
					10.0f, 100000.0f);		
	glMatrixMode (GL_MODELVIEW);										// Select The Modelview Matrix
	glLoadIdentity ();													// Reset The Modelview Matrix
}

BOOL ChangeScreenResolution (int width, int height, int bitsPerPixel)	// Change The Screen Resolution
{
	DEVMODE dmScreenSettings;											// Device Mode
	ZeroMemory (&dmScreenSettings, sizeof (DEVMODE));					// Make Sure Memory Is Cleared
	dmScreenSettings.dmSize				= sizeof (DEVMODE);				// Size Of The Devmode Structure
	dmScreenSettings.dmPelsWidth		= width;						// Select Screen Width
	dmScreenSettings.dmPelsHeight		= height;						// Select Screen Height
	dmScreenSettings.dmBitsPerPel		= bitsPerPixel;					// Select Bits Per Pixel
	dmScreenSettings.dmFields			= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	if (ChangeDisplaySettings (&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		return FALSE;													// Display Change Failed, Return False
	}
	return TRUE;														// Display Change Was Successful, Return True
}

BOOL CreateWindowGL (GL_Window* window)									// This Code Creates Our OpenGL Window
{
	//DWORD windowStyle = WS_OVERLAPPEDWINDOW;							// Define Our Window Style
	//DWORD windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ;
	DWORD windowStyle =WS_POPUP;
	DWORD windowExtendedStyle = WS_EX_APPWINDOW;						// Define The Window's Extended Style

	PIXELFORMATDESCRIPTOR pfd =											// pfd Tells Windows How We Want Things To Be
	{
		sizeof (PIXELFORMATDESCRIPTOR),									// Size Of This Pixel Format Descriptor
		1,																// Version Number
		PFD_DRAW_TO_WINDOW |											// Format Must Support Window
		PFD_SUPPORT_OPENGL |											// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,												// Must Support Double Buffering
		PFD_TYPE_RGBA,													// Request An RGBA Format
		window->init.bitsPerPixel,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,												// Color Bits Ignored
		0,																// No Alpha Buffer
		0,																// Shift Bit Ignored
		0,																// No Accumulation Buffer
		0, 0, 0, 0,														// Accumulation Bits Ignored
		16,																// 16Bit Z-Buffer (Depth Buffer)  
		0,																// No Stencil Buffer
		0,																// No Auxiliary Buffer
		PFD_MAIN_PLANE,													// Main Drawing Layer
		0,																// Reserved
		0, 0, 0															// Layer Masks Ignored
	};

	RECT windowRect = {0, 0, window->init.width, window->init.height};	// Define Our Window Coordinates

	GLuint PixelFormat;													// Will Hold The Selected Pixel Format

	if (window->init.isFullScreen == TRUE)								// Fullscreen Requested, Try Changing Video Modes
	{
		if (ChangeScreenResolution (window->init.width, window->init.height, window->init.bitsPerPixel) == FALSE)
		{
			// Fullscreen Mode Failed.  Run In Windowed Mode Instead
			MessageBox (HWND_DESKTOP, "Mode Switch Failed.\nRunning In Windowed Mode.", "Error", MB_OK | MB_ICONEXCLAMATION);
			window->init.isFullScreen = FALSE;							// Set isFullscreen To False (Windowed Mode)
		}
		else															// Otherwise (If Fullscreen Mode Was Successful)
		{
			ShowCursor (FALSE);											// Turn Off The Cursor
			windowStyle = WS_POPUP;										// Set The WindowStyle To WS_POPUP (Popup Window)
			windowExtendedStyle |= WS_EX_TOPMOST;						// Set The Extended Window Style To WS_EX_TOPMOST
		}																// (Top Window Covering Everything Else)
	}
	else																// If Fullscreen Was Not Selected
	{
		// Adjust Window, Account For Window Borders
		AdjustWindowRectEx (&windowRect, windowStyle, 0, windowExtendedStyle);
	}
#ifdef _RELEASELOG 
	WritePrivateProfileString("CreateWindowGL","AdjustWindowRectEx","OK",".\\Log.ini");
#endif
	// Create The OpenGL Window
	if(BisFullScreen)
	{
		window->hWnd = CreateWindowEx (windowExtendedStyle,					// Extended Style
									   window->init.application->className,	// Class Name
									   window->init.title,					// Window Title
									   windowStyle,							// Window Style
									   0, 0,								// Window X,Y Position
									   windowRect.right - windowRect.left,	// Window Width
									   windowRect.bottom - windowRect.top,	// Window Height
									   HWND_DESKTOP,						// Desktop Is Window's Parent
									   0,									// No Menu
									   window->init.application->hInstance, // Pass The Window Instance
									   window);
	}
	else
	{
		window->hWnd = CreateWindowEx (windowExtendedStyle,					// Extended Style
									   window->init.application->className,	// Class Name
									   window->init.title,					// Window Title
									   windowStyle,							// Window Style
									   (GetSystemMetrics(SM_CXFULLSCREEN)-(windowRect.right - windowRect.left))/2, 
									   (GetSystemMetrics(SM_CYFULLSCREEN)-(windowRect.bottom - windowRect.top))/2,								// Window X,Y Position
									   windowRect.right - windowRect.left,	// Window Width
									   windowRect.bottom - windowRect.top,	// Window Height
									   HWND_DESKTOP,						// Desktop Is Window's Parent
									   0,									// No Menu
									   window->init.application->hInstance, // Pass The Window Instance
									   window);
	}
#ifdef _RELEASELOG 
	WritePrivateProfileString("CreateWindowGL","CreateWindowEx","OK",".\\Log.ini");
#endif
	if (window->hWnd == 0)												// Was Window Creation A Success?
	{
		return FALSE;													// If Not Return False
	}

	window->hDC = GetDC (window->hWnd);									// Grab A Device Context For This Window
	if (window->hDC == 0)												// Did We Get A Device Context?
	{
		// Failed
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}
#ifdef _RELEASELOG 
	WritePrivateProfileString("CreateWindowGL","GetDC","OK",".\\Log.ini");
#endif
//ROACH
	/*
	Our first pass, Multisampling hasn't been created yet, so we create a window normally
	If it is supported, then we're on our second pass
	that means we want to use our pixel format for sampling
	so set PixelFormat to arbMultiSampleformat instead
  */
	if(!arbMultisampleSupported)
	{
		PixelFormat = ChoosePixelFormat (window->hDC, &pfd);				// Find A Compatible Pixel Format
		if (PixelFormat == 0)												// Did We Find A Compatible Format?
		{
			// Failed
			ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
			window->hDC = 0;												// Zero The Device Context
			DestroyWindow (window->hWnd);									// Destroy The Window
			window->hWnd = 0;												// Zero The Window Handle
			return FALSE;													// Return False
		}

	}
	else
	{
		PixelFormat = arbMultisampleFormat;
	}
#ifdef _RELEASELOG 
	WritePrivateProfileString("CreateWindowGL","arbMultisampleSupported","OK",".\\Log.ini");
#endif
//ENDROACH
	if (SetPixelFormat (window->hDC, PixelFormat, &pfd) == FALSE)		// Try To Set The Pixel Format
	{
		// Failed
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}
#ifdef _RELEASELOG 
	WritePrivateProfileString("CreateWindowGL","SetPixelFormat","OK",".\\Log.ini");
#endif
	window->hRC = wglCreateContext (window->hDC);						// Try To Get A Rendering Context
	if (window->hRC == 0)												// Did We Get A Rendering Context?
	{
		// Failed
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}
#ifdef _RELEASELOG 
	WritePrivateProfileString("CreateWindowGL","wglCreateContext","OK",".\\Log.ini");
#endif
	// Make The Rendering Context Our Current Rendering Context
	if (wglMakeCurrent (window->hDC, window->hRC) == FALSE)
	{
		// Failed
		wglDeleteContext (window->hRC);									// Delete The Rendering Context
		window->hRC = 0;												// Zero The Rendering Context
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}
#ifdef _RELEASELOG 
	WritePrivateProfileString("CreateWindowGL","wglMakeCurrent","OK",".\\Log.ini");
#endif
//ROACH
	/*
	Now that our window is created, we want to queary what samples are available
	we call our InitMultiSample window
	if we return a valid context, we want to destroy our current window
	and create a new one using the multisample interface.
	*/
	if(!arbMultisampleSupported && CHECK_FOR_MULTISAMPLE)
	{
	
		if(InitMultisample(window->init.application->hInstance,window->hWnd,pfd))
		{
			
			DestroyWindowGL (window);
			return CreateWindowGL(window);
		}
	}
#ifdef _RELEASELOG 
	WritePrivateProfileString("CreateWindowGL","InitMultisample","OK",".\\Log.ini");
#endif
//ENDROACH
	ShowWindow (window->hWnd, SW_NORMAL);								// Make The Window Visible
	window->isVisible = TRUE;											// Set isVisible To True
#ifdef _RELEASELOG 
	WritePrivateProfileString("CreateWindowGL","ShowWindow","OK",".\\Log.ini");
#endif
	ReshapeGL (window->init.width, window->init.height);				// Reshape Our GL Window
#ifdef _RELEASELOG 
	WritePrivateProfileString("CreateWindowGL","ReshapeGL","OK",".\\Log.ini");
#endif
	ZeroMemory (window->keys, sizeof (Keys));							// Clear All Keys

	window->lastTickCount = GetTickCount ();							// Get Tick Count

	return TRUE;														// Window Creating Was A Success
																		// Initialization Will Be Done In WM_CREATE
}

BOOL DestroyWindowGL (GL_Window* window)								// Destroy The OpenGL Window & Release Resources
{
	if (window->hWnd != 0)												// Does The Window Have A Handle?
	{	
		if (window->hDC != 0)											// Does The Window Have A Device Context?
		{
			wglMakeCurrent (window->hDC, 0);							// Set The Current Active Rendering Context To Zero
			if (window->hRC != 0)										// Does The Window Have A Rendering Context?
			{
				wglDeleteContext (window->hRC);							// Release The Rendering Context
				window->hRC = 0;										// Zero The Rendering Context

			}
			ReleaseDC (window->hWnd, window->hDC);						// Release The Device Context
			window->hDC = 0;											// Zero The Device Context
		}
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
	}

	if (window->init.isFullScreen)										// Is Window In Fullscreen Mode
	{
		ChangeDisplaySettings (NULL,0);									// Switch Back To Desktop Resolution
		ShowCursor (TRUE);												// Show The Cursor
	}	
	return TRUE;														// Return True
}

// Process Window Message Callbacks
LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Get The Window Context
	GL_Window* window = (GL_Window*)(GetWindowLong (hWnd, GWL_USERDATA));

	switch (uMsg)														// Evaluate Window Message
	{
		case WM_ERASEBKGND:								// ���Windows�Ƿ�ȥ��������
			return 0;	
		case WM_SYSCOMMAND:												// Intercept System Commands
		{
			switch (wParam)												// Check System Calls
			{
				case SC_SCREENSAVE:										// Screensaver Trying To Start?
				case SC_MONITORPOWER:									// Monitor Trying To Enter Powersave?
				return 0;												// Prevent From Happening
			}
			break;														// Exit
		}
		return 0;														// Return

		case WM_CREATE:													// Window Creation
		{
			CREATESTRUCT* creation = (CREATESTRUCT*)(lParam);			// Store Window Structure Pointer
			window = (GL_Window*)(creation->lpCreateParams);
			SetWindowLong (hWnd, GWL_USERDATA, (LONG)(window));
		}
		return 0;														// Return

		case WM_CLOSE:													// Closing The Window
			TerminateApplication(window);								// Terminate The Application
		return 0;														// Return

		case WM_SIZE:													// Size Action Has Taken Place
			switch (wParam)												// Evaluate Size Action
			{
				case SIZE_MINIMIZED:									// Was Window Minimized?
					window->isVisible = FALSE;							// Set isVisible To False
				return 0;												// Return

				case SIZE_MAXIMIZED:									// Was Window Maximized?
					window->isVisible = TRUE;							// Set isVisible To True
					ReshapeGL (LOWORD (lParam), HIWORD (lParam));		// Reshape Window - LoWord=Width, HiWord=Height
				return 0;												// Return

				case SIZE_RESTORED:										// Was Window Restored?
					window->isVisible = TRUE;							// Set isVisible To True
					ReshapeGL (LOWORD (lParam), HIWORD (lParam));		// Reshape Window - LoWord=Width, HiWord=Height
				return 0;												// Return
			}
		break;															// Break

		case WM_KEYDOWN:												// Update Keyboard Buffers For Keys Pressed
			if ((wParam >= 0) && (wParam <= 255))						// Is Key (wParam) In A Valid Range?
			{
				window->keys->keyDown [wParam] = TRUE;					// Set The Selected Key (wParam) To True
				return 0;												// Return
			}
		break;															// Break

		case WM_KEYUP:													// Update Keyboard Buffers For Keys Released
			if ((wParam >= 0) && (wParam <= 255))						// Is Key (wParam) In A Valid Range?
			{
				isKeyDown=true;
				window->keys->keyDown [wParam] = FALSE;					// Set The Selected Key (wParam) To False
				return 0;												// Return
			}
		break;															// Break

		case WM_TOGGLEFULLSCREEN:										// Toggle FullScreen Mode On/Off
			g_createFullScreen = (g_createFullScreen == TRUE) ? FALSE : TRUE;
			PostMessage (hWnd, WM_QUIT, 0, 0);
		break;															// Break

	}

	return DefWindowProc (hWnd, uMsg, wParam, lParam);					// Pass Unhandled Messages To DefWindowProc
}

BOOL RegisterWindowClass (Application* application)						// Register A Window Class For This Application.
{																		// TRUE If Successful
	// Register A Window Class
	WNDCLASSEX windowClass;												// Window Class
	ZeroMemory (&windowClass, sizeof (WNDCLASSEX));						// Make Sure Memory Is Cleared
	windowClass.cbSize			= sizeof (WNDCLASSEX);					// Size Of The windowClass Structure
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraws The Window For Any Movement / Resizing
	windowClass.lpfnWndProc		= (WNDPROC)(WindowProc);				// WindowProc Handles Messages
	windowClass.hInstance		= application->hInstance;				// Set The Instance
	windowClass.hbrBackground	= (HBRUSH)(COLOR_APPWORKSPACE);			// Class Background Brush Color
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	windowClass.lpszClassName	= application->className;				// Sets The Applications Classname
	windowClass.hIcon			= LoadIcon(NULL,"101");
	if (RegisterClassEx (&windowClass) == 0)							// Did Registering The Class Fail?
	{
		// NOTE: Failure, Should Never Happen
		MessageBox (HWND_DESKTOP, "RegisterClassEx Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;													// Return False (Failure)
	}
	return TRUE;														// Return True (Success)
}

// Program Entry (WinMain)
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    char path[_MAX_PATH];
    GetModuleFileName(hInstance, path, _MAX_PATH);
    for (int i = strlen(path) - 1; i >= 0; i -= 1){
        if (path[i] != '\\' && path[i] != '/'){
            path[i] = 0;
        }
        else{
            break;
        }
    }
    chdir(path);

	Application			application;									// Application Structure
	GL_Window			window;											// Window Structure
	Keys				keys;											// Key Structure
	BOOL				isMessagePumpActive;							// Message Pump Active?
	MSG					msg;											// Window Message Structure
	DWORD				tickCount;										// Used For The Tick Counter

	char szWINtile[128];
	sprintf(szWINtile,"TOP ACE testV%d by babywolf & oz01 & hellgate & neo the one",ACver);
	// Fill Out Application Data
	application.className = "OpenGL";									// Application Class Name
	application.hInstance = hInstance;									// Application Instance

 
	inifile ();
	// Fill Out Window
	ZeroMemory (&window, sizeof (GL_Window));							// Make Sure Memory Is Zeroed
	window.keys					= &keys;								// Window Key Structure
	window.init.application		= &application;							// Window Application
	window.init.title			= szWINtile;	// Window Title
	window.init.width			= windowswidth;									// Window Width
	window.init.height			= windowsheight;									// Window Height
	window.init.bitsPerPixel	= windowsbits;									// Bits Per Pixel
	window.init.isFullScreen	= BisFullScreen;									// Fullscreen? (Set To TRUE)

	ZeroMemory (&keys, sizeof (Keys));									// Zero keys Structure

	// Ask The User If They Want To Start In FullScreen Mode?
	//if (MessageBox (HWND_DESKTOP, "Would You Like To Run In Fullscreen Mode?", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	//{
		//window.init.isFullScreen = FALSE;								// If Not, Run In Windowed Mode
	//}

	// Register A Class For Our Window To Use
	if (RegisterWindowClass (&application) == FALSE)					// Did Registering A Class Fail?
	{
		// Failure
		MessageBox (HWND_DESKTOP, "Error Registering Window Class!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return -1;														// Terminate Application
	}
	if(!gl_dll)
	{
		gl_dll=LoadLibrary("OpenGL32.DLL");

		if(!gl_dll)
			MessageBox (HWND_DESKTOP, "Error Get OpenGL32.DLL!", "Error", MB_OK | MB_ICONEXCLAMATION);

	}

	hglSwapBuffers=(int (__stdcall *)(void *))GetProcAddress(gl_dll,"wglSwapBuffers");

	g_isProgramLooping = TRUE;											// Program Looping Is Set To TRUE
	g_createFullScreen = window.init.isFullScreen;						// g_createFullScreen Is Set To User Default
	while (g_isProgramLooping)											// Loop Until WM_QUIT Is Received
	{
		// Create A Window
		window.init.isFullScreen = g_createFullScreen;					// Set Init Param Of Window Creation To Fullscreen?
#ifdef _RELEASELOG 
				WritePrivateProfileString("CreateWindowGL","Begin","OK",".\\Log.ini");
#endif
		if (CreateWindowGL (&window) == TRUE)							// Was Window Creation Successful?
		{
			// At This Point We Should Have A Window That Is Setup To Render OpenGL
			if (Initialize (&window, &keys) == FALSE)					// Call User Intialization
			{
#ifdef _RELEASELOG 
				WritePrivateProfileString("Initialize","Initialize","False",".\\Log.ini");
#endif
				// Failure
				TerminateApplication (&window);							// Close Window, This Will Handle The Shutdown
			}
			else														// Otherwise (Start The Message Pump)
			{	// Initialize was a success
#ifdef _RELEASELOG 
				WritePrivateProfileString("ALLInit","ALLInit","OK",".\\Log.ini");
#endif
				isMessagePumpActive = TRUE;								// Set isMessagePumpActive To TRUE
				while (isMessagePumpActive == TRUE)						// While The Message Pump Is Active
				{
					// Success Creating Window.  Check For Window Messages
					if (PeekMessage (&msg, window.hWnd, 0, 0, PM_REMOVE) != 0)
					{
						// Check For WM_QUIT Message
						if (msg.message != WM_QUIT)						// Is The Message A WM_QUIT Message?
						{
							DispatchMessage (&msg);						// If Not, Dispatch The Message
						}
						else											// Otherwise (If Message Is WM_QUIT)
						{
							isMessagePumpActive = FALSE;				// Terminate The Message Pump
						}
					}
					else												// If There Are No Messages
					{
						if (window.isVisible == FALSE)					// If Window Is Not Visible
						{
							WaitMessage ();								// Application Is Minimized Wait For A Message
						}
						else											// If Window Is Visible
						{
							// Process Application Loop
							tickCount = GetTickCount ();				// Get The Tick Count
							Update (tickCount - window.lastTickCount);	// Update The Counter
							window.lastTickCount = tickCount;			// Set Last Count To Current Count
							Draw ();									// Draw Our Scene
							if(!IsSkip)
							hglSwapBuffers (window.hDC);					// Swap Buffers (Double Buffering)
							isKeyDown=false;
						}
					}
				}														// Loop While isMessagePumpActive == TRUE
			}															// If (Initialize (...

			// Application Is Finished
			Deinitialize ();											// User Defined DeInitialization

			DestroyWindowGL (&window);									// Destroy The Active Window
		}
		else															// If Window Creation Failed
		{
			// Error Creating Window
			MessageBox (HWND_DESKTOP, "Error Creating OpenGL Window", "Error", MB_OK | MB_ICONEXCLAMATION);
			g_isProgramLooping = FALSE;									// Terminate The Loop
		}
	}																	// While (isProgramLooping)

	UnregisterClass (application.className, application.hInstance);		// UnRegister Window Class
	return 0;
}																		// End Of WinMain()


bool inifile ()
{
	FILE *File=NULL;

	File=fopen(".\\set.ini","r");							// Check To See If The File Exists
	char szVer[16];
	sprintf(szVer,"%d",ACver);
	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The HandleisFullScreenBisFullScreen

		WritePrivateProfileString("ACver","ACver",szVer,".\\set.ini");
		windowswidth=GetPrivateProfileInt("Resolution","width",800,".\\set.ini");
		windowsheight=GetPrivateProfileInt("Resolution","height",600,".\\set.ini");
		windowsbits=GetPrivateProfileInt("Resolution","bits",16,".\\set.ini");
		winwidth=windowswidth;
		winheight=windowsheight;
		if(0==GetPrivateProfileInt("Resolution","isFullScreen",0,".\\set.ini"))
			BisFullScreen= false;
		else
			BisFullScreen= true;

		return true;				// Load The Bitmap And Return A Pointer
	}
	else
	{
		
		WritePrivateProfileString("ACver","ACver",szVer,".\\set.ini");
		WritePrivateProfileString("Resolution","width","800",".\\set.ini");
		WritePrivateProfileString("Resolution","height","600",".\\set.ini");
		WritePrivateProfileString("Resolution","bits","16",".\\set.ini");
		WritePrivateProfileString("Resolution","isFullScreen","0",".\\set.ini");
		WritePrivateProfileString("Resolution","FrameSkip","0",".\\set.ini");
		WritePrivateProfileString("Resolution","AA","0",".\\set.ini");
		WritePrivateProfileString("FlySet","moveSpeed","100",".\\set.ini");
		WritePrivateProfileString("FlySet","MAXSpeed","500",".\\set.ini");
		WritePrivateProfileString("FlySet","MINSpeed","1",".\\set.ini");
		WritePrivateProfileString("FlySet","Acceleration","1",".\\set.ini");
		WritePrivateProfileString("FlySet","SpeedShowPercentage","30000",".\\set.ini");
		WritePrivateProfileString("FlySet","TurnRateX","50",".\\set.ini");
		WritePrivateProfileString("FlySet","TurnRateY","500",".\\set.ini");
		WritePrivateProfileString("FlySet","TurnRateZ","50",".\\set.ini");
		WritePrivateProfileString("Fog","glClearColorR","201",".\\set.ini");
		WritePrivateProfileString("Fog","glClearColorG","207",".\\set.ini");
		WritePrivateProfileString("Fog","glClearColorB","210",".\\set.ini");
		WritePrivateProfileString("Fog","glClearColorA","255",".\\set.ini");
		WritePrivateProfileString("Fog","fogColorR","184",".\\set.ini");
		WritePrivateProfileString("Fog","fogColorG","187",".\\set.ini");
		WritePrivateProfileString("Fog","fogColorB","210",".\\set.ini");
		WritePrivateProfileString("Fog","fogColorA","255",".\\set.ini");
		WritePrivateProfileString("Fog","fogDENSITY","90",".\\set.ini");
		WritePrivateProfileString("Fog","Fog_Far","100000",".\\set.ini");
		WritePrivateProfileString("Fog","Fog_Near","60000",".\\set.ini");
		WritePrivateProfileString("Light","LightAmbientR","150",".\\set.ini");
		WritePrivateProfileString("Light","LightAmbientG","150",".\\set.ini");
		WritePrivateProfileString("Light","LightAmbientB","150",".\\set.ini");
		WritePrivateProfileString("Light","LightAmbientA","255",".\\set.ini");
		WritePrivateProfileString("Light","LightDiffuseR","106",".\\set.ini");
		WritePrivateProfileString("Light","LightDiffuseG","106",".\\set.ini");
		WritePrivateProfileString("Light","LightDiffuseB","106",".\\set.ini");
		WritePrivateProfileString("Light","LightDiffuseA","255",".\\set.ini");
		WritePrivateProfileString("Light","Use_openGL_Light","0",".\\set.ini");
		WritePrivateProfileString("Light","ShaderWater","1",".\\set.ini");
		WritePrivateProfileString("Light","Use_Bloom","0",".\\set.ini");
		WritePrivateProfileString("Light","BloomLevel","0",".\\set.ini");
		WritePrivateProfileString("Light","Shadow","4",".\\set.ini");
		//WritePrivateProfileString("Joke","GL_TEXTURE_GEN_S","0",".\\set.ini");
		//WritePrivateProfileString("Joke","GL_TEXTURE_GEN_T","0",".\\set.ini");
		WritePrivateProfileString("Effect","MoveBlur","1",".\\set.ini");
		WritePrivateProfileString("Effect","Cloud","1",".\\set.ini");
		WritePrivateProfileString("Graphics","LOW","0",".\\set.ini");
		WritePrivateProfileString("UI","SmallWindowSet","0",".\\set.ini");
		WritePrivateProfileString("Sound","Effect","100",".\\set.ini");
		WritePrivateProfileString("Sound","Voice","100",".\\set.ini");
		WritePrivateProfileString("Sound","BGM","50",".\\set.ini");

											// Close The Handle
		//fclose(File);
		return true;
	}

	return false;	
}