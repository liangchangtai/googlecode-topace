// KeyBoardSet.cpp : implementation file
//

#include "stdafx.h"
#include "TOP_ACE_SET.h"
#include "KeyBoardSet.h"
#include"IniFile.h"

// CKeyBoardSet dialog

IMPLEMENT_DYNAMIC(CKeyBoardSet, CDialog)
extern tGameSet GameSet;
extern tSoundSet SoundSet;
extern tJoyStictSet JoyStictSet;
extern tKeyBoardSet KeyBoardSet;
CKeyBoardSet::CKeyBoardSet(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyBoardSet::IDD, pParent)
{

}

CKeyBoardSet::~CKeyBoardSet()
{
}

void CKeyBoardSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD1, m_EDIT[JOY_KEY_UP]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD2, m_EDIT[JOY_KEY_DOWN]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD3, m_EDIT[JOY_KEY_LEFT]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD4, m_EDIT[JOY_KEY_RIGHT]);

	DDX_Control(pDX, IDC_EDIT_KEYBOARD5, m_EDIT[JOY_KEY_VIEW_UP]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD6, m_EDIT[JOY_KEY_VIEW_DOWN]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD7, m_EDIT[JOY_KEY_VIEW_LEFT]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD8, m_EDIT[JOY_KEY_VIEW_RIGHT]);

	DDX_Control(pDX, IDC_EDIT_KEYBOARD9, m_EDIT[JOY_KEY_SPEED_UP]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD10, m_EDIT[JOY_KEY_SPEED_DOWN]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD11, m_EDIT[JOY_KEY_L]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD12, m_EDIT[JOY_KEY_R]);

	DDX_Control(pDX, IDC_EDIT_KEYBOARD13, m_EDIT[JOY_KEY_MAIN_WEAPON]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD14, m_EDIT[JOY_KEY_SUB_WEAPON]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD15, m_EDIT[JOY_KEY_MAP]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD16, m_EDIT[JOY_KEY_LOCK]);

	DDX_Control(pDX, IDC_EDIT_KEYBOARD17, m_EDIT[JOY_KEY_SELECT]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD18, m_EDIT[JOY_KEY_START]);
	DDX_Control(pDX, IDC_EDIT_KEYBOARD19, m_EDIT[JOY_KEY_VIEW_RESET]);
}


BEGIN_MESSAGE_MAP(CKeyBoardSet, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_KEYBOARD1, &CKeyBoardSet::OnEnKillfocusEditKeyboard1)
END_MESSAGE_MAP()

void CKeyBoardSet::OnEnKillfocusEditKeyboard1()
{
	WCHAR GetWindowText[16];
	m_EDIT[JOY_KEY_UP].GetWindowTextW(GetWindowText,10);
	KeyBoardSet.KeySet[JOY_KEY_UP]=_wtoi(GetWindowText);
	// TODO: Add your control notification handler code here
}

void CKeyBoardSet::InitUI(void)
{
	//_itow_s(KeyBoardSet.KeySet[JOY_KEY_UP],SetChar,sizeof(SetChar),10);
	CString CSetWindowText;
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_UP]);
	m_EDIT[JOY_KEY_UP].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_DOWN]);
	m_EDIT[JOY_KEY_DOWN].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_LEFT]);
	m_EDIT[JOY_KEY_LEFT].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_RIGHT]);
	m_EDIT[JOY_KEY_RIGHT].SetWindowTextW(CSetWindowText);

	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_MAIN_WEAPON]);
	m_EDIT[JOY_KEY_MAIN_WEAPON].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_SUB_WEAPON]);
	m_EDIT[JOY_KEY_SUB_WEAPON].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_LOCK]);
	m_EDIT[JOY_KEY_LOCK].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_MAP]);
	m_EDIT[JOY_KEY_MAP].SetWindowTextW(CSetWindowText);

	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_SPEED_UP]);
	m_EDIT[JOY_KEY_SPEED_UP].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_SPEED_DOWN]);
	m_EDIT[JOY_KEY_SPEED_DOWN].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_L]);
	m_EDIT[JOY_KEY_L].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_R]);
	m_EDIT[JOY_KEY_R].SetWindowTextW(CSetWindowText);

	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_VIEW_UP]);
	m_EDIT[JOY_KEY_VIEW_UP].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_VIEW_DOWN]);
	m_EDIT[JOY_KEY_VIEW_DOWN].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_VIEW_LEFT]);
	m_EDIT[JOY_KEY_VIEW_LEFT].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_VIEW_RIGHT]);
	m_EDIT[JOY_KEY_VIEW_RIGHT].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_VIEW_RESET]);
	m_EDIT[JOY_KEY_VIEW_RESET].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_SELECT]);
	m_EDIT[JOY_KEY_SELECT].SetWindowTextW(CSetWindowText);
	CSetWindowText.Format(_T("%d"),KeyBoardSet.KeySet[JOY_KEY_START]);
	m_EDIT[JOY_KEY_START].SetWindowTextW(CSetWindowText);
}
