//----------------------------
// SmartEdit for MFC project
// Author:neetsonic
// Date:2016/6/22
//----------------------------

#include "stdafx.h"
#include "UtilsTest.h"
#include "SmartEdit.h"

IMPLEMENT_DYNAMIC(SmartEdit, CEdit)

BEGIN_MESSAGE_MAP(SmartEdit, CEdit)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

SmartEdit::SmartEdit() {}
SmartEdit::~SmartEdit() {}

void SmartEdit::OnDropFiles(HDROP hDropInfo) {
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
	}
}
