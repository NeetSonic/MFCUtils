//--------------------------------
// DialogManager for MFC project
// Author:neetsonic
// Date:2016/6/30
//--------------------------------

#include "stdafx.h"
#include "DialogManager.h"
#include "cderr.h"

#define MAX_FILE_SELECT_COUNT MAX_PATH
#define SELECTED_TOO_MUCH_FILE L"打开的文件数量太多！"

BOOL DialogManager::ShowFolderDlg(LPCWSTR lpszTitle, LPWSTR lpszGetPath, BFFCALLBACK callback /* = NULL */) {
	ASSERT(lpszGetPath);
	BROWSEINFO sInfo; // 设置文件夹浏览窗的结构
	::memset(&sInfo, 0, sizeof(BROWSEINFO));
	sInfo.pidlRoot = NULL; // 要显示的文件目录对话框的根
	sInfo.lpszTitle = lpszTitle; // 显示位于对话框左上部的标题  
	sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_USENEWUI; // 指定对话框的外观和功能的标志  
	sInfo.lpfn = callback;	// 处理事件的回调函数 
	sInfo.lParam = NULL;

	LPITEMIDLIST lpidlBrowse; // 显示文件夹选择的对话框  
	if(lpidlBrowse = ::SHBrowseForFolderW(&sInfo)) {
		BOOL bRet;
		bRet = ::SHGetPathFromIDListW(lpidlBrowse, lpszGetPath); // 取得文件夹名
		::CoTaskMemFree(lpidlBrowse);
		return bRet;
	}
	return FALSE;
}
int DialogManager::ShowSingleFileDlg(CString & getFilePath, LPCWSTR lpszFilter, DWORD dwFlags /* = OFN_HIDEREADONLY */) {
	int nRet;
	CFileDialog fileDlg(TRUE, NULL, NULL, dwFlags, lpszFilter);
	nRet = fileDlg.DoModal();
	if(nRet == IDOK) getFilePath = fileDlg.GetPathName();
	return nRet;
}
int DialogManager::ShowMultiFileDlg(LinkList<CString>* pFileNameList, LPCWSTR lpszFilter, DWORD dwFlags /* = OFN_HIDEREADONLY */) {
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT | dwFlags, lpszFilter);
	fileDlg.m_ofn.nMaxFile = static_cast<DWORD>(MAX_FILE_SELECT_COUNT * MAX_PATH);
	wchar_t buffer[MAX_FILE_SELECT_COUNT * MAX_PATH];
	::memset(buffer, 0, sizeof(buffer));
	fileDlg.m_ofn.lpstrFile = buffer;
	int nRet = fileDlg.DoModal();
	if((nRet == IDCANCEL) && (::CommDlgExtendedError() == FNERR_BUFFERTOOSMALL)) AfxMessageBox(SELECTED_TOO_MUCH_FILE);
	else if(nRet == IDOK) {
		POSITION filePos;
		filePos = fileDlg.GetStartPosition();
		while(filePos != NULL) pFileNameList->Append(fileDlg.GetNextPathName(filePos));
	}
	return nRet;
}