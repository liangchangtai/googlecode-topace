﻿#ifndef _TEXTURES_H
#define _TEXTURES_H
#include "DDS.h"
#include "tga.h"
#define NO_TEX 0
#define IS_DDS 1
#define IS_TGA 2
#define IS_DEF 3
#include "TALogSys.h"
class Textures
{
public:
	Textures(void);
	~Textures(void);
	bool loadfile(char * filename);
	bool loadfile(wchar_t * filename);
	unsigned int LoadToVRAM(int TexParameter = 0);
	bool isRAM();
	bool isVRAM();
	int GetTexError();
	void Del_RAM();
	void Del_VRAM();
	int TexType;
	GLuint TexID;
	CDDS *DDSfile;
	TGA *TGAfile;
	bool UseAlpha;

	static GLuint DefineTexID;
	static GLuint DefNorTexID;
	static GLuint DefSpeTexID;
	static void LoadDefineTex();
	static void DelDefineTex();

	int TexW;
	int TexH;
};
#endif