// wifewifiDlg.h : header file
//

#if !defined(AFX_WIFEWIFIDLG_H__00CFD5E1_CFB2_4610_9994_6A4FC3ACCC2B__INCLUDED_)
#define AFX_WIFEWIFIDLG_H__00CFD5E1_CFB2_4610_9994_6A4FC3ACCC2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWifewifiDlg dialog

class CWifewifiDlg : public CDialog
{
// Construction
public:
	CWifewifiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWifewifiDlg)
	enum { IDD = IDD_WIFEWIFI_DIALOG };
	CIPAddressCtrl	m_dns2;
	CIPAddressCtrl	m_dns1;
	CIPAddressCtrl	m_gateway;
	CIPAddressCtrl	m_subnetmask;
	CIPAddressCtrl	m_ipaddress;
	CString	m_message;
	CString	m_wifiname;
	CString	m_wifipassword;
	CString	m_networkacount;
	CString	m_networkpassword;
	CString	m_machinecode;
	CString	m_registrationcode;
	CString	m_error;
	CString	m_welcome;
	CString	m_about;
	CString	m_regmessage;
	CString	m_school;
	CString	m_model;
	CString	m_state1;
	CString	m_state10;
	CString	m_state2;
	CString	m_state3;
	CString	m_state4;
	CString	m_state5;
	CString	m_state6;
	CString	m_state7;
	CString	m_state8;
	CString	m_state9;
	CString	m_registration;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWifewifiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWifewifiDlg)
	void FlushDialog();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton2();
	afx_msg void OnShuaji();
	afx_msg void OnPeizhi();
	afx_msg void OnZhuce();
	afx_msg void OnJiance();
	afx_msg void OnGuanwang();
	afx_msg void OnShengji();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIFEWIFIDLG_H__00CFD5E1_CFB2_4610_9994_6A4FC3ACCC2B__INCLUDED_)
