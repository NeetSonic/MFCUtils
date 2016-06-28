//-------------------------------
// SmartListCtrl for MFC project
// Author:neetsonic
// Date:2016/6/27
//-------------------------------

//--------------------------------
// ���ԣ�
//      1.֧�ֿ��ٳ�ʼ��
//      2.֧�ֵ�һ�б��������ʾ
//--------------------------------

#pragma once
#include "MFCUtils.h"
using namespace MFCUtils;

class SmartListCtrl : public CListCtrl {
	DECLARE_DYNAMIC(SmartListCtrl)
	DECLARE_MESSAGE_MAP()

public:
	SmartListCtrl();
	virtual ~SmartListCtrl();
	void Init(DWORD dwStyle, INT nCols, INT nFormat, LPCWSTR *pHeaders, DOUBLE *pColWidth = NULL); // ��ʼ���б�ؼ�
};


