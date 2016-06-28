//----------------------------
// SmartEdit for MFC project
// Author:neetsonic
// Date:2016/6/22
//----------------------------

//--------------------------------
// 特性：
//      1.可通过拖拽文件获取文件名
//      2.可将获取到的文件名设置高亮
//      3.可以限制输入的字符
//--------------------------------

#pragma once

// 用于存放限制字符输入所需要的参数
typedef struct LimitInputData {
	bool(*pfnFilter)(UINT nChar); // 限制输入字符的函数指针
	LPWSTR lpszBallonTipTitle;    // 用户键入非法字符时气泡提示的标题
	LPWSTR lpszBallonTipText;     // 用户键入非法字符时气泡提示的内容
	INT ttiIcon;				  // 用户键入非法字符时气泡提示的类型
}LIMIT_INPUT_DATA;

class SmartEdit : public CEdit {
	DECLARE_DYNAMIC(SmartEdit)
	DECLARE_MESSAGE_MAP()

private:
	bool m_bLimitInput; // 是否限制输入字符
	LIMIT_INPUT_DATA* m_pData; // 限制字符输入所需要的参数

public:
	SmartEdit();
	virtual ~SmartEdit();
	void HighlightFileName(); // 高亮文件名（设置选中）
	void LimitInput(bool(*pfnFilter)(UINT nChar), LPCWSTR lpszBallonTipTitle = NULL, LPCWSTR lpszBallonTipText = NULL, INT ttiIcon = TTI_NONE); // 限制输入的字符，只传一个NULL参数表示取消限制
	void WriteLog(LPCWSTR lpszLog, bool bPrintTime = true); // 打印日志消息（对于作为日志框的控件使用）
	afx_msg void OnDropFiles(HDROP hDropInfo); // 拖拽文件的消息
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags); // 键盘输入字符的消息
};
