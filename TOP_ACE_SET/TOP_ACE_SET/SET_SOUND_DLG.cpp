// SET_SOUND_DLG.cpp : implementation file
//

#include "stdafx.h"
#include "TOP_ACE_SET.h"
#include "SET_SOUND_DLG.h"
#include"IniFile.h"

// CSET_SOUND_DLG dialog

IMPLEMENT_DYNAMIC(CSET_SOUND_DLG, CTopAceDialog)
extern tGameSet GameSet;
extern tSoundSet SoundSet;
extern tJoyStictSet JoyStictSet;

CSET_SOUND_DLG::CSET_SOUND_DLG(CWnd* pParent /*=NULL*/)
	: CTopAceDialog(CSET_SOUND_DLG::IDD, pParent)
	, SliderNumMusic(0)
	, SliderNumEffect(0)
	, SliderNumVoice(0)
{

}

CSET_SOUND_DLG::~CSET_SOUND_DLG()
{
}

void CSET_SOUND_DLG::DoDataExchange(CDataExchange* pDX)
{
	CTopAceDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EDIT_Music);
	DDX_Control(pDX, IDC_EDIT2, m_EDIT_Effect);
	DDX_Control(pDX, IDC_EDIT20, m_EDIT_Voice);
	DDX_Control(pDX, IDC_SLIDER3, m_Slider_Voice);
	DDX_Control(pDX, IDC_SLIDER2, m_Slider_Effect);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider_Music);
	DDX_Control(pDX, IDC_STATIC_BGM, m_LTEXT_BGM);
	DDX_Control(pDX, IDC_STATIC_EFFECT, m_LTEXT_EFFECT);
	DDX_Control(pDX, IDC_STATIC_VOICE, m_LTEXT_VOICE);
}


BEGIN_MESSAGE_MAP(CSET_SOUND_DLG, CTopAceDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CSET_SOUND_DLG::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CSET_SOUND_DLG::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CSET_SOUND_DLG::OnNMCustomdrawSlider3)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CSET_SOUND_DLG::OnEnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CSET_SOUND_DLG::OnEnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT20, &CSET_SOUND_DLG::OnEnKillfocusEdit20)
END_MESSAGE_MAP()


// CSET_SOUND_DLG message handlers

void CSET_SOUND_DLG::InitUI(void)
{
	m_LTEXT_BGM.SetWindowText(_T("音乐音量"));
	m_LTEXT_EFFECT.SetWindowText(_T("音效音量"));
	m_LTEXT_VOICE.SetWindowText(_T("语音音量"));
	CString cSetEdit;
	cSetEdit.Format(_T("%d"),SoundSet.BGM);
	m_EDIT_Music.SetWindowText(cSetEdit);
	cSetEdit.Empty();
	cSetEdit.Format(_T("%d"),SoundSet.Effect);
	m_EDIT_Effect.SetWindowText(cSetEdit);
	cSetEdit.Empty();
	cSetEdit.Format(_T("%d"),SoundSet.Voice);
	m_EDIT_Voice.SetWindowText(cSetEdit);

	m_Slider_Music.SetPos(SoundSet.BGM);
	m_Slider_Music.SetTicFreq(1);
	m_Slider_Effect.SetPos(SoundSet.Effect);
	m_Slider_Effect.SetTicFreq(1);
	m_Slider_Voice.SetPos(SoundSet.Voice);
	m_Slider_Voice.SetTicFreq(1);

}



void CSET_SOUND_DLG::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	*pResult = 0;
	if(SliderNumMusic!=m_Slider_Music.GetPos())
	{
		SliderNumMusic=m_Slider_Music.GetPos();
		SoundSet.BGM=SliderNumMusic;
		CString cSetEdit;
		cSetEdit.Format(_T("%d"),SoundSet.BGM);
		m_EDIT_Music.SetWindowText(cSetEdit);
	}
}

void CSET_SOUND_DLG::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	*pResult = 0;
	if(SliderNumEffect!=m_Slider_Effect.GetPos())
	{
		SliderNumEffect=m_Slider_Effect.GetPos();
		SoundSet.Effect=SliderNumEffect;
		CString cSetEdit;
		cSetEdit.Format(_T("%d"),SoundSet.Effect);
		m_EDIT_Effect.SetWindowText(cSetEdit);
	}
}

void CSET_SOUND_DLG::OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	*pResult = 0;
	if(SliderNumVoice!=m_Slider_Voice.GetPos())
	{
		SliderNumVoice=m_Slider_Voice.GetPos();
		SoundSet.Voice=SliderNumVoice;
		CString cSetEdit;
		cSetEdit.Format(_T("%d"),SoundSet.Voice);
		m_EDIT_Voice.SetWindowText(cSetEdit);
	}
}
void CSET_SOUND_DLG::OnEnKillfocusEdit1()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CString cSetEdit;
	m_EDIT_Music.GetWindowTextW(cSetEdit);
	if(!cSetEdit.IsEmpty())
	{
		swscanf_s(cSetEdit.GetBuffer(),_T("%d"),&SoundSet.BGM);

	}

	if(SoundSet.BGM<0)
	{
		SoundSet.BGM=0;
	}
	if(SoundSet.BGM>100)
	{
		SoundSet.BGM=100;
	}
	cSetEdit.Format(_T("%d"),SoundSet.BGM);
	m_EDIT_Music.SetWindowText(cSetEdit);
	m_Slider_Music.SetPos(SoundSet.BGM);
}

void CSET_SOUND_DLG::OnEnKillfocusEdit2()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CString cSetEdit;
	m_EDIT_Effect.GetWindowTextW(cSetEdit);
	if(!cSetEdit.IsEmpty())
	{
		swscanf_s(cSetEdit.GetBuffer(),_T("%d"),&SoundSet.Effect);

	}

	if(SoundSet.Effect<0)
	{
		SoundSet.Effect=0;
	}
	if(SoundSet.Effect>100)
	{
		SoundSet.Effect=100;
	}
	cSetEdit.Format(_T("%d"),SoundSet.Effect);
	m_EDIT_Effect.SetWindowText(cSetEdit);
	m_Slider_Effect.SetPos(SoundSet.Effect);
}

void CSET_SOUND_DLG::OnEnKillfocusEdit20()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CString cSetEdit;
	m_EDIT_Voice.GetWindowTextW(cSetEdit);
	if(!cSetEdit.IsEmpty())
	{
		swscanf_s(cSetEdit.GetBuffer(),_T("%d"),&SoundSet.Voice);

	}

	if(SoundSet.Voice<0)
	{
		SoundSet.Voice=0;
	}
	if(SoundSet.Voice>100)
	{
		SoundSet.Voice=100;
	}
	cSetEdit.Format(_T("%d"),SoundSet.Voice);
	m_EDIT_Voice.SetWindowText(cSetEdit);
	m_Slider_Voice.SetPos(SoundSet.Voice);
}

