#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "KeyMapDlg.h"


enum EGameOperate
{
	E_GO_UP ,
	E_GO_DOWN ,
	E_GO_LEFT ,
	E_GO_RIGHT ,
	E_GO_SPEED_UP ,
	E_GO_SPEED_DOWN ,
	E_GO_L ,
	E_GO_R ,
	E_GO_MAIN_WEAPON ,
	E_GO_SUB_WEAPON ,
	E_GO_SELECT ,
	E_GO_START ,
	E_GO_MAP ,
	E_GO_LOCK ,
	E_GO_VIEW_UP ,
	E_GO_VIEW_DOWN ,
	E_GO_VIEW_LEFT ,
	E_GO_VIEW_RIGHT ,
	E_GO_VIEW_RESET ,

	E_GO_MAX ,
};

class CKeyBoardCfg
{
public:
	struct SKeyBoardItem
	{
		const TCHAR* m_szName;
		const TCHAR* m_szCfgName;
		UINT m_uDefaultKey;
		UINT m_uUserKey;
	};

private:
	SKeyBoardItem m_szKeyBoardItem[E_GO_MAX];

	inline void InitItem( EGameOperate a_eIndex , const TCHAR* a_pName , const TCHAR* a_pCfgName , UINT a_uKey )
	{
		m_szKeyBoardItem[a_eIndex].m_szName = a_pName;
		m_szKeyBoardItem[a_eIndex].m_szCfgName = a_pCfgName;
		m_szKeyBoardItem[a_eIndex].m_uDefaultKey = a_uKey;
		m_szKeyBoardItem[a_eIndex].m_uUserKey = a_uKey;
	}
public:
	inline CKeyBoardCfg()
	{
		InitItem( E_GO_UP			, _T("操作 上")	, _T("JOY_KEY_UP")			, KEY_W	);
		InitItem( E_GO_DOWN			, _T("操作 下")	, _T("JOY_KEY_DOWN")		, KEY_S	);
		InitItem( E_GO_LEFT			, _T("操作 左")	, _T("JOY_KEY_LEFT")		, KEY_A	);
		InitItem( E_GO_RIGHT		, _T("操作 右")	, _T("JOY_KEY_RIGHT")		, KEY_D	);
		InitItem( E_GO_SPEED_UP		, _T("加速")	, _T("JOY_KEY_SPEED_UP")	, KEY_UP	);
		InitItem( E_GO_SPEED_DOWN	, _T("减速")	, _T("JOY_KEY_SPEED_DOWN")	, KEY_DOWN	);
		InitItem( E_GO_L			, _T("垂直左转"), _T("JOY_KEY_L")			, KEY_LEFT	);
		InitItem( E_GO_R			, _T("垂直右转"), _T("JOY_KEY_R")			, KEY_RIGHT	);
		InitItem( E_GO_MAIN_WEAPON	, _T("主武器")	, _T("JOY_KEY_MAIN_WEAPON")	, KEY_F	);
		InitItem( E_GO_SUB_WEAPON	, _T("副武器")	, _T("JOY_KEY_SUB_WEAPON")	, KEY_G	);
		InitItem( E_GO_SELECT		, _T("选择")	, _T("JOY_KEY_SELECT")		, KEY_SPACE	);
		InitItem( E_GO_START		, _T("开始")	, _T("JOY_KEY_START")		, KEY_RETURN );
		InitItem( E_GO_MAP			, _T("地图")	, _T("JOY_KEY_MAP")			, KEY_T	);
		InitItem( E_GO_LOCK			, _T("锁定")	, _T("JOY_KEY_LOCK")		, KEY_Q	);
		InitItem( E_GO_VIEW_UP		, _T("视角 上")	, _T("JOY_KEY_VIEW_UP")		, KEY_8	);
		InitItem( E_GO_VIEW_DOWN	, _T("视角 下")	, _T("JOY_KEY_VIEW_DOWN")	, KEY_2	);
		InitItem( E_GO_VIEW_LEFT	, _T("视角 左")	, _T("JOY_KEY_VIEW_LEFT")	, KEY_4	);
		InitItem( E_GO_VIEW_RIGHT	, _T("视角 右")	, _T("JOY_KEY_VIEW_RIGHT")	, KEY_6	);
		InitItem( E_GO_VIEW_RESET	, _T("视角复位"), _T("JOY_KEY_VIEW_RESET")	, KEY_5	);
	}

	BOOL LoadCfg()
	{
		for ( int i = 0 ; i < E_GO_MAX ; ++i )
		{
			m_szKeyBoardItem[i].m_uUserKey = GetPrivateProfileInt( _T("KeyBoardSet") , m_szKeyBoardItem[i].m_szCfgName , m_szKeyBoardItem[i].m_uDefaultKey , _T(".\\gameset.ini") );
		}

		return TRUE;
	}

	BOOL SaveCfg()
	{
		TCHAR buf[128];

		for ( int i = 0 ; i < E_GO_MAX ; ++i )
		{
			_stprintf( buf , _T("%d") , m_szKeyBoardItem[i].m_uUserKey );
			if( !WritePrivateProfileString( _T("KeyBoardSet") , m_szKeyBoardItem[i].m_szCfgName , buf ,_T(".\\gameset.ini")) )
				return FALSE;
		}

		return TRUE;
	}

	inline const TCHAR* GetItemName( EGameOperate a_eIndex )const
	{
		ASSERT( a_eIndex >= 0 && a_eIndex < E_GO_MAX );
		return m_szKeyBoardItem[a_eIndex].m_szName;
	}

	inline const TCHAR* GetItemCfgName( EGameOperate a_eIndex )const
	{
		ASSERT( a_eIndex >= 0 && a_eIndex < E_GO_MAX );
		return m_szKeyBoardItem[a_eIndex].m_szCfgName;
	}

	inline void SetItemMapKey( EGameOperate a_eIndex , UINT a_uKey )
	{
		ASSERT( a_eIndex >= 0 && a_eIndex < E_GO_MAX );
		m_szKeyBoardItem[a_eIndex].m_uUserKey = a_uKey;
	}

	inline UINT GetItemMapKey( EGameOperate a_eIndex )const
	{
		ASSERT( a_eIndex >= 0 && a_eIndex < E_GO_MAX );
		return m_szKeyBoardItem[a_eIndex].m_uUserKey;
	}
};

// CKeyBoardSet dialog

class CKeyBoardSet : public CTopAceDialog
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
	afx_msg void OnEnKillfocusEditKeyboard1();

	virtual BOOL SaveCfg(void)
	{
		return m_cfg.SaveCfg();
	}
private:
	CKeyBoardCfg m_cfg;
	CListCtrl m_cList;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemActivateList1(NMHDR *pNMHDR, LRESULT *pResult);
};
