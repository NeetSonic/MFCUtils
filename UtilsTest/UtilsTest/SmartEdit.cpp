//----------------------------
// SmartEdit for MFC project
// Author:neetsonic
// Date:2016/6/22
//----------------------------

#include "stdafx.h"
#include "SmartEdit.h"
#include "MFCUtils.h"
#include "StringManager.h"
#include "TimeManager.h"

IMPLEMENT_DYNAMIC(SmartEdit, CEdit)

BEGIN_MESSAGE_MAP(SmartEdit, CEdit)
	ON_WM_DROPFILES()
	ON_WM_CHAR()
END_MESSAGE_MAP()

SmartEdit::SmartEdit() : m_bLimitInput(false), m_pData(NULL) {}
SmartEdit::~SmartEdit() {
	// 释放已经存储的限制字符输入气泡提示的数据
	if(m_pData) {
		MFCUtils::MultiDelete(m_pData->lpszBallonTipTitle);
		MFCUtils::MultiDelete(m_pData->lpszBallonTipText);
		delete m_pData;
	}
}

static bool filter(UINT nChar) {
	return ((nChar >= L'0') && (nChar <= L'9'));
}

void SmartEdit::HighlightFileName() {
	CString csFileName;
	CEdit::GetWindowTextW(csFileName);
	CEdit::SetFocus();
	CEdit::SetSel(0, csFileName.ReverseFind(WCHAR_DOT));
}
void SmartEdit::LimitInput(bool(*pfnFilter)(UINT nChar), LPCWSTR lpszBallonTipTitle /* = NULL */, LPCWSTR lpszBallonTipText /* = NULL */, INT ttiIcon /* = TTI_NONE */) {
	m_bLimitInput = !!(pfnFilter); // 设置是否要限制输入
	if(pfnFilter) {
		if(!m_pData) {
			m_pData = new LIMIT_INPUT_DATA;
			m_pData->pfnFilter = NULL;
			m_pData->lpszBallonTipText = NULL;
			m_pData->lpszBallonTipTitle = NULL;
			m_pData->ttiIcon = NULL;
		}
		m_pData->pfnFilter = pfnFilter;
		StringManager::WcscpyPtr(&m_pData->lpszBallonTipTitle, lpszBallonTipTitle);
		StringManager::WcscpyPtr(&m_pData->lpszBallonTipText, lpszBallonTipText);
		m_pData->ttiIcon = ttiIcon;
	}
}
void SmartEdit::WriteLog(LPCWSTR lpszLog, bool bPrintTime /* = true */) {
	CString log;
	this->GetWindowTextW(log);
	if(log.GetLength())log.Append(WCS_NEW_LINE);
	if(bPrintTime) {
		log.Append(TimeManager::GetCurrTimeFormattedString());
		log.Append(WCS_SPACE);
	}
	log.Append(lpszLog);
	log.Append(WCS_NEW_LINE);
	this->SetWindowTextW(log);
	this->LineScroll(this->GetLineCount());
}
afx_msg void SmartEdit::OnDropFiles(HDROP hDropInfo) {
	if(hDropInfo) {
		/* 在这里做处理 */

		// DragQueryFileW() 的函数说明
		/*
		hDrop Handle sent by Message
		iFile: File index.
		if pass 0xFFFFFFFF, function returns count of files being dragged.
		if pass 0 to n, function will copy the file path indexed by iFile to lpszFile.

		lpszFile: Space to save the specified file name.
		if pass NULL, function returns count of files being dragged.
		if NOT NULL, function returns length of file path in word.

		cch: size of lpszFile in word.
		*/

		// 处理示例1：获取拖拽的文件个数
		UINT nDragFileCount;
		nDragFileCount = DragQueryFileW(hDropInfo, 0xFFFFFFFF, NULL, 0);

		// 处理示例2：将第一个文件的文件路径展示出来
		UINT nFilePathLen;
		WCHAR wcsBuffer[MAX_PATH + 1];
		memset(wcsBuffer, 0, sizeof(wcsBuffer));
		nFilePathLen = DragQueryFileW(hDropInfo, 0, wcsBuffer, MAX_PATH);
		CEdit::SetWindowTextW(wcsBuffer);

		// 处理示例3：高亮文件名
		HighlightFileName();

		// 处理示例4：显示气泡提示
		this->ShowBalloonTip(L"提示", L"成功的拖拽了文件进入编辑框！", TTI_INFO_LARGE);

		// 处理示例5：限制用户输入数字0-9
		LimitInput(&filter, L"提示", L"你只能输入0-9的数字！", TTI_ERROR_LARGE);
	}
}
afx_msg void SmartEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	((!m_bLimitInput) || m_pData->pfnFilter(nChar)) ? CEdit::OnChar(nChar, nRepCnt, nFlags) : this->ShowBalloonTip(m_pData->lpszBallonTipTitle, m_pData->lpszBallonTipText, m_pData->ttiIcon);
}