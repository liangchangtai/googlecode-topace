#include "GLSLLoader.h"

#include <stdio.h>	
#include <windows.h>
#include "FileSysBace.h"

CGLSLLoader::CGLSLLoader(void)
{
	GLSL_Shader_Obj.g_VS=0;
	GLSL_Shader_Obj.g_PS=0;
	GLSL_Shader_Obj.g_PO=0;
}


CGLSLLoader::~CGLSLLoader(void)
{
	ClearShader();
	GLSLLOG.ClearLOG();
}

char * CGLSLLoader::GetGLSLInfoLog(GLhandleARB GLSLShaderObject)
{
	int logreadsize=0;
	int logbuffersize=0x800;
	char * logbuffer=new char [logbuffersize];
	glGetInfoLogARB(GLSLShaderObject, logbuffersize,&logreadsize, logbuffer);
	while(logbuffersize<=logreadsize)
	{
		logbuffersize=logbuffersize*2;
		delete[] logbuffer;
		if(logbuffersize>0x10000)
			break;
		logbuffer=new char [logbuffersize];
		glGetInfoLogARB(GLSLShaderObject, logbuffersize,&logreadsize, logbuffer);
	}
	return logbuffer;
}
GLhandleARB CGLSLLoader::CompileShader(const wchar_t* shaderfilename,GLenum ShaderObject)
{
	GLSLLOG.ClearLOG();
	GLhandleARB GLhandleARBTMP=0;
	char * GLSLFileBuffer=ReadLocFullFile_ANSI_TXT(shaderfilename);
	int dwNum=WideCharToMultiByte(CP_ACP,0,shaderfilename,-1,NULL,0,NULL,NULL);
	char * shaderfilenameANSI=new char[dwNum];
	WideCharToMultiByte(CP_ACP,0,shaderfilename,-1,shaderfilenameANSI,dwNum,NULL,NULL);
	if(!GLSLFileBuffer)
	{
		GLSLLOG.AddLOG("****** GLSL ERROR ******");
		GLSLLOG.AddLOG("Cannot open shader file");
		GLSLLOG.AddLOG(shaderfilenameANSI);
		GLSLLOG.WriteLOGFile(true);
		GLSLLOG.ClearLOG();
		delete [] shaderfilenameANSI;
		return 0;
	}
	GLSLLOG.AddLOG("****** GLSL Loading File ******");
	GLSLLOG.AddLOG(shaderfilenameANSI);
	GLhandleARBTMP = CompileShader(GLSLFileBuffer,ShaderObject);
	
	delete [] shaderfilenameANSI;
	delete [] GLSLFileBuffer;
	return GLhandleARBTMP;
}
GLhandleARB CGLSLLoader::CompileShader(char *ShaderAssembly,GLenum ShaderObject)
{
	GLhandleARB GLSLShaderObject=glCreateShaderObjectARB(ShaderObject);
	glShaderSourceARB( GLSLShaderObject, 1, (const GLcharARB **)(&ShaderAssembly), NULL );
	glCompileShaderARB( GLSLShaderObject);
	GLint bCompiled=0;
	glGetObjectParameterivARB( GLSLShaderObject, GL_OBJECT_COMPILE_STATUS_ARB, &bCompiled );
	if(!bCompiled)
	{
		char * logbuffer=GetGLSLInfoLog(GLSLShaderObject);
		GLSLLOG.AddLOG("****** GLSL ERROR ******");
		GLSLLOG.AddLOG(logbuffer);
		GLSLLOG.WriteLOGFile(true);
		GLSLLOG.ClearLOG();
		delete[] logbuffer;
	}
	return GLSLShaderObject;
}
bool CGLSLLoader::GetGLSLLinkSTATUS(GLhandleARB g_programObj)
{
//
// Link the program object and print out the info log...
//
	GLint bLinked=false;
	glLinkProgramARB( g_programObj );
	glGetObjectParameterivARB( g_programObj, GL_OBJECT_LINK_STATUS_ARB, &bLinked );

	if( bLinked == false )
	{
		char * logbuffer=GetGLSLInfoLog(g_programObj);
		GLSLLOG.ClearLOG();
		GLSLLOG.AddLOG("****** GLSL ERROR ******");
		GLSLLOG.AddLOG(logbuffer);
		GLSLLOG.WriteLOGFile(true);
		GLSLLOG.ClearLOG();
		delete[] logbuffer;
		/*char str[40960];
		glGetInfoLogARB( g_programObj, sizeof(str), NULL, str );
		MessageBox( NULL, "Error Message saving to Error.log", "Linking Error", MB_OK|MB_ICONEXCLAMATION );
		//WritePrivateProfileString("Glsl","Linking_Error",str,".\\Error_log.ini");
		HANDLE   hFile;     
      
		hFile   =   CreateFileW(L".\\Error.log",                       //   open   MYFILE.TXT     
                                  GENERIC_WRITE,                             //   open   for   reading     
                                  FILE_SHARE_READ,                       //   share   for   reading     
                                  NULL,                                             //   no   security     
                                  CREATE_ALWAYS,                           //   existing   file   only     
                                  FILE_ATTRIBUTE_NORMAL,           //   normal   file     
                                  NULL);
		str[40959]=0;
		DWORD savesize=0;
		WriteFile(hFile,str,min(40959,strlen(str)),&savesize,NULL);
		CloseHandle(hFile);*/
		return false;
	}
	return true;
}

bool CGLSLLoader::LoadShader(const wchar_t* VSfilename,const wchar_t* PSfilename)
{
	ClearShader();
	GLSL_Shader_Obj.g_VS=CompileShader(VSfilename,GL_VERTEX_SHADER_ARB);
	GLSL_Shader_Obj.g_PS=CompileShader(PSfilename,GL_FRAGMENT_SHADER_ARB);
	GLSL_Shader_Obj.g_PO = glCreateProgramObjectARB();
	glAttachObjectARB( GLSL_Shader_Obj.g_PO, GLSL_Shader_Obj.g_VS );
	glAttachObjectARB( GLSL_Shader_Obj.g_PO, GLSL_Shader_Obj.g_PS );
	return GetGLSLLinkSTATUS( GLSL_Shader_Obj.g_PO );
}


void CGLSLLoader::ClearShader(void)
{
	if((GLSL_Shader_Obj.g_PO>0)&&(GLSL_Shader_Obj.g_VS>0)) glDetachObjectARB(GLSL_Shader_Obj.g_PO,GLSL_Shader_Obj.g_VS);
	if((GLSL_Shader_Obj.g_PO>0)&&(GLSL_Shader_Obj.g_PS>0)) glDetachObjectARB(GLSL_Shader_Obj.g_PO,GLSL_Shader_Obj.g_PS);
	if(GLSL_Shader_Obj.g_PO>0) glDeleteObjectARB(GLSL_Shader_Obj.g_PO);
	if(GLSL_Shader_Obj.g_VS>0) glDeleteObjectARB(GLSL_Shader_Obj.g_VS);
	if(GLSL_Shader_Obj.g_PS>0) glDeleteObjectARB(GLSL_Shader_Obj.g_PS);
	GLSL_Shader_Obj.g_VS=0;
	GLSL_Shader_Obj.g_PS=0;
	GLSL_Shader_Obj.g_PO=0;
}
