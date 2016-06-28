//--------------------------------
// SmartComboBox for MFC project
// Author:neetsonic
// Date:2016/6/25
//--------------------------------

//--------------------------------
// 特性：
//      1.将SmartEdit对象附加到ComboBox上，替换掉CEdit，具有SmartEdit的所有功能
//--------------------------------

#pragma once
#include "SmartEdit.h"
#include "MFCUtils.h"
using namespace MFCUtils;

class SmartComboBox : public CComboBox {
	DECLARE_DYNAMIC(SmartComboBox)
	DECLARE_MESSAGE_MAP()

public:
	SmartEdit m_edit;
	SmartComboBox();
	virtual ~SmartComboBox();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor); // 绘制控件的消息
	afx_msg void OnDropFiles(HDROP hDropInfo); // 拖拽文件的消息
};


