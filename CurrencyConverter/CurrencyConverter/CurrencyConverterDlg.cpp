#include "stdafx.h"
#include "CurrencyConverter.h"
#include "CurrencyConverterDlg.h"
#include "Downloader.h"
#include "afxdialogex.h"


#include <string>
#include <list>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCurrencyConverterDlg dialog

CCurrencyConverterDlg::CCurrencyConverterDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CURRENCYCONVERTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCurrencyConverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, editValue);
	DDX_Control(pDX, IDC_LIST2, currencyList);
}

BEGIN_MESSAGE_MAP(CCurrencyConverterDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2_CONVERT, &CCurrencyConverterDlg::OnBnClickedButton2Convert)
	ON_EN_CHANGE(IDC_EDIT1, &CCurrencyConverterDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()

// CCurrencyConverterDlg message handlers

void CCurrencyConverterDlg::AddColumnsName() {
	int index = 0;
	currencyList.InsertColumn(index++, _T("Currency"), LVCFMT_CENTER, 75);
	currencyList.InsertColumn(index++, _T("Value"), LVCFMT_CENTER, 83);
}

BOOL CCurrencyConverterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	editValue.ModifyStyle(0, ES_NUMBER);
	this->AddColumnsName();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCurrencyConverterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCurrencyConverterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCurrencyConverterDlg::OnBnClickedButton2Convert()
{
	/*CString value;
	GetDlgItemText(IDC_EDIT1, value);
	SetDlgItemText(IDC_EDIT2, value);*/
	
	Downloader down;
	down.DownloadContent();

	if (down.IsContentDownloaded()) {
		std::string a = down.GetContent();
		MessageBox(_T("da"));
	}
	else {
		MessageBox(_T("ne "));
	}
}


void CCurrencyConverterDlg::OnEnChangeEdit1()
{
	CString value;
	GetDlgItemText(IDC_EDIT1, value);
	
	CWnd *btnConvert = GetDlgItem(IDC_BUTTON2_CONVERT);
	if (value.IsEmpty()) {
		btnConvert->EnableWindow(FALSE);
	}
	else {
		btnConvert->EnableWindow(TRUE);
	}
}