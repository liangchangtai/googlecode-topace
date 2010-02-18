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
#include "FBO.h"
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
CLoad3DS  * Test3dsModelHanger=NULL;
extern tGameSet GameSet;
int OmniLightNumBase=0;
int SpotLightNumBase=0;
void InitDraw()
{
	glewInit();
	WritePrivateProfileString("PC Info","Video Card",(char *)glGetString(GL_RENDERER),".\\gameset.ini");
	WritePrivateProfileString("PC Info","GL_VERSION",(char *)glGetString(GL_VERSION),".\\gameset.ini");
	//WritePrivateProfileString("PC Info","GL_EXTENSIONS",(char *)glGetString(GL_EXTENSIONS),".\\gameset.ini");
	if(GameSet.Light>1)
		InitFBO(GameSet.winW,GameSet.winH);
	InitGLSL(GameSet.Light);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glPolygonMode(GL_BACK,GL_LINE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0);
	GLfloat LightPos[]={0.0f,10000.0f,0.0f,0.0f};
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
		glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
		//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
		//glEnable(GL_LIGHT0);
	}
	if(!Test3dsModelHanger)
	{
		
		Test3dsModelHanger=new CLoad3DS;
		Test3dsModelHanger->Loadfile("data/model/hanger/Test3dsModelHanger.3DS");
		if(!Test3dsModelHanger->isRAM)
			MessageBox( NULL, "Cannot open data/model/hanger/Test3dsModelHanger.3DS!", "ERROR",MB_OK | MB_ICONEXCLAMATION );
		Test3dsModelHanger->LoadToVRAM();
		if(Test3dsModelHanger->Model3ds)
			maxFreme=float(Test3dsModelHanger->Model3ds->frames);
	}
	if(!Test3dsModelHanger->isVRAM)
	{
		Test3dsModelHanger->LoadToVRAM();
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
	if(Test3dsModelHanger)
	{
		Test3dsModelHanger->Del_VRAM();
	}

	if(Font2D)
	{
		delete Font2D;
		Font2D=NULL;
	}
}
void DeinitDraw()
{
	if(GameSet.Light>1)
		DeinitFBO();
	DeinitGLSL();
	if(Font2D)
	{
		delete Font2D;
		Font2D=NULL;
	}
	Inited=false;

}
void UnitMatrix()
{
	float NodesFrameIn[MAX_TYPE_3DS_NODE];
	NodesFrameIn[0]=Test3dsFrame;
	for(int i=1;i<MAX_TYPE_3DS_NODE;i++)
		NodesFrameIn[i]=Test3dsFrame;
	if(Test3dsModelHanger)
	if(Test3dsModelHanger->Model3ds)
	{
		Test3dsModelHanger->ModelMatrix(NodesFrameIn,Test3dsFrame);
	}
}
void SetCameraMatrix()
{
	glLoadIdentity();
	glTranslatef(moveX,moveY,-150-moveZ);
	glRotatef(angleR,0.0f,1.0f,0.0f);
	glRotatef(-90,1.0f,0.0f,0.0f);
	if(Test3dsModelHanger)
	if(Test3dsModelHanger->Model3ds)
	if(Test3dsModelHanger->Model3ds->ncameras>0)
	{
		glLoadIdentity();
		glTranslatef(moveX,moveY,-moveZ);
		glRotatef(-90,1.0f,0.0f,0.0f);
		Test3dsModelHanger->MultCameraMatrix();
	}

}
void SetLights()
{
	OmniLightNumBase=0;
	SpotLightNumBase=0;
	if(Test3dsModelHanger)
	if(Test3dsModelHanger->Model3ds)
	{
		Test3dsModelHanger->SetLightsPos(OmniLightNumBase+SpotLightNumBase);
		OmniLightNumBase+=Test3dsModelHanger->OmniLightNum;
		SpotLightNumBase+=Test3dsModelHanger->SpotLightNum;
	}
	if((OmniLightNumBase+SpotLightNumBase)==0)
	{
		OmniLightNumBase=1;
		float TMPLightColor[4]={0.5,0.5,0.5,1.0};
		float TMPLightPos[4]={0.0,0.0,3000.0,1.0};
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0,GL_POSITION,TMPLightPos);
		glLightfv(GL_LIGHT0,GL_SPECULAR,TMPLightColor);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,TMPLightColor);
		glLightfv(GL_LIGHT0,GL_AMBIENT,TMPLightColor);
	}
}
void RenderUnits(bool OnlySelfIllumUnit=false)
{
	if(Test3dsModelHanger)
	if(Test3dsModelHanger->isRAM)
	{
		Test3dsModelHanger->OnlySelfIllum=OnlySelfIllumUnit;
		Test3dsModelHanger->Render();
	}
}
void RenderSelfIllumUnits()
{
	//glTranslatef(0.0,0.0,2.0f);
	FBOS_Star_Begin();
	RenderUnits(true);
	FBOS_Star_End();
	TestTexFBO();
}
void DrawFPS(float oneframetimepointCPUSYS,float oneframetimepointGPU)
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
	glColor4f(1.0f,1.0f,0.0f,1.0f);
	glEnable( GL_TEXTURE_2D );
	Font2D->DrawTXT(GameSet.winW,GameSet.winH,0,0,24,24,GameSet.winW,3);
	glColor4f(1.0f,1.0f,1.0f,1.0f);
}
void Draw(float oneframetimepointCPUSYS,float oneframetimepointGPU)
{
	QueryPerformanceCounter(&CPUTestStart);
	UnitMatrix();
	SetCameraMatrix();
	SetLights();
	Test_matrix();
	QueryPerformanceCounter(&CPUTestEnd);

	if(domultiR)
		glEnable(GL_MULTISAMPLE_ARB);

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(GameSet.Light==1)
		glEnable(GL_LIGHTING);

	GLSL_Enable_PhoneLight(OmniLightNumBase,SpotLightNumBase);
	RenderUnits();
	GLSL_Disable();

	if(GameSet.Light==1)
		glDisable(GL_LIGHTING);

	RenderSelfIllumUnits();

	DrawFPS(oneframetimepointCPUSYS, oneframetimepointGPU);

	if(domultiR)
		glDisable(GL_MULTISAMPLE_ARB);

	
}
