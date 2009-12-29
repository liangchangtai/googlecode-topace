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
	, ResolutionSet(-1)
{

}

CSystemSetDLG::~CSystemSetDLG()
{
}

void CSystemSetDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_COMBOBOX_Resolution);
	DDX_Control(pDX, IDC_EDIT1, m_EDIT_w);
	DDX_Control(pDX, IDC_EDIT2, m_EDIT_h);
}


BEGIN_MESSAGE_MAP(CSystemSetDLG, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CSystemSetDLG::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSystemSetDLG::OnBnClickedRadio2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSystemSetDLG::OnCbnSelchangeCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CSystemSetDLG::OnEnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CSystemSetDLG::OnEnKillfocusEdit2)
END_MESSAGE_MAP()


// CSystemSetDLG message handlers

void CSystemSetDLG::InitUI(void)
{
	DEVMODE   lpDevMode;
	int iModeNum=0;
	unsigned int ResolutionPels=0;
	ResolutionSet=-1;
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
	for(int i=0;i<m_COMBOBOX_Resolution.GetCount();i++)
	{
		CString ctestResolutionSet1,ctestResolutionSet12;
		ctestResolutionSet1.Format(_T("%d X %d %dbit"),GameSet.winW,GameSet.winH,GameSet.bits);
		m_COMBOBOX_Resolution.GetLBText(i,ctestResolutionSet12);
		if(ctestResolutionSet1==ctestResolutionSet12)
		{
			ResolutionSet=i;
			break;
		}
	}
	if(ResolutionSet)
	{
		m_COMBOBOX_Resolution.SetCurSel(ResolutionSet);
		CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);
	}
	else
	{
		CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO2);
	}
	
}

void CSystemSetDLG::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	m_COMBOBOX_Resolution.EnableWindow(true);
	m_EDIT_w.EnableWindow(false);
	m_EDIT_h.EnableWindow(false);
	OnCbnSelchangeCombo1();
}

void CSystemSetDLG::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	m_COMBOBOX_Resolution.EnableWindow(false);
	m_EDIT_w.EnableWindow(true);
	m_EDIT_h.EnableWindow(true);
}

void CSystemSetDLG::OnCbnSelchangeCombo1()
{
	CString getResolutionSet;
	//getResolutionSet=_T("123");
	//int test=0;
	//swscanf_s(getResolutionSet.GetBuffer(),_T("%d"),test);
	ResolutionSet=m_COMBOBOX_Resolution.GetCurSel();
	m_COMBOBOX_Resolution.GetLBText(ResolutionSet,getResolutionSet);
	swscanf_s(getResolutionSet.GetBuffer(),_T("%d X %d %dbit"),&GameSet.winW,&GameSet.winH,&GameSet.bits);
	// TODO: Add your control notification handler code here
}

void CSystemSetDLG::OnEnKillfocusEdit1()
{
	// TODO: Add your control notification handler code here
	CString getResolutionSet;
	m_EDIT_w.GetWindowTextW(getResolutionSet);
	swscanf_s(getResolutionSet.GetBuffer(),_T("%d"),&GameSet.winW);
}

void CSystemSetDLG::OnEnKillfocusEdit2()
{
	// TODO: Add your control notification handler code here
	CString getResolutionSet;
	m_EDIT_h.GetWindowTextW(getResolutionSet);
	swscanf_s(getResolutionSet.GetBuffer(),_T("%d"),&GameSet.winH);
}
