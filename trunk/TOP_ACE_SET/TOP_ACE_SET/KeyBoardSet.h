#pragma once
#include "afxwin.h"


// CKeyBoardSet dialog

class CKeyBoardSet : public CDialog
{
	DECLARE_DYNAMIC(CKeyBoardSet)

public:
	CKeyBoardSet(CWnd* pParent = NULL);   // standard constructor
	virtual ~CKeyBoardSet();

// Dialog Data
	enum { IDD = IDD_DIALOG_KEYBOARDSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EDIT[20];
	afx_msg void OnEnKillfocusEditKeyboard1();
	void InitUI(void);
	CString KeySetIntToChar(int KeyInt);
	CString cKeycharList[256];
	int KeySetCharToInt(CString KeyChar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
