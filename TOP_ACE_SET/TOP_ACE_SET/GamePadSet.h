#pragma once
#include "afxwin.h"


// CGamePadSet dialog

class CGamePadSet : public CTopAceDialog
{
	DECLARE_DYNAMIC(CGamePadSet)

public:
	CGamePadSet(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGamePadSet();

// Dialog Data
	enum { IDD = IDD_DIALOG_KEYSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EDIT[20];
	virtual void InitUI(void);
};
