#pragma once


// VideoManage �Ի���

class CVideoManage : public CDialogEx
{
//	DECLARE_DYNAMIC(CVideoManage)

public:
	SOCKET ClientSocket;
	CVideoManage(SOCKET s,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVideoManage();

// �Ի�������
	enum { IDD = IDD_VIDEO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
