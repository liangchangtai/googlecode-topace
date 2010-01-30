#include"Draw.h"
#include <stdlib.h>
#include <GL/glew.h>
#include <math.h>
#include <stdio.h>	
#include "Glsl.h"
#include <lib3ds.h>
#include <string.h>	
#include "Load3DS.h"
#include "Font2D.h"
#include "Textures.h"
#include"IniFile.h"
bool extern domultiR ;
bool extern doangleR ;
float extern angleR;
float extern Test3dsFrame;
float extern maxFreme;
float extern moveZ;
float extern moveY;
float extern moveX;
CFont2D * Font2D=NULL; 
bool Inited=false;
bool IsFirstInit=true;
LARGE_INTEGER TimeStart,TimeEnd,Timefeq,RunTimeStart,RunTimeEnd,CPUTestStart,CPUTestEnd;
int FPSNum=0;
int FPSNumShow=0; 
wchar_t ShowFPS[64]={0};
CLoad3DS  * Test3DSModel=NULL;
extern tGameSet GameSet;
void InitDraw()
{
	glewInit();
	WritePrivateProfileString("PC Info","Video Card",(char *)glGetString(GL_RENDERER),".\\gameset.ini");
	WritePrivateProfileString("PC Info","GL_VERSION",(char *)glGetString(GL_VERSION),".\\gameset.ini");
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glPolygonMode(GL_BACK,GL_LINE);
	glClearColor(0.0f, 0.5f, 0.5f, 0.5);
	GLfloat LightPos[]={1000.0f,0.0f,10000.0f,0.0f};
	glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
	GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat mat_ambient[]={0.3f,0.3f,0.3f,1.0f};
	GLfloat mat_diffuse[]={0.7f,0.7f,0.7f,1.0f};
	GLfloat mat_shininess[]={100.0f};
	glLightfv(GL_LIGHT0,GL_SPECULAR,mat_specular);
	glLightfv(GL_LIGHT0,GL_AMBIENT,mat_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,mat_diffuse);
	glLightfv(GL_LIGHT0,GL_SHININESS,mat_shininess);

	if(GameSet.Light==1)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	if(!Test3DSModel)
	{
		
		Test3DSModel=new CLoad3DS;
		Test3DSModel->Loadfile("data/model/test/Test3dsModel.3DS");
		Test3DSModel->LoadToVRAM();
		maxFreme=float(Test3DSModel->Model3ds->frames);
	}
	if(!Test3DSModel->isVRAM)
	{
		Test3DSModel->LoadToVRAM();
	}

	if(!Font2D)
	{
		char szPath[MAX_PATH];
		GetWindowsDirectory(szPath,sizeof(szPath));
		char FontPath[MAX_PATH];
		sprintf(FontPath,"%s/Fonts/simsun.ttc",szPath);
		Font2D=new CFont2D;
		Font2D->LoadFont(FontPath,32,32,256,256);
	}
	swprintf_s(ShowFPS,64,L"-");
	QueryPerformanceCounter(&TimeStart);
	if(IsFirstInit)
	{
		QueryPerformanceCounter(&RunTimeStart);
		IsFirstInit=false;
	}
	QueryPerformanceFrequency(&Timefeq);

}
void ClearVRAM()
{
	if(Test3DSModel)
	{
		Test3DSModel->Del_VRAM();
	}

	if(Font2D)
	{
		delete Font2D;
		Font2D=NULL;
	}
}
void DeinitDraw()
{
	if(Font2D)
	{
		delete Font2D;
		Font2D=NULL;
	}
	Inited=false;

}
void Draw(float oneframetimepointCPUSYS,float oneframetimepointGPU)
{
	float oneframetimepointCPUDraw=0.0f;
	oneframetimepointCPUDraw=(float(CPUTestEnd.QuadPart-CPUTestStart.QuadPart)/float(Timefeq.QuadPart));
	if(GameSet.FPS>0)
		oneframetimepointCPUDraw=100.0f*oneframetimepointCPUDraw/(1.0f/float(GameSet.FPS));
	else
		oneframetimepointCPUDraw=100.0f;
	QueryPerformanceFrequency(&Timefeq);
	QueryPerformanceCounter(&TimeEnd);
	QueryPerformanceCounter(&RunTimeEnd);
	float runtime;
	if((double(TimeEnd.QuadPart-TimeStart.QuadPart)/double(Timefeq.QuadPart))>=1.0)
	{
		QueryPerformanceCounter(&TimeStart);
		FPSNumShow=FPSNum;
		FPSNum=0;
		runtime=float((RunTimeEnd.QuadPart-RunTimeStart.QuadPart)/Timefeq.QuadPart);
		swprintf_s(ShowFPS,64,L"FPS:%d, CPU:%3.3f%%, CPUDraw:%3.3f%%, GPU:%3.3f%%",FPSNumShow,oneframetimepointCPUSYS,oneframetimepointCPUDraw,oneframetimepointGPU);
		Font2D->inputTxt(ShowFPS);
	}
	FPSNum=FPSNum+1;


	// ROACH
	if(domultiR)
		glEnable(GL_MULTISAMPLE_ARB);							// Enable Our Multisampling
	// ENDROACH
					// Set The Clear Color To Black
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity();											// Reset The View	

	glTranslatef(moveX,moveY,-150-moveZ);
	glRotatef(angleR,0.0f,1.0f,0.0f);
	glRotatef(-90,1.0f,0.0f,0.0f);

	float NodesFrameIn[MAX_TYPE_3DS_NODE];
	NodesFrameIn[0]=Test3dsFrame;
	for(int i=1;i<MAX_TYPE_3DS_NODE;i++)
		NodesFrameIn[i]=Test3dsFrame;

	if(Test3DSModel)
	{
		
		QueryPerformanceCounter(&CPUTestStart);
		Test3DSModel->ModelMatrix(NodesFrameIn,Test3dsFrame);
		if(Test3DSModel->Model3ds->ncameras>0)
		{
			glLoadIdentity();
			glTranslatef(moveX,moveY,-moveZ);
			glRotatef(-90,1.0f,0.0f,0.0f);
			Test3DSModel->MultCameraMatrix();
		}
		
		QueryPerformanceCounter(&CPUTestEnd);
		//Test3DSModel->RenderNoColor();
		Test3DSModel->Render();
	}

	glEnable( GL_TEXTURE_2D );
	Font2D->DrawTXT(800,600,0,0,24,24,800,3);

	if(domultiR)
	glDisable(GL_MULTISAMPLE_ARB);

}
