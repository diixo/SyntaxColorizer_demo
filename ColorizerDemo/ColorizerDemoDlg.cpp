// ColorizerDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ColorizerDemo.h"
#include "ColorizerDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// File interaction, 
DWORD CALLBACK readFunction(DWORD dwCookie,
							 LPBYTE lpBuf,	//the buffer to write
							 LONG nCount,	//the no. of bytes to write
							 LONG* nWritten); // no. of bytes written

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorizerDemoDlg dialog

CColorizerDemoDlg::CColorizerDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorizerDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorizerDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorizerDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorizerDemoDlg)
	DDX_Control(pDX, IDC_BDIRECTIVES, m_cDirective);
	DDX_Control(pDX, IDC_BKEYWORDS, m_cKeyword);
	DDX_Control(pDX, IDC_BCOMMENT, m_cComment);
	DDX_Control(pDX, IDC_BFORMAT, m_cFormat);
	DDX_Control(pDX, IDCANCEL, m_cCancel);
	DDX_Control(pDX, IDC_RICHEDIT1, m_cSyntax);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CColorizerDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CColorizerDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_EN_CHANGE(IDC_RICHEDIT1, OnChangeRichedit1)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BFORMAT, OnBformat)
	ON_BN_CLICKED(IDC_BCOMMENT, OnBcomment)
	ON_BN_CLICKED(IDC_BKEYWORDS, OnBkeywords)
	ON_BN_CLICKED(IDC_BDIRECTIVES, OnBdirectives)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorizerDemoDlg message handlers

BOOL CColorizerDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// setup the menu
	m_mainMenu.LoadMenu(MAKEINTRESOURCE(IDR_MENU1));
	SetMenu(&m_mainMenu);
	m_mainMenu.Detach();

	m_sDir = STR_INITDIR;

	//set the locations and sizes of the controls
	RECT r;
	this->GetClientRect(&r);
	setSizes(r.right,r.bottom);// sends the width and height of the dlg box

	//set the event mask to accept ENM_CHANGE messages
	long mask = m_cSyntax.GetEventMask();
	m_cSyntax.SetEventMask(mask |= ENM_CHANGE );

   parse2();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CColorizerDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CColorizerDemoDlg::OnAppAbout() 
{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
}

// other functions

void CColorizerDemoDlg::readFile(CString sFileName)
{
	m_cSyntax.SetRedraw(FALSE);
	
	CFile file(sFileName,CFile::modeReadWrite|CFile::typeBinary);
	m_es.dwCookie = (DWORD)&file;
	m_es.pfnCallback = readFunction;
	m_cSyntax.StreamIn(SF_TEXT,m_es);
	file.Close();

	parse();

}

DWORD CALLBACK readFunction(DWORD dwCookie,
							 LPBYTE lpBuf,	//the buffer to fill
							 LONG nCount,	//the no. of bytes to read
							 LONG* nRead) // no. of bytes read
{
	CFile* fp = (CFile *)dwCookie;
	*nRead = fp->Read(lpBuf,nCount);
	return 0;
}

void CColorizerDemoDlg::parse()
{
	//turn off response to onchange events
	long mask = m_cSyntax.GetEventMask();
	m_cSyntax.SetEventMask(mask ^= ENM_CHANGE );

	//set redraw to false to reduce flicker, and to speed things up
	m_cSyntax.SetRedraw(FALSE);

	//call the colorizer
	sc.Colorize(0, -1, &m_cSyntax);

	//do some cleanup
	m_cSyntax.SetSel(0,0);
	m_cSyntax.SetRedraw(TRUE);
	m_cSyntax.RedrawWindow();

	m_cSyntax.SetEventMask(mask |= ENM_CHANGE );
}

void CColorizerDemoDlg::parse2()
{
	//get the current line of text from the control
	int len = m_cSyntax.LineLength();
	int start = m_cSyntax.LineIndex();

	//call the colorizer
	sc.Colorize(start,start + len,&m_cSyntax);
}

void CColorizerDemoDlg::setSizes(int cx, int cy)
{
	RECT r;

	//set coordinates for rich edit box
	r.left = XY_EDITLEFT; 
	r.top = XY_TOP;
	r.right = cx - XY_BORDER;
	r.bottom = cy - XY_BOTTOM;
	m_cSyntax.MoveWindow(&r);

	//set coordinates for Cancel button
	r.left = cx - XY_BORDER - XY_BUTTONWIDTH; 
	r.top = cy - XY_BOTTOM + XY_GAP;
	r.right = cx - XY_BORDER;
	r.bottom = cy - XY_BORDER;
	m_cCancel.MoveWindow(&r);

	//set coordinates for Format button
	r.left = cx - XY_BORDER - (3 * XY_BUTTONWIDTH) - (2 * XY_GAP); 
	r.top = cy - XY_BOTTOM + XY_GAP;
	r.right = cx - XY_BORDER - (2 * XY_BUTTONWIDTH) - (2 * XY_GAP);
	r.bottom = cy - XY_BORDER;
	m_cFormat.MoveWindow(&r);

	//set coordinates for Comments button
	r.left = cx - XY_BORDER - (4 * XY_BUTTONWIDTH) - (3 * XY_GAP); 
	r.top = cy - XY_BOTTOM + XY_GAP;
	r.right = cx - XY_BORDER - (3 * XY_BUTTONWIDTH) - (3 * XY_GAP);
	r.bottom = cy - XY_BORDER;
	m_cComment.MoveWindow(&r);

	//set coordinates for Keywords button
	r.left = cx - XY_BORDER - (5 * XY_BUTTONWIDTH) - (4 * XY_GAP); 
	r.top = cy - XY_BOTTOM + XY_GAP;
	r.right = cx - XY_BORDER - (4 * XY_BUTTONWIDTH) - (4 * XY_GAP);
	r.bottom = cy - XY_BORDER;
	m_cKeyword.MoveWindow(&r);

	//set coordinates for Compiler directives button
	r.left = cx - XY_BORDER - (6 * XY_BUTTONWIDTH) - (5 * XY_GAP); 
	r.top = cy - XY_BOTTOM + XY_GAP;
	r.right = cx - XY_BORDER - (5 * XY_BUTTONWIDTH) - (5 * XY_GAP);
	r.bottom = cy - XY_BORDER;
	m_cDirective.MoveWindow(&r);

}

void CColorizerDemoDlg::OnChangeRichedit1() 
{
	CHARRANGE cr;
	m_cSyntax.GetSel(cr);
	parse2();
	m_cSyntax.SetSel(cr);
}

void CColorizerDemoDlg::OnFileOpen() 
{
	CFileDialog fd(TRUE);		//construct a File Open dialog

	fd.m_ofn.lpstrFilter = STR_FILTER;
	fd.m_ofn.lpstrInitialDir = m_sDir;
	if(fd.DoModal() == IDOK)
	{
		readFile(fd.GetPathName());
		m_sDir = fd.GetPathName();
		m_sDir.Replace(fd.GetFileName(),"");
	}

	m_cSyntax.SetFocus();
	
}

void CColorizerDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if(m_cSyntax.GetSafeHwnd()) setSizes(cx,cy);
}

void CColorizerDemoDlg::OnBformat() 
{
	parse();
//	MessageBox(sc.GetKeywordList());
}

void CColorizerDemoDlg::OnBcomment() 
{
	static int nChange = 0;
	CHARFORMAT cf;
	CString str;
	sc.GetCommentStyle(cf);
	switch(nChange)
	{
	case 0:
		MessageBox("Change comment style to YELLOW ITALIC");
		cf.dwMask = CFM_ITALIC | CFM_COLOR;
		cf.dwEffects = CFE_ITALIC;
		cf.crTextColor = RGB(255,255,0);
		sc.SetCommentStyle(cf);
		nChange++;
		break;
	case 1:
		MessageBox("Change comment font to RED Arial");
		cf.dwMask = CFM_FACE | CFM_COLOR;
		cf.crTextColor = RGB(255,0,0);
		strcpy(cf.szFaceName,"Arial");
		sc.SetCommentStyle(cf);
		nChange++;
		break;
	case 2:
		MessageBox("Restore comment style");
		cf.dwMask = CFM_COLOR;
		cf.dwEffects = 0;
		cf.crTextColor = RGB(0,170,0);
		sc.SetCommentStyle(cf);
		nChange = 0;
		break;
	}
	parse();
}

void CColorizerDemoDlg::OnBkeywords() 
{
	static int nChange = 0;
	CHARFORMAT cf;
	sc.GetGroupStyle(42,cf);
	switch(nChange)
	{
	case 0:
		MessageBox("Change keywords to MAGENTA");
		cf.dwMask = CFM_COLOR;
		cf.dwEffects = 0;
		cf.crTextColor = RGB(255,0,255);
		sc.SetGroupStyle(GRP_KEYWORD,cf);
		nChange++;
		break;
	case 1:
		MessageBox("Change keywords to CYAN STRIKEOUT");
		cf.dwMask = CFM_COLOR | CFM_STRIKEOUT;
		cf.dwEffects = CFE_STRIKEOUT;
		cf.crTextColor = RGB(0,255,255);
		sc.SetGroupStyle(GRP_KEYWORD,cf);
		nChange++;
		break;
	case 2:
		MessageBox("Restore keywords");
		cf.dwMask = CFM_COLOR;
		cf.dwEffects = 0;
		cf.crTextColor = RGB(0,0,255);
		sc.SetGroupStyle(GRP_KEYWORD,cf);
		nChange = 0;
		break;
	}
	parse();
}

void CColorizerDemoDlg::OnBdirectives() 
{
	static int nChange = 0;
	CHARFORMAT cf;
	sc.GetGroupStyle(GRP_DIRECTIVE,cf);
	switch(nChange)
	{
	case 0:
		MessageBox("Change Compiler Directives to RED");
		cf.dwMask = CFM_COLOR;
		cf.dwEffects = 0;
		cf.crTextColor = RGB(255,0,0);
		sc.SetGroupStyle(GRP_DIRECTIVE,cf);
		nChange++;
		break;
	case 1:
		MessageBox("Change Compiler Directives to BOLD UNDERLINE");
		cf.dwMask = CFM_BOLD | CFM_UNDERLINE | CFM_COLOR;
		cf.dwEffects = CFE_BOLD | CFE_UNDERLINE;
		cf.crTextColor = RGB(255,0,0);
		sc.SetGroupStyle(GRP_DIRECTIVE,cf);
		nChange++;
		break;
	case 2:
		MessageBox("Restore Compiler Directives");
		cf.dwMask = CFM_COLOR;
		cf.dwEffects = 0;
		cf.crTextColor = RGB(0,0,255);
		sc.SetGroupStyle(GRP_DIRECTIVE,cf);
		nChange = 0;
		break;
	}
	parse();
}

