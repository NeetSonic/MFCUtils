//-------------------------------
// SmartListCtrl for MFC project
// Author:neetsonic
// Date:2016/6/27
//-------------------------------

#include "stdafx.h"
#include "UtilsTest.h"
#include "SmartListCtrl.h"

IMPLEMENT_DYNAMIC(SmartListCtrl, CListCtrl)
BEGIN_MESSAGE_MAP(SmartListCtrl, CListCtrl)
END_MESSAGE_MAP()

SmartListCtrl::SmartListCtrl() {}
SmartListCtrl::~SmartListCtrl() {}

void SmartListCtrl::Init(DWORD dwStyle, INT nCols, INT nFormat, LPCWSTR *pHeaders, DOUBLE *pColWidth /* = NULL */) {
	this->DeleteAllItems();
	this->SetExtendedStyle(this->GetExtendedStyle() | dwStyle);
	
	int nTotalWidth;
	CRect rc;
	this->GetWindowRect(&rc);
	nTotalWidth = static_cast<int>(rc.Size().cx);
	for(int i = 0; i < nCols; i++) {
		this->InsertColumn(i, pHeaders[i], nFormat, (pColWidth) ? static_cast<int>(nTotalWidth * pColWidth[i]) : (nTotalWidth / nCols));
	}

	// 修改参数使得支持第一列标题居中显示
	if(nFormat == LVCFMT_CENTER) {
		LVCOLUMN lvc;
		lvc.mask = LVCF_FMT;
		GetColumn(0, &lvc);
		lvc.fmt &= ~LVCFMT_JUSTIFYMASK;
		lvc.fmt |= LVCFMT_CENTER;
		SetColumn(0, &lvc);
	}
}


