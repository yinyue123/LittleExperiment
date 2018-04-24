// wifewifi.h : main header file for the WIFEWIFI application
//

#if !defined(AFX_WIFEWIFI_H__9A36B2A4_B21A_4698_8D6F_561033DD0D3E__INCLUDED_)
#define AFX_WIFEWIFI_H__9A36B2A4_B21A_4698_8D6F_561033DD0D3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWifewifiApp:
// See wifewifi.cpp for the implementation of this class
//

class CWifewifiApp : public CWinApp
{
public:
	CWifewifiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWifewifiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWifewifiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIFEWIFI_H__9A36B2A4_B21A_4698_8D6F_561033DD0D3E__INCLUDED_)
