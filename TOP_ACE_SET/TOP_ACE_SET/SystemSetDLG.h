#pragma once
#include "afxwin.h"


// CSystemSetDLG dialog

class CSystemSetDLG : public CTopAceDialog
{
	DECLARE_DYNAMIC(CSystemSetDLG)

public:
	CSystemSetDLG(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSystemSetDLG();

// Dialog Data
	enum { IDD = IDD_DIALOG_SET_SYS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual void InitUI(void);
	virtual BOOL SaveCfg(void){return TRUE;}

	CComboBox m_COMBOBOX_Resolution;
	int ResolutionSet;
	
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnCbnSelchangeCombo1();
	CEdit m_EDIT_w;
	CEdit m_EDIT_h;
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnEnKillfocusEdit2();
	CComboBox m_COMBOBOX_ColorBit;
	void Init_COMBOBOX_Resolution(void);
	void Init_COMBOBOX_ColorBit(void);
	afx_msg void OnCbnSelchangeCombo3();
	CButton m_CHECK_SYNC;
	afx_msg void OnBnClickedCheck2();
	CComboBox m_COMBOBOX_AA;
	void Init_COMBOBOX_AA(void);
	afx_msg void OnCbnSelchangeCombo2();
	CEdit m_EDIT_FPS_Set;
	afx_msg void OnEnKillfocusEdit3();
	CButton m_CHECK_Bloom;
	afx_msg void OnBnClickedCheckBloom();
	CStatic m_LTEXT_FPS;
	CStatic m_LTEXT_AA;
	CStatic m_LTEXT_WIN_WARING;
	CStatic m_LTEXT_winw;
	CStatic m_LTEXT_winh;
	CStatic m_LTEXT_wind;
	CStatic m_GROUPBOX_Resolution;
	CStatic m_LTEXT_SHADOW;
	CComboBox m_COMBOBOX_SHADOW;
	void Init_COMBOBOX_SHADOW(void);
	afx_msg void OnCbnSelchangeComboShadow();
	CStatic m_LTEXT_LIGHT;
	CComboBox m_COMBOBOX_LIGHT;
	void Init_COMBOBOX_LIGHT(void);
	afx_msg void OnCbnSelchangeComboLight();
	CStatic m_LTEXT_AF;
	CComboBox m_COMBOBOX_AF;
	void Init_COMBOBOX_AF(void);
	afx_msg void OnCbnSelchangeComboAf();
	CButton m_BUTTON_OPEN_TEST_MODEL;
	CEdit m_EDIT_OPEN_TEST_MODEL;
	afx_msg void OnEnKillfocusEditOpenTestModel();
	afx_msg void OnBnClickedButtonOpenTestModel();
	CEdit m_EDIT_Touch_Move_Override;
	CEdit m_EDIT_Touch_Zoom_Override;
	afx_msg void OnEnKillfocusEditTouchMoveOverride();
	afx_msg void OnEnKillfocusEditTouchZoomOverride();
};
