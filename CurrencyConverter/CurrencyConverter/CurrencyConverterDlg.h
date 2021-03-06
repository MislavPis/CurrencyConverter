#pragma once

class CCurrencyConverterDlg : public CDialog
{
private:
	void AddColumnsName();
	void PrepareCurrencyList();
	void DownloadCurrency();
	void UnsuccessfulDownload();
	void CheckButtonState(int, bool = false);
	void InsertCurrencyIntoList();
	void FillComboCurrency(CComboBox&);
	void PrepareCombos();
	float ConvertValue(const CString&, const CString&, const float value);
	CString GetStringFromMap(int);
	bool IsInputValid(const CString&);

public:
	CCurrencyConverterDlg(CWnd* pParent = nullptr);	// standard constructor
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CURRENCYCONVERTER_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CEdit editValue;
	CEdit timeEdit;
	CListCtrl currencyList;
	CComboBox currencyFrom;
	CComboBox currencyTo;
	bool canConvert;

	std::map<CString, float> currencyMap;

	afx_msg void OnBnClickedButton2Convert();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1Refresh();
	afx_msg void OnBnClickedButton3Exit();
	afx_msg void OnBnClickedButton1();
};
