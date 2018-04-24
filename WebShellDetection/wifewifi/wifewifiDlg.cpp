// wifewifiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wifewifi.h"
#include "wifewifiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWifewifiDlg dialog

CWifewifiDlg::CWifewifiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWifewifiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWifewifiDlg)
	m_message = _T("");
	m_wifiname = _T("");
	m_wifipassword = _T("");
	m_networkacount = _T("");
	m_networkpassword = _T("");
	m_machinecode = _T("");
	m_registrationcode = _T("");
	m_error = _T("");
	m_welcome = _T("");
	m_about = _T("");
	m_regmessage = _T("");
	m_school = _T("");
	m_model = _T("");
	m_state1 = _T("");
	m_state10 = _T("");
	m_state2 = _T("");
	m_state3 = _T("");
	m_state4 = _T("");
	m_state5 = _T("");
	m_state6 = _T("");
	m_state7 = _T("");
	m_state8 = _T("");
	m_state9 = _T("");
	m_registration = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CWifewifiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWifewifiDlg)
	DDX_Control(pDX, IDC_IPADDRESS5, m_dns2);
	DDX_Control(pDX, IDC_IPADDRESS4, m_dns1);
	DDX_Control(pDX, IDC_IPADDRESS3, m_gateway);
	DDX_Control(pDX, IDC_IPADDRESS2, m_subnetmask);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipaddress);
	DDX_Text(pDX, IDC_EDIT1, m_message);
	DDX_Text(pDX, IDC_EDIT4, m_wifiname);
	DDX_Text(pDX, IDC_EDIT5, m_wifipassword);
	DDX_Text(pDX, IDC_EDIT6, m_networkacount);
	DDX_Text(pDX, IDC_EDIT7, m_networkpassword);
	DDX_Text(pDX, IDC_EDIT8, m_machinecode);
	DDX_Text(pDX, IDC_EDIT9, m_registrationcode);
	DDX_Text(pDX, IDC_EDIT10, m_error);
	DDX_Text(pDX, IDC_EDIT2, m_welcome);
	DDX_Text(pDX, IDC_EDIT3, m_about);
	DDX_Text(pDX, IDC_EDIT11, m_regmessage);
	DDX_CBString(pDX, IDC_COMBO2, m_school);
	DDX_CBString(pDX, IDC_COMBO1, m_model);
	DDX_Text(pDX, IDC_STATE1, m_state1);
	DDX_Text(pDX, IDC_STATE10, m_state10);
	DDX_Text(pDX, IDC_STATE2, m_state2);
	DDX_Text(pDX, IDC_STATE3, m_state3);
	DDX_Text(pDX, IDC_STATE4, m_state4);
	DDX_Text(pDX, IDC_STATE5, m_state5);
	DDX_Text(pDX, IDC_STATE6, m_state6);
	DDX_Text(pDX, IDC_STATE7, m_state7);
	DDX_Text(pDX, IDC_STATE8, m_state8);
	DDX_Text(pDX, IDC_STATE9, m_state9);
	DDX_Text(pDX, IDC_ZHUCE3, m_registration);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWifewifiDlg, CDialog)
	//{{AFX_MSG_MAP(CWifewifiDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_BN_CLICKED(IDC_SHUAJI, OnShuaji)
	ON_BN_CLICKED(IDC_PEIZHI, OnPeizhi)
	ON_BN_CLICKED(IDC_ZHUCE, OnZhuce)
	ON_BN_CLICKED(IDC_JIANCE, OnJiance)
	ON_BN_CLICKED(IDC_GUANWANG, OnGuanwang)
	ON_BN_CLICKED(IDC_SHENGJI, OnShengji)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWifewifiDlg message handlers

BOOL CWifewifiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//((CTabCtrl *)GetDlgItem(IDC_TAB1))->DeleteItem(0);
	((CTabCtrl *)GetDlgItem(IDC_TAB1))->InsertItem(0,"1.刷路由器");
	((CTabCtrl *)GetDlgItem(IDC_TAB1))->InsertItem(1,"2.配置路由器");
	((CTabCtrl *)GetDlgItem(IDC_TAB1))->InsertItem(2,"3.购买注册");
	((CTabCtrl *)GetDlgItem(IDC_TAB1))->InsertItem(3,"4.解决问题");
	((CTabCtrl *)GetDlgItem(IDC_TAB1))->InsertItem(4,"关于");
	UpdateData();
	m_welcome = "1.如果是新买的路由器请跳过这一步  (可选)\r\n  如果你买的是二手的，或者已经使用过\r\n  请将路由器按照说明书恢复出场设置\r\n\r\n2.请把网线一头插在路由器WAN口\r\n  一头插在电脑上\r\n  并给路由器供电\r\n  等待路由器启动好后\r\n  点击刷机按钮\r\n\r\n3.注意事项:\r\n  路由器刷机过程中请千万不要拔掉网线\r\n  或者路由器电源线\r\n  请购买路由器运费险以防路由器刷机失败\r\n\r\n4.手动刷机  (可选 特殊情况)\r\n  如果你的路由器按照以上步骤不能完成刷机，\r\n  请在浏览器地址栏输入192.168.1.1进入\r\n  用户和密码均为: admin 登陆\r\n  点击窗口左边的系统工具->软件升级\r\n  选择本目录下对应路由器型号的固件(后缀为.bin)\r\n  点升级  \r\n  等待2到3分钟后 路由器灯停止闪烁\r\n  再次访问192.168.1.1\r\n  如果能进入OpwnWrt界面，说明刷机成功";
	m_about = "程序名    ：路由器刷机工具\r\n版本      ：1.0\r\n大小      ：10MB\r\n官网      ：www.wifewifi.com\r\n作者      ：殷悦\r\n联系方式  ：手机  ：17863137381\r\n            QQ    ：798523593\r\n出生地    ：哈尔滨工业大学(威海)\r\n\r\n\r\n使命      ：\r\n      由于各个大学校园网需要拨号，但是没有相应的拨号程序，因此不能使用无线路由器，大家就没有WiFi用了，然而邪恶的CMCC太贵，但是又不能不用，吸着大学生们的血汗钱，但是在大地黑暗的此时，善良正义的殷悦化作光明，制作出了校园客户端，并且极大的简化了配置路由器的流程，让大家鼠标点点就能使用WiFi了，此时大地恢复了光明，人们在此时尽情享受着WiFi的生活！\r\n\r\n    由于作者也要吃饭饭，也要找女票，也要享受生活，因此本程序收费且不开源，但是作者留出了开发接口，请大家进行扩展，本程序采用了一定的算法防止篡改破解，请尊重作者的劳动成果!\r\n\r\n本程序不很完善，但宝宝相信在不久的将来，比本程序完善100倍的程序将会出现，但是思路会抄袭本宝宝，这将是历史的必然！";
	m_regmessage = "未完成注册的路由器，开启后使用30分钟会自动关机断网\r\n请先刷路由器，配置好一切，确保能上网后再进行购买\r\n机器码与你的学校与校园网有关，因此更换账号需要重新进行购买\r\n\r\n价格:￥40\r\n\r\n购买方式:\r\n支付宝:17863137381\r\nQQ钱包转账:798523593\r\n微信转账ID:oflyff";
	CWifewifiDlg::FlushDialog();
	UpdateData(false);
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWifewifiDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWifewifiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CWifewifiDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CWifewifiDlg::FlushDialog();
	*pResult = 0;
}
void CWifewifiDlg::FlushDialog()
{
	GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_SHUAJI)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PEIZHI)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PEIZHI1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PEIZHI2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PEIZHI3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PEIZHI4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_IPADDRESS1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_IPADDRESS2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_IPADDRESS3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_IPADDRESS4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_IPADDRESS5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ZHUCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ZHUCE1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ZHUCE2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ZHUCE3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ZHUCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT11)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_JIANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_JIANCE1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_JIANCE2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATE1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATE2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATE3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATE4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATE5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATE6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATE7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATE8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATE9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATE10)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT10)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GUANWANG)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_SHENGJI)->ShowWindow(SW_HIDE);
	switch(((CTabCtrl *)GetDlgItem(IDC_TAB1))->GetCurSel())
	{
	case 0:
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SHUAJI)->ShowWindow(SW_SHOW);
		break;
	case 1:
		GetDlgItem(IDC_PEIZHI)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PEIZHI1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PEIZHI2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PEIZHI3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PEIZHI4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_IPADDRESS1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_IPADDRESS2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_IPADDRESS3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_IPADDRESS4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_IPADDRESS5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_SHOW);
		break;
	case 2:
		GetDlgItem(IDC_ZHUCE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ZHUCE1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ZHUCE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ZHUCE3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT9)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ZHUCE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT11)->ShowWindow(SW_SHOW);
		break;
	case 3:
		GetDlgItem(IDC_JIANCE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_JIANCE1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_JIANCE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATE1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATE3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATE4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATE5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATE6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATE7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATE8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATE9)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATE10)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT10)->ShowWindow(SW_SHOW);
		break;
	case 4:
		GetDlgItem(IDC_EDIT3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GUANWANG)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SHENGJI)->ShowWindow(SW_SHOW);
		break;
	}
}
void CWifewifiDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here

	((CTabCtrl *)GetDlgItem(IDC_TAB1))->DeleteItem(1);

}

void CWifewifiDlg::OnShuaji() 
{
	// TODO: Add your control notification handler code here
	
}

void CWifewifiDlg::OnPeizhi() 
{
	// TODO: Add your control notification handler code here
	/*
	BYTE a1,a2,a3,a4;  
	m_ip.GetAddress(a1,a2,a3,a4);  
	CString str;  
	str.Format("%d.%d.%d.%d",a1,a2,a3,a4);//这里的nf得到的值是IP值了.  
	MessageBox(str);  
	*/
	BYTE IP[4];
	CString str;
	UpdateData();
	m_ipaddress.GetAddress(IP[0], IP[1], IP[2], IP[3]);
	str.Format("%d.%d.%d.%d",IP[0],IP[1],IP[2],IP[3]);
	m_message = m_wifiname + m_wifipassword + m_networkacount + m_networkpassword + m_school + str;
	MessageBox(m_school);
	UpdateData(false);
}

void CWifewifiDlg::OnZhuce() 
{
	UpdateData();
	m_machinecode = "123123123";
	m_registration = "已注册";
	UpdateData(false);
	MessageBox(m_registrationcode);
	// TODO: Add your control notification handler code here
}

void CWifewifiDlg::OnJiance() 
{
	UpdateData();
	m_state1 = _T("失败");
	m_state2 = _T("失败");
	m_state3 = _T("失败");
	m_state4 = _T("失败");
	m_state5 = _T("失败");
	m_state6 = _T("失败");
	m_state7 = _T("失败");
	m_state8 = _T("失败");
	m_state9 = _T("失败");
	m_state10 = _T("失败");
	UpdateData(false);
	// TODO: Add your control notification handler code here
	
}

void CWifewifiDlg::OnGuanwang() 
{
	// TODO: Add your control notification handler code here
	
}

void CWifewifiDlg::OnShengji() 
{
	// TODO: Add your control notification handler code here
	
}
