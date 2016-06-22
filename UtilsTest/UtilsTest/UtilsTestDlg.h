
// UtilsTestDlg.h : 头文件
//

#pragma once
#include "SmartEdit.h"


// CUtilsTestDlg 对话框
class CUtilsTestDlg : public CDialogEx
{
// 构造
public:
	CUtilsTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UTILSTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	SmartEdit m_editTest1;
};
