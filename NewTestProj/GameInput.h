#ifndef  __GameInput_H__
#define  __GameInput_H__

#include"IniFile.h"
struct tJoyStictKeyVal
{
	float KeyVal[MAX_JOY_KEYS];
};
bool JoyStictUpdeta(int shockX=0,int shockY=0);
bool InitJoyStict(void * MainhDlg);
void FreeJoyStict();

#endif
