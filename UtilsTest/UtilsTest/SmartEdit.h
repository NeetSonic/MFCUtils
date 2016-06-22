//----------------------------
// SmartEdit for MFC project
// Author:neetsonic
// Date:2016/6/22
//----------------------------

//--------------------------------
// 特性：
//      1.可通过拖拽文件获取文件名
//--------------------------------

#pragma once

class SmartEdit : public CEdit {
	DECLARE_DYNAMIC(SmartEdit)
	DECLARE_MESSAGE_MAP()

public:
	SmartEdit();
	virtual ~SmartEdit();
	void HighlightFileName(); // 高亮文件名
	afx_msg void OnDropFiles(HDROP hDropInfo); // 拖拽文件消息
};


