#pragma once
#include "afxcmn.h"


// CRegManageDlg �Ի���

class CRegManageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegManageDlg)

public:
	BOOL OnInitDialog();
	SOCKET ClientSocket;
	CRegManageDlg(SOCKET s,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegManageDlg();

// �Ի�������
	enum { IDD = IDD_REG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	CTreeCtrl m_tree;
};
