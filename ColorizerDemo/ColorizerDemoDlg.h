// ColorizerDemoDlg.h : header file
//

#if !defined(AFX_COLORIZERDEMODLG_H__C4934CC6_E881_11D4_A61E_00FA59C1010C__INCLUDED_)
#define AFX_COLORIZERDEMODLG_H__C4934CC6_E881_11D4_A61E_00FA59C1010C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SyntaxColorizer.h"

#define STR_FILTER "C++ Source Files\0*.cpp;\0Header Files\0*.h\0\0"
//#define STR_INITDIR "C:\\My Documents"
#define STR_INITDIR "C:\\Program Files\\Microsoft Visual Studio\\VC98\\MFC\\SRC"
#define GRP_KEYWORD		0
#define GRP_PRAGMA		1
#define GRP_DIRECTIVE	2

#define XY_BORDER		10
#define XY_BUTTONWIDTH	80
#define XY_BUTTONHEIGHT 50
#define XY_EDITLEFT		10
#define XY_TOP			10
#define XY_GAP			10	
#define XY_BOTTOM		50

/////////////////////////////////////////////////////////////////////////////
// CColorizerDemoDlg dialog

class CColorizerDemoDlg : public CDialog
{
// Construction
public:
	CColorizerDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CColorizerDemoDlg)
	enum { IDD = IDD_COLORIZERDEMO_DIALOG };
	CButton	m_cDirective;
	CButton	m_cKeyword;
	CButton	m_cComment;
	CButton	m_cFormat;
	CButton	m_cCancel;
	CRichEditCtrl	m_cSyntax;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorizerDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CColorizerDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnChangeRichedit1();
	afx_msg void OnFileOpen();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBformat();
	afx_msg void OnBchange();
	afx_msg void OnBcomment();
	afx_msg void OnBkeywords();
	afx_msg void OnBdirectives();
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CMenu m_mainMenu;
	EDITSTREAM m_es;
	CSyntaxColorizer sc;
	CString m_sDir;

	void readFile(CString sFileName);
	void parse();
	void parse2();
	void setSizes(int cx, int cy);
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORIZERDEMODLG_H__C4934CC6_E881_11D4_A61E_00FA59C1010C__INCLUDED_)
