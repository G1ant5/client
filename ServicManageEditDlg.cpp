// ServicManageEditDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "ServicManageEditDlg.h"
#include "afxdialogex.h"


// CServicManageEditDlg �Ի���

IMPLEMENT_DYNAMIC(CServicManageEditDlg, CDialogEx)

CServicManageEditDlg::CServicManageEditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServicManageEditDlg::IDD, pParent)
{

}

CServicManageEditDlg::~CServicManageEditDlg()
{
}

void CServicManageEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combox_state);
	DDX_Control(pDX, IDC_COMBO2, m_combox_autoload);
}


BEGIN_MESSAGE_MAP(CServicManageEditDlg, CDialogEx)
END_MESSAGE_MAP()


// CServicManageEditDlg ��Ϣ�������


BOOL CServicManageEditDlg::OnInitDialog()
{
	
	CDialog::OnInitDialog();
 
    SetDlgItemText(IDC_STATIC_NAME,ServiceName);	
	SetDlgItemText(IDC_STATIC_STATE,ServiceState);	
	SetDlgItemText(IDC_STATIC_TYPE,ServiceStartType);	

/*
	    m_combox_state.AddString("����");
		m_combox_state.AddString("ͣ��");
		
		m_combox_autoload.AddString("�Զ�");
	    m_combox_autoload.AddString("�ֶ�");
		m_combox_autoload.AddString("ͣ��");
*/
	

	return TRUE;

}
