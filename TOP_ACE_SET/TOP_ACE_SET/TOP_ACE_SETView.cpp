// TOP_ACE_SETView.cpp : CTOP_ACE_SETView 类的实现
//

#include "stdafx.h"
#include "TOP_ACE_SET.h"

#include "TOP_ACE_SETDoc.h"
#include "TOP_ACE_SETView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern tGameSet GameSet;
extern tSoundSet SoundSet;
extern tJoyStictSet JoyStictSet;

// CTOP_ACE_SETView

IMPLEMENT_DYNCREATE(CTOP_ACE_SETView, CFormView)

BEGIN_MESSAGE_MAP(CTOP_ACE_SETView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CTOP_ACE_SETView::OnBnClickedButton2)
//	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB1, &CTOP_ACE_SETView::OnTcnSelchangingTab1)
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTOP_ACE_SETView::OnTcnSelchangeTab1)
ON_BN_CLICKED(IDC_BUTTON1, &CTOP_ACE_SETView::OnBnClickedButton1)
END_MESSAGE_MAP()

// CTOP_ACE_SETView 构造/析构

CTOP_ACE_SETView::CTOP_ACE_SETView()
	: CFormView(CTOP_ACE_SETView::IDD)
	, m_CurSelTab(0)
	, m_CurDlg(NULL)
{
	// TODO: 在此处添加构造代码
	loadIniFile();

}

CTOP_ACE_SETView::~CTOP_ACE_SETView()
{
}

void CTOP_ACE_SETView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}

BOOL CTOP_ACE_SETView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);

}

void CTOP_ACE_SETView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	m_TabCtrl.InsertItem(0,_T("图像设置"));
	//m_TabCtrl.InsertItem(1,_T("手柄设置"));
	//m_TabCtrl.InsertItem(2,_T("键盘设置"));
	//m_TabCtrl.InsertItem(3,_T("声音设置"));
	
	((CButton *)GetDlgItem(IDC_BUTTON1))->SetWindowText(_T("保存设置"));
	((CButton *)GetDlgItem(IDC_BUTTON2))->SetWindowText(_T("运行"));

	CRect rect;
	GetClientRect(&rect);

	m_SystemSetDLG.Create(IDD_DIALOG_SET_SYS,this);
	m_SystemSetDLG.MoveWindow(rect.left+20,rect.top+40,300,rect.bottom-140);
	m_SystemSetDLG.InitUI();
	m_SystemSetDLG.ShowWindow(SW_SHOW);
	m_pDlgs.push_back( &m_SystemSetDLG );
	m_CurDlg = m_pDlgs[0];

	m_GamePadSetDLG.Create(IDD_DIALOG_KEYSET,this);
	//m_GamePadSetDLG.MoveWindow(rect.left+20,rect.top+40,400,400);IDC_BUTTON2
	m_GamePadSetDLG.ShowWindow(SW_HIDE);
	m_pDlgs.push_back( &m_GamePadSetDLG );

	m_KeyBoardSetDLG.Create(IDD_DIALOG_KEYBOARDSET,this);
	//m_KeyBoardSetDLG.MoveWindow(rect.left+20,rect.top+40,400,400);
	m_KeyBoardSetDLG.ShowWindow(SW_HIDE);
	m_pDlgs.push_back( &m_KeyBoardSetDLG );

	m_SetSoundDLG.Create(IDD_DIALOG_SET_SOUND,this);
	//m_SetSoundDLG.MoveWindow(rect.left+20,rect.top+40,400,400);
	m_SetSoundDLG.ShowWindow(SW_HIDE);
	m_pDlgs.push_back( &m_SetSoundDLG );
}


// CTOP_ACE_SETView 诊断

#ifdef _DEBUG
void CTOP_ACE_SETView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTOP_ACE_SETView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTOP_ACE_SETDoc* CTOP_ACE_SETView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTOP_ACE_SETDoc)));
	return (CTOP_ACE_SETDoc*)m_pDocument;
}
#endif //_DEBUG


// CTOP_ACE_SETView 消息处理程序

void CTOP_ACE_SETView::OnBnClickedButton2()
{
	OnBnClickedButton1();
	ShellExecute(this->m_hWnd,_T("open"),_T("TOP_ACE.exe"),_T(""),_T(""), SW_SHOW );
	// TODO: Add your control notification handler code here
}



void CTOP_ACE_SETView::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	CRect rect; 
	GetClientRect(&rect);
	m_CurSelTab=m_TabCtrl.GetCurSel();

	CTopAceDialog* curDlg = ( m_CurSelTab >= 0 && (size_t)m_CurSelTab < m_pDlgs.size() )?m_pDlgs[m_CurSelTab]:NULL;

	if( curDlg != m_CurDlg )
	{
		if( m_CurDlg )
			m_CurDlg->ShowWindow(SW_HIDE);

		m_CurDlg = curDlg;
		m_CurDlg->MoveWindow(rect.left+20,rect.top+40,300,400);
		m_CurDlg->InitUI();
		m_CurDlg->ShowWindow(SW_SHOW);
		Invalidate();
	}

	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CTOP_ACE_SETView::OnBnClickedButton1()
{
	SaveIniFile();

	for ( size_t i = 0 ; i < m_pDlgs.size() ; ++i )
	{
		if( !m_pDlgs[i]->SaveCfg() )
		{
		}
	}
	// TODO: Add your control notification handler code here
}
