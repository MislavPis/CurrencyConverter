#include "stdafx.h"
#include "CurrencyConverter.h"
#include "CurrencyConverterDlg.h"
#include "Downloader.h"
#include "DateWorker.h"
#include "XmlParser.h"
#include "afxdialogex.h"
#include "AboutDialog.h"

#include "pugiXML/pugixml.hpp"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCurrencyConverterDlg dialog

CCurrencyConverterDlg::CCurrencyConverterDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CURRENCYCONVERTER_DIALOG, pParent), canConvert(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCurrencyConverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, editValue);
	DDX_Control(pDX, IDC_LIST2, currencyList);
	DDX_Control(pDX, IDC_EDIT3, timeEdit);
	DDX_Control(pDX, IDC_COMBO1, currencyFrom);
	DDX_Control(pDX, IDC_COMBO2, currencyTo);
}

BEGIN_MESSAGE_MAP(CCurrencyConverterDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2_CONVERT, &CCurrencyConverterDlg::OnBnClickedButton2Convert)
	ON_EN_CHANGE(IDC_EDIT1, &CCurrencyConverterDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1_REFRESH, &CCurrencyConverterDlg::OnBnClickedButton1Refresh)
	ON_BN_CLICKED(IDC_BUTTON3_EXIT, &CCurrencyConverterDlg::OnBnClickedButton3Exit)
	ON_BN_CLICKED(IDC_BUTTON1, &CCurrencyConverterDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// CCurrencyConverterDlg message handlers
CString CCurrencyConverterDlg::GetStringFromMap(int stringID) {
	CString string;
	if (string.LoadString(stringID))
		return string;

	return _T("");
}

void CCurrencyConverterDlg::CheckButtonState(int componentID, bool enable) {
	CWnd *btnRefresh = GetDlgItem(componentID);
	btnRefresh->EnableWindow(enable);
}

void CCurrencyConverterDlg::InsertCurrencyIntoList() {
	int numberOfInsertedElements = this->currencyList.GetItemCount();

	std::map<CString, float>::iterator it = currencyMap.begin();
	for (; it != currencyMap.end(); ++it) {
		CString currency = it->first;
		CString exchangeRate((std::to_string(it->second)).c_str());

		this->currencyList.InsertItem(numberOfInsertedElements, currency);
		this->currencyList.SetItemText(numberOfInsertedElements++, 1, exchangeRate);
	}
}

void CCurrencyConverterDlg::PrepareCurrencyList() {
	this->AddColumnsName();
	this->DownloadCurrency();
}

void CCurrencyConverterDlg::UnsuccessfulDownload() {
	MessageBox(this->GetStringFromMap(IDS_FAIL_LOAD));
	this->CheckButtonState(IDC_BUTTON1_REFRESH, true);
}

void CCurrencyConverterDlg::FillComboCurrency(CComboBox& component) {
	for (const auto& key : currencyMap) {
		component.AddString(key.first);
	}

	component.SetCurSel(component.FindStringExact(0, _T("EUR")));
}

void CCurrencyConverterDlg::PrepareCombos() {
	this->FillComboCurrency(currencyFrom);
	this->FillComboCurrency(currencyTo);
}

float CCurrencyConverterDlg::ConvertValue(const CString& currencyFrom, const CString& currencyTo, const float value)
{
	if (currencyFrom.CompareNoCase(currencyTo) == 0) return value;

	float currencyFromRate = this->currencyMap[currencyFrom];
	float currencyToRate = this->currencyMap[currencyTo];

	float oneEuro = 1 / currencyFromRate;
	float valueInEuro = value * oneEuro;
	float valueInTargetCurrency = valueInEuro * currencyToRate;

	return valueInTargetCurrency;
}

void CCurrencyConverterDlg::DownloadCurrency() {
	std::string content(DownloadContent());

	if (!content.empty()) {
		std::pair< std::map<CString, float>, CString> data =  CreateXmlFromString(content);

		if (!data.first.empty()) {
			currencyMap = data.first;
			currencyMap.insert(std::pair<CString, float>("EUR", 1));			

			this->InsertCurrencyIntoList();
			//this->CheckButtonState(IDC_BUTTON1_REFRESH);
			this->PrepareCombos();

			SetDlgItemText(IDC_EDIT3, this->GetStringFromMap(IDS_LAST_UPDATE) + " " + Format(data.second));
			this->canConvert = true;
		}

	}
	else {
		this->UnsuccessfulDownload();
	}
}

void CCurrencyConverterDlg::AddColumnsName() {
	int index = 0;
	currencyList.InsertColumn(index++, this->GetStringFromMap(IDS_CURRENCY), LVCFMT_CENTER, 80);
	currencyList.InsertColumn(index++, this->GetStringFromMap(IDS_RATE), LVCFMT_CENTER, 143);

	currencyList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
}

BOOL CCurrencyConverterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	this->PrepareCurrencyList();
	
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

bool CCurrencyConverterDlg::IsInputValid(const CString& value) {
	int numberOfDots = 0;

	if ((value[0] == L'0' && value.GetLength() > 1) || value[0] == L'.' && value.GetLength() == 1) return false;

	for (int i = 0; i < value.GetLength(); ++i) {
		wchar_t letter = value[i];
		if (letter == L'.')
			++numberOfDots;
		else if (letter < L'0' || letter > L'9')
			return false;
	}

	if (numberOfDots > 1) return false;

	return true;
}


void CCurrencyConverterDlg::OnBnClickedButton2Convert()
{
	if (!canConvert) {
		MessageBox(this->GetStringFromMap(IDS_NOT_LOADED));
		return;
	}

	CString value;
	GetDlgItemText(IDC_EDIT1, value);

	if (this->IsInputValid(value)) {
		CString currencyFrom;
		CString currencyTo; 

		GetDlgItemText(IDC_COMBO1, currencyFrom);
		GetDlgItemText(IDC_COMBO2, currencyTo);

		float calculatedValue = this->ConvertValue(currencyFrom, currencyTo, _ttof(value));
		CString calculatedValueString((std::to_wstring(calculatedValue)).c_str());

		SetDlgItemText(IDC_EDIT2, value + _T(" ") + currencyFrom + _T(" = ") + calculatedValueString + _T(" ") + currencyTo);
	}
	else {
		MessageBox(this->GetStringFromMap(IDS_INSERT_VALID_NUMBER));
	}
}




void CCurrencyConverterDlg::OnEnChangeEdit1()
{
	CString value;
	GetDlgItemText(IDC_EDIT1, value);
	
	if (value.IsEmpty()) {
		this->CheckButtonState(IDC_BUTTON2_CONVERT);
	}
	else {
		this->CheckButtonState(IDC_BUTTON2_CONVERT, true);
	}
}

void CCurrencyConverterDlg::OnBnClickedButton1Refresh()
{
	SetRedraw(FALSE);
	this->currencyList.DeleteAllItems();
	this->currencyFrom.ResetContent();
	this->currencyTo.ResetContent();
	SetRedraw(TRUE);

	this->DownloadCurrency();
}


void CCurrencyConverterDlg::OnBnClickedButton3Exit()
{
	CDialog::OnCancel();
}


void CCurrencyConverterDlg::OnBnClickedButton1()
{
	AboutDialog about;
	about.DoModal();
}
