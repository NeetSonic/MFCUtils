//-------------------------------
// SmartListCtrl for MFC project
// Author:neetsonic
// Date:2016/6/27
//-------------------------------

//--------------------------------
// 特性：
//      1.支持快速初始化
//      2.支持第一列标题居中显示
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
	void Init(DWORD dwStyle, INT nCols, INT nFormat, LPCWSTR *pHeaders, DOUBLE *pColWidth = NULL); // 初始化列表控件
};


