// AboutDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CurrencyConverter.h"
#include "AboutDialog.h"
#include "afxdialogex.h"


// AboutDialog dialog

IMPLEMENT_DYNAMIC(AboutDialog, CDialog)

AboutDialog::AboutDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

AboutDialog::~AboutDialog()
{
}

void AboutDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutDialog, CDialog)
END_MESSAGE_MAP()


// AboutDialog message handlers
