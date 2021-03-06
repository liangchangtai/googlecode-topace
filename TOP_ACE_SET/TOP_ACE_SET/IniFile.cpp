
#include "stdafx.h"
#include"IniFile.h"
tGameSet GameSet;
tSoundSet SoundSet;
tJoyStictSet JoyStictSet;
wchar_t  TestModelPath[512];
wchar_t Writeini[64]={0};
void loadIniFile()
{
	FILE *IntFile=NULL;
	fopen_s(&IntFile,IniFileName,"r");
	if (IntFile)
	{
		fclose(IntFile);

	}
	else
	{
		WritePrivateProfileString(_T("GameSet"),_T("winW"),_T("800"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("winH"),_T("600"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("bits"),_T("32"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("depth"),_T("24"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("isFullScreem"),_T("0"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("SYNC"),_T("0"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("LOW"),_T("0"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("AA"),_T("0"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("AF"),_T("1"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("FPS"),_T("60"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("Light"),_T("2"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("Water"),_T("0"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("Bloom"),_T("0"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("Shadow"),_T("0"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("MoveBlur"),_T("0"),_T(IniFileName));
		WritePrivateProfileString(_T("GameSet"),_T("Cloud"),_T("0"),_T(IniFileName));
		WritePrivateProfileString(_T("SoundSet"),_T("BGM"),_T("100"),_T(IniFileName));
		WritePrivateProfileString(_T("SoundSet"),_T("Effect"),_T("100"),_T(IniFileName));
		WritePrivateProfileString(_T("SoundSet"),_T("Voice"),_T("100"),_T(IniFileName));
		
		WritePrivateProfileString(_T("other"),_T("TouchMoveOverride"),_T("1"),_T(IniFileName));
		WritePrivateProfileString(_T("other"),_T("TouchZoomOverride"),_T("1"),_T(IniFileName));

		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_UP"),_T("32"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_DOWN"),_T("22"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_LEFT"),_T("12"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_RIGHT"),_T("2"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_MAIN_WEAPON"),_T("11"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SUB_WEAPON"),_T("1"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_LOCK"),_T("31"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_MAP"),_T("21"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SPEED_UP"),_T("41"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SPEED_DOWN"),_T("51"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_L"),_T("61"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_R"),_T("71"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_UP"),_T("52"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_DOWN"),_T("42"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_LEFT"),_T("112"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_RIGHT"),_T("102"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_RESET"),_T("111"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SELECT"),_T("81"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_START"),_T("91"),_T(IniFileName));
		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_NO_USE"),_T("101"),_T(IniFileName));

		WritePrivateProfileString(_T("other"),_T("TestModelPath"),_T("data/1234.tam"),_T(IniFileName));
	}

		GameSet.winW=GetPrivateProfileInt(_T("GameSet"),_T("winW"),800,_T(IniFileName));
		GameSet.winH=GetPrivateProfileInt(_T("GameSet"),_T("winH"),600,_T(IniFileName));
		GameSet.winW=GameSet.winW-GameSet.winW%4;
		GameSet.winH=GameSet.winH-GameSet.winH%4;
		GameSet.bits=GetPrivateProfileInt(_T("GameSet"),_T("bits"),32,_T(IniFileName));
		GameSet.depth=GetPrivateProfileInt(_T("GameSet"),_T("depth"),24,_T(IniFileName));
		if(GetPrivateProfileInt(_T("GameSet"),_T("isFullScreem"),0,_T(IniFileName))>0)
			GameSet.isFullScreem=true;
		else
			GameSet.isFullScreem=false;
		if(GetPrivateProfileInt(_T("GameSet"),_T("SYNC"),0,_T(IniFileName))>0)
			GameSet.SYNC=true;
		else
			GameSet.SYNC=false;
		if(GetPrivateProfileInt(_T("GameSet"),_T("LOW"),0,_T(IniFileName))>0)
			GameSet.LOW=true;
		else
			GameSet.LOW=false;
		GameSet.AA=GetPrivateProfileInt(_T("GameSet"),_T("AA"),0,_T(IniFileName));
		GameSet.AF=GetPrivateProfileInt(_T("GameSet"),_T("AF"),0,_T(IniFileName));
		GameSet.FPS=GetPrivateProfileInt(_T("GameSet"),_T("FPS"),60,_T(IniFileName));
		GameSet.Light=GetPrivateProfileInt(_T("GameSet"),_T("Light"),0,_T(IniFileName));
		GameSet.Water=GetPrivateProfileInt(_T("GameSet"),_T("Water"),0,_T(IniFileName));
		GameSet.Bloom=GetPrivateProfileInt(_T("GameSet"),_T("Bloom"),0,_T(IniFileName));
		GameSet.Shadow=GetPrivateProfileInt(_T("GameSet"),_T("Shadow"),0,_T(IniFileName));
		GameSet.MoveBlur=GetPrivateProfileInt(_T("GameSet"),_T("MoveBlur"),0,_T(IniFileName));
		GameSet.Cloud=GetPrivateProfileInt(_T("GameSet"),_T("Cloud"),0,_T(IniFileName));

		SoundSet.BGM=GetPrivateProfileInt(_T("SoundSet"),_T("BGM"),100,_T(IniFileName));
		SoundSet.Effect=GetPrivateProfileInt(_T("SoundSet"),_T("Effect"),100,_T(IniFileName));
		SoundSet.Voice=GetPrivateProfileInt(_T("SoundSet"),_T("Voice"),100,_T(IniFileName));
		
		GameSet.TouchMoveOverride=GetPrivateProfileIntW(_T("other"),_T("TouchMoveOverride"),1,_T(IniFileName));
		GameSet.TouchZoomOverride=GetPrivateProfileIntW(_T("other"),_T("TouchZoomOverride"),1,_T(IniFileName));

		JoyStictSet.KeySet[JOY_KEY_UP]			=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_UP"),			32,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_DOWN]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_DOWN"),			22,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_LEFT]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_LEFT"),			12,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_RIGHT]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_RIGHT"),		2,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_MAIN_WEAPON]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_MAIN_WEAPON"),	11,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_SUB_WEAPON]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_SUB_WEAPON"),	1,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_LOCK]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_LOCK"),			31,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_MAP]			=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_MAP"),			21,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_SPEED_UP]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_SPEED_UP"),		41,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_SPEED_DOWN]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_SPEED_DOWN"),	51,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_L]			=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_L"),			61,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_R]			=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_R"),			71,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_VIEW_UP]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_VIEW_UP"),		52,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_VIEW_DOWN]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_VIEW_DOWN"),	42,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_VIEW_LEFT]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_VIEW_LEFT"),	112,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_VIEW_RIGHT]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_VIEW_RIGHT"),	102,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_VIEW_RESET]	=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_VIEW_RESET"),	111,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_SELECT]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_SELECT"),		81,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_START]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_START"),		91,_T(IniFileName));
		JoyStictSet.KeySet[JOY_KEY_NO_USE]		=GetPrivateProfileInt(_T("JoyStictSet"),_T("JOY_KEY_NO_USE"),		101,_T(IniFileName));

		
		GetPrivateProfileStringW(L"other",L"TestModelPath",L"data/1234.tam",TestModelPath,512,_T(IniFileName));
}

void SaveIniFile()
{
	//char Writeini[256]={0};
	//sprintf_s(Writeini,sizeof(Writeini),"%d",GameSet.winW);
	//CString Writeini;
	//Writeini.Format(_T("%d"),GameSet.winW);
	GameSet.winW=GameSet.winW-GameSet.winW%4;
	GameSet.winH=GameSet.winH-GameSet.winH%4;
	_itow_s(GameSet.winW,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("winW"),Writeini,_T(IniFileName));
	_itow_s(GameSet.winH,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("winH"),Writeini,_T(IniFileName));
	_itow_s(GameSet.bits,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("bits"),Writeini,_T(IniFileName));
	_itow_s(GameSet.depth,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("depth"),Writeini,_T(IniFileName));
	_itow_s(GameSet.isFullScreem,Writeini,sizeof(Writeini),10);	WritePrivateProfileString(_T("GameSet"),_T("isFullScreem"),Writeini,_T(IniFileName));
	_itow_s(GameSet.SYNC,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("SYNC"),Writeini,_T(IniFileName));
	_itow_s(GameSet.LOW,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("LOW"),Writeini,_T(IniFileName));
	_itow_s(GameSet.AA,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("AA"),Writeini,_T(IniFileName));
	_itow_s(GameSet.AF,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("AF"),Writeini,_T(IniFileName));
	_itow_s(GameSet.FPS,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("GameSet"),_T("FPS"),Writeini,_T(IniFileName));
	_itow_s(GameSet.Light,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("Light"),Writeini,_T(IniFileName));
	_itow_s(GameSet.Water,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("Water"),Writeini,_T(IniFileName));
	_itow_s(GameSet.Bloom,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("Bloom"),Writeini,_T(IniFileName));
	_itow_s(GameSet.Shadow,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("Shadow"),Writeini,_T(IniFileName));
	_itow_s(GameSet.MoveBlur,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("MoveBlur"),Writeini,_T(IniFileName));
	_itow_s(GameSet.Cloud,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("GameSet"),_T("Cloud"),Writeini,_T(IniFileName));

	_itow_s(SoundSet.BGM,Writeini,sizeof(Writeini),10);			WritePrivateProfileString(_T("SoundSet"),_T("BGM"),Writeini,_T(IniFileName));
	_itow_s(SoundSet.Effect,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("SoundSet"),_T("Effect"),Writeini,_T(IniFileName));
	_itow_s(SoundSet.Voice,Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("SoundSet"),_T("Voice"),Writeini,_T(IniFileName));
	
	_itow_s(GameSet.TouchMoveOverride,Writeini,sizeof(Writeini),10); WritePrivateProfileString(_T("other"),_T("TouchMoveOverride"),Writeini,_T(IniFileName));
	_itow_s(GameSet.TouchZoomOverride,Writeini,sizeof(Writeini),10); WritePrivateProfileString(_T("other"),_T("TouchZoomOverride"),Writeini,_T(IniFileName));

	_itow_s(JoyStictSet.KeySet[JOY_KEY_UP],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_UP"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_DOWN],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_DOWN"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_LEFT],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_LEFT"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_RIGHT],Writeini,sizeof(Writeini),10);	WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_RIGHT"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_MAIN_WEAPON],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_MAIN_WEAPON"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_SUB_WEAPON],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SUB_WEAPON"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_LOCK],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_LOCK"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_MAP],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_MAP"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_SPEED_UP],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SPEED_UP"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_SPEED_DOWN],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SPEED_DOWN"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_L],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_L"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_R],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_R"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_VIEW_UP],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_UP"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_VIEW_DOWN],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_DOWN"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_VIEW_LEFT],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_LEFT"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_VIEW_RIGHT],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_RIGHT"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_VIEW_RESET],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_VIEW_RESET"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_SELECT],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_SELECT"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_START],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_START"),Writeini,_T(IniFileName));
	_itow_s(JoyStictSet.KeySet[JOY_KEY_NO_USE],Writeini,sizeof(Writeini),10);		WritePrivateProfileString(_T("JoyStictSet"),_T("JOY_KEY_NO_USE"),Writeini,_T(IniFileName));

	
	WritePrivateProfileString(_T("other"),_T("TestModelPath"),TestModelPath,_T(IniFileName));
}