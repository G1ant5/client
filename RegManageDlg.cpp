// RegManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "RegManageDlg.h"
#include "afxdialogex.h"
#include "comm.h"
#include "TcpTran.h"


// CRegManageDlg �Ի���

IMPLEMENT_DYNAMIC(CRegManageDlg, CDialogEx)

CRegManageDlg::CRegManageDlg(SOCKET s,CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegManageDlg::IDD, pParent)
{

}

CRegManageDlg::~CRegManageDlg()
{
}

void CRegManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}


BEGIN_MESSAGE_MAP(CRegManageDlg, CDialogEx)
END_MESSAGE_MAP()


// CRegManageDlg ��Ϣ�������

BOOL CRegManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	LONG lStyle = m_list.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	lStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
	m_list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0,(LPARAM)lStyle);
	LV_COLUMN lvc;
	
	lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH /*| LVCF_FMT*/;
	
	m_list.DeleteAllItems();
 	m_list.InsertColumn(0,"����",LVCFMT_LEFT,130);  
 	m_list.InsertColumn(1,"����",LVCFMT_LEFT,120);
 	m_list.InsertColumn(2,"ֵ",LVCFMT_LEFT,150);


	return true;

}

