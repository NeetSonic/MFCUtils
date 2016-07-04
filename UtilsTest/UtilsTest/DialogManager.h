//--------------------------------
// DialogManager for MFC project
// Author:neetsonic
// Date:2016/6/30
//--------------------------------

//-------------------------------------------
// 特性：
//      1.可显示选择文件夹的对话框
//      2.可显示选择打开单个或多个文件的对话框
//-------------------------------------------

#pragma once
#include "LinkStructs.h"

#define FOLDER_DIALOG_DEFAULT_TITLE L"请选择一个文件夹："
#define FILE_DAILOG_ALL_FILE L"所有文件(*.*)|*.*||"
#define FILE_DAILOG_IMAGE_FILE L"图像文件（JPG, PNG, BMP)|*.jpg;*.png;*.bmp||"

namespace DialogManager {
	BOOL ShowFolderDlg(LPCWSTR lpszTitle, LPWSTR lpszGetPath, BFFCALLBACK callback = NULL); // 显示选择文件夹的对话框
	int ShowSingleFileDlg(CString & getFilePath, LPCWSTR lpszFilter, DWORD dwFlags = OFN_HIDEREADONLY); // 显示选择打开单个文件的对话框
	int ShowMultiFileDlg(LinkList<CString>* pFileNameList, LPCWSTR lpszFilter, DWORD dwFlags = OFN_HIDEREADONLY); // 显示选择打开多个文件的对话框
};

