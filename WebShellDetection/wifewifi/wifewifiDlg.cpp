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
	((CTabCtrl *)GetDlgItem(IDC_TAB1))->InsertItem(0,"1.ˢ·����");
	((CTabCtrl *)GetDlgItem(IDC_TAB1))->InsertItem(1,"2.����·����");
	((CTabCtrl *)GetDlgItem(IDC_TAB1))->InsertItem(2,"3.����ע��");
	((CTabCtrl *)GetDlgItem(IDC_TAB1))->InsertItem(3,"4.�������");
	((CTabCtrl *)GetDlgItem(IDC_TAB1))->InsertItem(4,"����");
	UpdateData();
	m_welcome = "1.����������·������������һ��  (��ѡ)\r\n  ���������Ƕ��ֵģ������Ѿ�ʹ�ù�\r\n  �뽫·��������˵����ָ���������\r\n\r\n2.�������һͷ����·����WAN��\r\n  һͷ���ڵ�����\r\n  ����·��������\r\n  �ȴ�·���������ú�\r\n  ���ˢ����ť\r\n\r\n3.ע������:\r\n  ·����ˢ����������ǧ��Ҫ�ε�����\r\n  ����·������Դ��\r\n  �빺��·�����˷����Է�·����ˢ��ʧ��\r\n\r\n4.�ֶ�ˢ��  (��ѡ �������)\r\n  ������·�����������ϲ��費�����ˢ����\r\n  �����������ַ������192.168.1.1����\r\n  �û��������Ϊ: admin ��½\r\n  ���������ߵ�ϵͳ����->�������\r\n  ѡ��Ŀ¼�¶�Ӧ·�����ͺŵĹ̼�(��׺Ϊ.bin)\r\n  ������  \r\n  �ȴ�2��3���Ӻ� ·������ֹͣ��˸\r\n  �ٴη���192.168.1.1\r\n  ����ܽ���OpwnWrt���棬˵��ˢ���ɹ�";
	m_about = "������    ��·����ˢ������\r\n�汾      ��1.0\r\n��С      ��10MB\r\n����      ��www.wifewifi.com\r\n����      ������\r\n��ϵ��ʽ  ���ֻ�  ��17863137381\r\n            QQ    ��798523593\r\n������    ����������ҵ��ѧ(����)\r\n\r\n\r\nʹ��      ��\r\n      ���ڸ�����ѧУ԰����Ҫ���ţ�����û����Ӧ�Ĳ��ų�����˲���ʹ������·��������Ҿ�û��WiFi���ˣ�Ȼ��а���CMCC̫�󣬵����ֲ��ܲ��ã����Ŵ�ѧ���ǵ�Ѫ��Ǯ�������ڴ�غڰ��Ĵ�ʱ��������������û�����������������У԰�ͻ��ˣ����Ҽ���ļ�������·���������̣��ô����������ʹ��WiFi�ˣ���ʱ��ػָ��˹����������ڴ�ʱ����������WiFi�����\r\n\r\n    ��������ҲҪ�Է�����ҲҪ��ŮƱ��ҲҪ���������˱������շ��Ҳ���Դ���������������˿����ӿڣ����ҽ�����չ�������������һ�����㷨��ֹ�۸��ƽ⣬���������ߵ��Ͷ��ɹ�!\r\n\r\n�����򲻺����ƣ������������ڲ��õĽ������ȱ���������100���ĳ��򽫻���֣�����˼·�᳭Ϯ���������⽫����ʷ�ı�Ȼ��";
	m_regmessage = "δ���ע���·������������ʹ��30���ӻ��Զ��ػ�����\r\n����ˢ·���������ú�һ�У�ȷ�����������ٽ��й���\r\n�����������ѧУ��У԰���йأ���˸����˺���Ҫ���½��й���\r\n\r\n�۸�:��40\r\n\r\n����ʽ:\r\n֧����:17863137381\r\nQQǮ��ת��:798523593\r\n΢��ת��ID:oflyff";
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
	str.Format("%d.%d.%d.%d",a1,a2,a3,a4);//�����nf�õ���ֵ��IPֵ��.  
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
	m_registration = "��ע��";
	UpdateData(false);
	MessageBox(m_registrationcode);
	// TODO: Add your control notification handler code here
}

void CWifewifiDlg::OnJiance() 
{
	UpdateData();
	m_state1 = _T("ʧ��");
	m_state2 = _T("ʧ��");
	m_state3 = _T("ʧ��");
	m_state4 = _T("ʧ��");
	m_state5 = _T("ʧ��");
	m_state6 = _T("ʧ��");
	m_state7 = _T("ʧ��");
	m_state8 = _T("ʧ��");
	m_state9 = _T("ʧ��");
	m_state10 = _T("ʧ��");
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
