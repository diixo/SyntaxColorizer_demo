// ColorizerDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ColorizerDemo.h"
#include "ColorizerDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorizerDemoApp

BEGIN_MESSAGE_MAP(CColorizerDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CColorizerDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorizerDemoApp construction

CColorizerDemoApp::CColorizerDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CColorizerDemoApp object

CColorizerDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CColorizerDemoApp initialization

BOOL CColorizerDemoApp::InitInstance()
{
	AfxEnableControlContainer();

	//Since there is a rich edit control in one or more of the dialog boxes,
	// 	AfxInitRichEdit() must be called
	AfxInitRichEdit();	

	CColorizerDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
