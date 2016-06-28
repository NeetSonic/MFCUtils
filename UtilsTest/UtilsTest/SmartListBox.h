//----------------------------
// SmartListBox for MFC project
// Author:neetsonic
// Date:2016/6/27
//----------------------------

//------------------------------------
// 特性：
//      1.可以自动根据文本长度生成滚动条
//------------------------------------

#pragma once

class SmartListBox : public CListBox {
	DECLARE_DYNAMIC(SmartListBox)
	DECLARE_MESSAGE_MAP()

public:
	SmartListBox(void) {};
	virtual ~SmartListBox(void) {};
	void SetHSBar(void); // 计算水平滚动条宽度

	// 覆盖以下方法以便添加水平滚动条，调用一下方法后会自动设置水平滚动条
	int AddString(LPCTSTR lpszItem);
	int InsertString(int nIndex, LPCTSTR lpszItem);
};