#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSET_SOUND_DLG dialog

class CSET_SOUND_DLG : public CTopAceDialog
{
	DECLARE_DYNAMIC(CSET_SOUND_DLG)

public:
	CSET_SOUND_DLG(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSET_SOUND_DLG();

// Dialog Data
	enum { IDD = IDD_DIALOG_SET_SOUND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual void InitUI(void);
	virtual BOOL SaveCfg(void){return TRUE;}

	CEdit m_EDIT_Music;
	CEdit m_EDIT_Effect;
	CEdit m_EDIT_Voice;
	CSliderCtrl m_Slider_Voice;
	CSliderCtrl m_Slider_Effect;
	CSliderCtrl m_Slider_Music;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	int SliderNumMusic;
	int SliderNumEffect;
	int SliderNumVoice;
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnEnKillfocusEdit20();
	CStatic m_LTEXT_BGM;
	CStatic m_LTEXT_EFFECT;
	CStatic m_LTEXT_VOICE;
};
