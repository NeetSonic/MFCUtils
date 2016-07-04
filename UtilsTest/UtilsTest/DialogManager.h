//--------------------------------
// DialogManager for MFC project
// Author:neetsonic
// Date:2016/6/30
//--------------------------------

//-------------------------------------------
// ���ԣ�
//      1.����ʾѡ���ļ��еĶԻ���
//      2.����ʾѡ��򿪵��������ļ��ĶԻ���
//-------------------------------------------

#pragma once
#include "LinkStructs.h"

#define FOLDER_DIALOG_DEFAULT_TITLE L"��ѡ��һ���ļ��У�"
#define FILE_DAILOG_ALL_FILE L"�����ļ�(*.*)|*.*||"
#define FILE_DAILOG_IMAGE_FILE L"ͼ���ļ���JPG, PNG, BMP)|*.jpg;*.png;*.bmp||"

namespace DialogManager {
	BOOL ShowFolderDlg(LPCWSTR lpszTitle, LPWSTR lpszGetPath, BFFCALLBACK callback = NULL); // ��ʾѡ���ļ��еĶԻ���
	int ShowSingleFileDlg(CString & getFilePath, LPCWSTR lpszFilter, DWORD dwFlags = OFN_HIDEREADONLY); // ��ʾѡ��򿪵����ļ��ĶԻ���
	int ShowMultiFileDlg(LinkList<CString>* pFileNameList, LPCWSTR lpszFilter, DWORD dwFlags = OFN_HIDEREADONLY); // ��ʾѡ��򿪶���ļ��ĶԻ���
};

