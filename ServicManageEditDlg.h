#pragma once
#include "afxwin.h"


// CServicManageEditDlg �Ի���

class CServicManageEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServicManageEditDlg)

public:
	BOOL OnInitDialog();
	SOCKET m_ClientSocket;

	CString  ServiceName;
	CString  ServiceState;
    CString  ServiceStartType;
	CServicManageEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CServicManageEditDlg();

// �Ի�������
	enum { IDD = IDD_SERVICE_MANAGE_SUB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combox_state;
	CComboBox m_combox_autoload;
};
