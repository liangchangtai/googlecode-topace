// SystemSetDLG.cpp : implementation file
//

#include "stdafx.h"
#include "TOP_ACE_SET.h"
#include "SystemSetDLG.h"
#include"IniFile.h"

// CSystemSetDLG dialog

IMPLEMENT_DYNAMIC(CSystemSetDLG, CDialog)
extern tGameSet GameSet;
extern tSoundSet SoundSet;
extern tJoyStictSet JoyStictSet;
extern tKeyBoardSet KeyBoardSet;
CSystemSetDLG::CSystemSetDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemSetDLG::IDD, pParent)
	, ResolutionSet(0)
{

}

CSystemSetDLG::~CSystemSetDLG()
{
}

void CSystemSetDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_COMBOBOX_Resolution);
}


BEGIN_MESSAGE_MAP(CSystemSetDLG, CDialog)
END_MESSAGE_MAP()


// CSystemSetDLG message handlers

void CSystemSetDLG::InitUI(void)
{
	DEVMODE   lpDevMode;
	int iModeNum=0;
	int ResolutionPels=0;
	m_COMBOBOX_Resolution.ResetContent();
	while( EnumDisplaySettings(NULL,iModeNum,&lpDevMode))
	{
		iModeNum=iModeNum+1;
		CString cDevMode;
		if(lpDevMode.dmBitsPerPel>8)
		{
			if(ResolutionPels!=lpDevMode.dmBitsPerPel)
			{
				cDevMode.Format(_T("%d X %d %dbit"),lpDevMode.dmPelsWidth,lpDevMode.dmPelsHeight,lpDevMode.dmBitsPerPel);
				if(ResolutionPels>(lpDevMode.dmPelsWidth*lpDevMode.dmPelsHeight))
					m_COMBOBOX_Resolution.AddString(cDevMode);
				else
					m_COMBOBOX_Resolution.InsertString(0,cDevMode);
				ResolutionPels=lpDevMode.dmBitsPerPel;
			}
		}
	}
	iModeNum=0;
	m_COMBOBOX_Resolution.SetCurSel(3);
	
}
