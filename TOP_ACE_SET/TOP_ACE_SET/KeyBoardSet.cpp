// KeyBoardSet.cpp : implementation file
//

#include "stdafx.h"
#include "TOP_ACE_SET.h"
#include "KeyBoardSet.h"
#include"IniFile.h"


// CKeyBoardSet dialog

IMPLEMENT_DYNAMIC(CKeyBoardSet, CTopAceDialog)
extern tGameSet GameSet;
extern tSoundSet SoundSet;
extern tJoyStictSet JoyStictSet;

CKeyBoardSet::CKeyBoardSet(CWnd* pParent /*=NULL*/)
	: CTopAceDialog(CKeyBoardSet::IDD, pParent)
{
}

CKeyBoardSet::~CKeyBoardSet()
{
}

void CKeyBoardSet::DoDataExchange(CDataExchange* pDX)
{
	CTopAceDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_cList);
}


BEGIN_MESSAGE_MAP(CKeyBoardSet, CTopAceDialog)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST1, &CKeyBoardSet::OnLvnItemActivateList1)
END_MESSAGE_MAP()


BOOL CKeyBoardSet::OnInitDialog()
{
	CTopAceDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if( !m_cfg.LoadCfg() )
	{
		EndDialog( IDCANCEL );
		return FALSE;
	}

	m_cList.SetExtendedStyle( m_cList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	m_cList.InsertColumn( 0 , L"功能" , LVCFMT_LEFT , 100 );
	m_cList.InsertColumn( 1 , L"按键" , LVCFMT_LEFT , 100 );
	m_cList.SetRedraw( FALSE );

	for( int i = 0 ; i < E_GO_MAX ; ++i )
	{
		if( i != m_cList.InsertItem( i , m_cfg.GetItemName( EGameOperate(i) ) ) )
		{
			EndDialog( IDCANCEL );
			return FALSE;
		}

		m_cList.SetItemData( i , (DWORD_PTR)EGameOperate(i) );
		m_cList.SetItemText( i , 1 , GetKeyName(m_cfg.GetItemMapKey( EGameOperate(i) )) );
	}

	m_cList.SetRedraw( TRUE );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CKeyBoardSet::OnLvnItemActivateList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	const EGameOperate eIndex = (EGameOperate)m_cList.GetItemData( pNMIA->iItem );

	CKeyMapDlg dlg( m_cfg.GetItemMapKey( eIndex ) , m_cfg.GetItemName(eIndex) );

	if( dlg.DoModal() == IDOK && m_cfg.GetItemMapKey(eIndex) != dlg.GetKey() )
	{
		m_cfg.SetItemMapKey( eIndex , dlg.GetKey() );

		m_cList.SetItemText( pNMIA->iItem , 1 , GetKeyName(m_cfg.GetItemMapKey( eIndex )) );
	}
}
