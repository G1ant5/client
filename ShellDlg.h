#pragma once
#include "afxwin.h"


// CShellDlg �Ի���

class CShellDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShellDlg)

public:
	BOOL OnInitDialog();
	SOCKET ClientSocket;
	CShellDlg(SOCKET s,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShellDlg();

// �Ի�������
	enum { IDD = IDD_SHELL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_CmdEdit;
	CString m_cmd;
	CString	m_command;
	afx_msg void OnClickedExecute();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
