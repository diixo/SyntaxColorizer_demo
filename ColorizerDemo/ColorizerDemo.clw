; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CColorizerDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ColorizerDemo.h"

ClassCount=3
Class1=CColorizerDemoApp
Class2=CColorizerDemoDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_COLORIZERDEMO_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDD_COLORIZERDEMO_DIALOG (English (U.S.))
Resource6=IDR_MENU1

[CLS:CColorizerDemoApp]
Type=0
HeaderFile=ColorizerDemo.h
ImplementationFile=ColorizerDemo.cpp
Filter=N

[CLS:CColorizerDemoDlg]
Type=0
HeaderFile=ColorizerDemoDlg.h
ImplementationFile=ColorizerDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_APP_ABOUT

[CLS:CAboutDlg]
Type=0
HeaderFile=ColorizerDemoDlg.h
ImplementationFile=ColorizerDemoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_COLORIZERDEMO_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CColorizerDemoDlg

[DLG:IDD_COLORIZERDEMO_DIALOG (English (U.S.))]
Type=1
Class=CColorizerDemoDlg
ControlCount=6
Control1=IDCANCEL,button,1342242816
Control2=IDC_RICHEDIT1,RICHEDIT,1353781444
Control3=IDC_BFORMAT,button,1342242816
Control4=IDC_BCOMMENT,button,1342242816
Control5=IDC_BKEYWORDS,button,1342242816
Control6=IDC_BDIRECTIVES,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_APP_EXIT
Command3=ID_APP_ABOUT
CommandCount=3

