// ColorizerDemo.h : main header file for the COLORIZERDEMO application
//

#if !defined(AFX_COLORIZERDEMO_H__C4934CC4_E881_11D4_A61E_00FA59C1010C__INCLUDED_)
#define AFX_COLORIZERDEMO_H__C4934CC4_E881_11D4_A61E_00FA59C1010C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CColorizerDemoApp:
// See ColorizerDemo.cpp for the implementation of this class
//

class CColorizerDemoApp : public CWinApp
{
public:
	CColorizerDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorizerDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CColorizerDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORIZERDEMO_H__C4934CC4_E881_11D4_A61E_00FA59C1010C__INCLUDED_)
