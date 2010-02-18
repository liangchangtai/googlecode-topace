#ifndef _FBO_H
#define _FBO_H
#include <windows.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "Glsl.h"
#define StarTexSizeX 256
#define StarTexSizeY 256
void CheckFBOError();
GLuint InitTex2D(int TexSizeX,int TexSizeY,GLfloat FILTER,GLuint FormatI,GLuint Format,GLuint DataType);
GLuint InitFBO(int winW,int winH);
void DeinitFBO();
void FBOS_Star_Begin();
void FBOS_Star_End();
void TestTexFBO();





#endif