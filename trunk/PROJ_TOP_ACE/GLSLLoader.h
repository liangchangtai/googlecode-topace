//#pragma once
#ifndef _GLSLLOADER_H
#define _GLSLLOADER_H
#include <GL/glew.h>
#include "TALogSys.h"

class CGLSLLoader
{
public:
	CGLSLLoader(void);
	~CGLSLLoader(void);
	char * GetGLSLInfoLog(GLhandleARB GLSLShaderObject);
	bool GetGLSLLinkSTATUS(GLhandleARB g_programObj);
	GLhandleARB CompileShader(const wchar_t* shaderfilename,GLenum ShaderObject);
	GLhandleARB CompileShader(char *ShaderAssembly,GLenum ShaderObject);
	CTALogSys GLSLLOG;
	bool LoadShader(const wchar_t* VSfilename,const wchar_t* PSfilename);
	void ClearShader(void);
	GLhandleARB g_VS;
	GLhandleARB g_PS;
	GLhandleARB g_PO;//ProgramObject
	bool LoadShader2(const wchar_t* ShaderFullName);
	bool LoadShader(const wchar_t* ShaderName,int LightSet);
};

#endif