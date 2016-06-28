//----------------------------
// SmartListBox for MFC project
// Author:neetsonic
// Date:2016/6/27
//----------------------------

#include "stdafx.h"
#include "SmartListBox.h"

IMPLEMENT_DYNAMIC(SmartListBox, CListBox)
BEGIN_MESSAGE_MAP(SmartListBox, CListBox)
END_MESSAGE_MAP()

#define SLB_HS_BAR_OFFSET 90
int SmartListBox::AddString(LPCTSTR lpszItem) {
	int nResult = CListBox::AddString(lpszItem);
	SetHSBar();
	return nResult;
}
int SmartListBox::InsertString(int nIndex, LPCTSTR lpszItem) {
	int nResult = CListBox::InsertString(nIndex, lpszItem);
	SetHSBar();
	return nResult;
}
void SmartListBox::SetHSBar(void) {
	int nCount, nMaxExtent;
	CDC *pDC;
	CString cs;
	CSize size;
	pDC = GetDC();
	if(!pDC) return;

	nCount = GetCount();
	if(nCount < 1) {
		SetHorizontalExtent(0);
		return;
	}

	nMaxExtent = 0;
	for(int i = 0; i < nCount; i++) {
		GetText(i, cs);
		size = pDC->GetTextExtent(cs);
		if(size.cx > nMaxExtent) nMaxExtent = size.cx;
	}

	SetHorizontalExtent(nMaxExtent - SLB_HS_BAR_OFFSET); // 根据实际情况调整显示长度
}