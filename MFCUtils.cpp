#include "stdafx.h"
#include "MFCUtils.h"
#include "cderr.h"
using namespace MFCUtils;

//--------------------字符（串）操作相关--------------------
void MFCUtils::UnicodeToAnsi(const wchar_t* srcStr, char* destStr, const UINT & nMaxBytesToConvert) {
	int nLen = WideCharToMultiByte(CP_ACP, 0, srcStr, -1, NULL, 0, NULL, NULL); // 得到转换后的Ansi字符串长度，包含结尾符\0
	if(nLen) {
		char* p = new char[nLen];
		WideCharToMultiByte(CP_ACP, 0, srcStr, -1, p, nLen, NULL, NULL); // 转换
		strcpy_s(destStr, nMaxBytesToConvert, p); // 在nMaxBytesToConvert范围内遇到\0则停止拷贝
		MultiDelete(p);
	}
}
void MFCUtils::UnicodeToUTF8(const wchar_t* srcStr, char* destStr, const UINT & nMaxBytesToConvert) {
	int nLen = WideCharToMultiByte(CP_UTF8, 0, srcStr, -1, NULL, 0, NULL, NULL);
	if(nLen) {
		char* utf8Str = new char[nLen];
		WideCharToMultiByte(CP_UTF8, 0, srcStr, -1, utf8Str, nLen, NULL, NULL);
		strcpy_s(destStr, nMaxBytesToConvert, utf8Str);
		MultiDelete(utf8Str);
	}
}
void MFCUtils::AnsiToUnicode(const char* srcStr, wchar_t* destStr, const UINT & nMaxWordsToConvert) {
	int nLen = MultiByteToWideChar(CP_ACP, 0, srcStr, -1, NULL, 0);
	if(nLen) {
		wchar_t * pUnicode = new wchar_t[nLen];
		MultiByteToWideChar(CP_ACP, 0, srcStr, -1, pUnicode, nLen);
		wcscpy_s(destStr, nMaxWordsToConvert, pUnicode);
		MultiDelete(pUnicode);
	}
}
void MFCUtils::WcscpyPtr(wchar_t** dstPtrAddr, const wchar_t* src) {
	ASSERT(src);
	size_t nLen;
	nLen = wcslen(src) + 1;
	MultiDelete(*dstPtrAddr);
	(*dstPtrAddr) = new wchar_t[nLen];
	wcscpy_s(*dstPtrAddr, nLen, src);
}
void MFCUtils::WcscpyArray(wchar_t* dstArr, const size_t & sizeInWords, const wchar_t* src) {
	ASSERT(dstArr && src);
	size_t nLen;
	nLen = wcslen(src) + 1;
	ASSERT(sizeInWords >= nLen);
	wmemset(dstArr, 0, sizeInWords);
	wcscpy_s(dstArr, nLen, src);
}
bool MFCUtils::WcsEndWith(const CString & cs, const wchar_t* endStr) {
	int nLen;
	nLen = wcslen(endStr);
	if(cs.GetLength() < nLen) return false;
	return (cs.Right(nLen).Compare(endStr) == 0);
}

//--------------------实用功能--------------------
#define CTIME_FORMAT_WCS L"%Y/%m/%d %H:%M:%S"
int MFCUtils::GetCurrYear() {
	CTime time;
	CString csYear;
	int nYear;
	time = CTime::GetCurrentTime();
	csYear = time.Format(L"%Y");
	nYear = _wtoi(csYear.GetString());
	return nYear;
}
CString MFCUtils::GetCTimeFormatString(CTime & time) {
	return time.Format(CTIME_FORMAT_WCS);
}

//--------------------打开对话框操作--------------------
#define MAX_FILE_SELECT_COUNT MAX_PATH
#define WILD_CARD_WCS L"*.*"
#define FOLDER_DIALOG_TITLE L"请选择一个文件夹："
#define FILE_DAILOG_ALL_FILE L"所有文件(*.*)|*.*||"
#define FILE_DAILOG_IMAGE_FILE L"图像文件（JPG, PNG, BMP)|*.jpg;*.png;*.bmp||"
#define SELECTED_TOO_MUCH_FILE L"打开的文件数量太多！"
BOOL MFCUtils::ShowFolderDlg(wchar_t* pWcsGetPath, BFFCALLBACK callback/* = NULL */) {
	ASSERT(pWcsGetPath);
	// 设置文件夹浏览窗的结构
	BROWSEINFO sInfo;
	memset(&sInfo, 0, sizeof(BROWSEINFO));
	sInfo.pidlRoot = NULL;										 // 要显示的文件目录对话框的根
	sInfo.lpszTitle = FOLDER_DIALOG_TITLE;					     // 显示位于对话框左上部的标题  
	sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS // 指定对话框的外观和功能的标志  
		| BIF_USENEWUI;
	sInfo.lpfn = callback;	// 处理事件的回调函数 
	sInfo.lParam = 0;
	
	LPITEMIDLIST lpidlBrowse = SHBrowseForFolderW(&sInfo); // 显示文件夹选择的对话框  
	if(lpidlBrowse) {
		BOOL bRet;
		bRet = ::SHGetPathFromIDListW(lpidlBrowse, pWcsGetPath); // 取得文件夹名
		CoTaskMemFree(lpidlBrowse);
		return bRet;
	}
	return false;
}
int MFCUtils::ShowMultiFileDlg(LinkList<CString>* list) {
	CFileDialog fileDlg(TRUE, NULL, WILD_CARD_WCS, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY, FILE_DAILOG_ALL_FILE);
	fileDlg.m_ofn.nMaxFile = static_cast<DWORD>(MAX_FILE_SELECT_COUNT * MAX_PATH);
	wchar_t buffer[MAX_FILE_SELECT_COUNT * MAX_PATH];
	fileDlg.m_ofn.lpstrFile = buffer;
	memset(fileDlg.m_ofn.lpstrFile, 0, sizeof(buffer));
	int ret = fileDlg.DoModal();
	if(ret == IDCANCEL) {
		if(CommDlgExtendedError() == FNERR_BUFFERTOOSMALL) { AfxMessageBox(SELECTED_TOO_MUCH_FILE); }
	}
	else if(ret == IDOK) {
		POSITION filePos;
		CString csFilePath;
		filePos = fileDlg.GetStartPosition();
		while(filePos != NULL) list->Append(fileDlg.GetNextPathName(filePos));
	}
	return ret;
}
int MFCUtils::ShowSingleFileDlg(CString & filePath) {
	int nRet;
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, FILE_DAILOG_IMAGE_FILE);
	nRet = fileDlg.DoModal();
	if(nRet == IDOK) filePath = fileDlg.GetPathName();
	return nRet;
}

//--------------------文件操作--------------------
#define SIZE_GB 1024*1024*1024
#define SIZE_MB 1024*1024
#define SIZE_KB 1024
void MFCUtils::GetFileSizeWcs(CString path, wchar_t *buf, int maxWordCount) {
	CFile file;
	UINT nLen; // 单个文件不能超过4G大小
	if(!file.Open(path, CFile::modeRead | CFile::typeBinary, 0)) return;
	nLen = static_cast<UINT>(file.GetLength());
	float fSize;
	CString cs;
	if(nLen > SIZE_GB) {
		fSize = static_cast<float>(nLen) / static_cast<float>(SIZE_GB);
		cs.Format(L"%.2fGB", fSize);
	}
	else if(nLen > SIZE_MB) {
		fSize = static_cast<float>(nLen) / static_cast<float>(SIZE_MB);
		cs.Format(L"%.2fMB", fSize);
	}
	else if(nLen > SIZE_KB) {
		fSize = static_cast<float>(nLen) / static_cast<float>(SIZE_KB);
		cs.Format(L"%.2fKB", fSize);
	}
	else { cs.Format(L"%dB", nLen); }
	wcscpy_s(buf, maxWordCount, cs.GetString());
}
void MFCUtils::RemoveFilePostfix(CString & filePath) {
	int nFlag;
	nFlag = filePath.ReverseFind(DOT_W);
	if(nFlag != CSTRING_FIND_FAILED)filePath = filePath.Left(nFlag);
}
void MFCUtils::GetPathFilePostfix(const wchar_t* filePath, CString & postfix) {
	CString cs(filePath);
	int nFlag;
	nFlag = cs.ReverseFind(DOT_W);
	postfix = (nFlag != CSTRING_FIND_FAILED) ? cs.Right(cs.GetLength() - nFlag) : EMPTY_WCS;
}
void MFCUtils::GetPathFileName(const wchar_t* filePath, CString & name) {
	CString cs(filePath);
	int nFlag;
	nFlag = cs.ReverseFind(BACK_SLASH);
	name = (nFlag != CSTRING_FIND_FAILED) ? cs.Right(cs.GetLength() - nFlag - 1) : cs;
}
void MFCUtils::GetFileDirectory(const wchar_t* filePath, CString & csDir) {
	CString cs(filePath);
	int nFlag;
	nFlag = cs.ReverseFind(BACK_SLASH);
	csDir = (nFlag != CSTRING_FIND_FAILED) ? cs.Left(nFlag) : cs;
}
void MFCUtils::EnsureDirExist(const wchar_t* dir) {
	if(PathFileExistsW(dir)) return;
	CString cs(dir), csFatherDir;
	if(cs.Find(BACK_SLASH) == CSTRING_FIND_FAILED) return; // Prevent infinite loop when meets an error input.
	GetFileDirectory(dir, csFatherDir);
	EnsureDirExist(csFatherDir.GetString());
	CreateDirectoryW(dir, NULL);
}
BOOL MFCUtils::SmartCopyFile(const wchar_t* lpExistingFileName, const wchar_t* lpNewFileName, BOOL bFailIfExists) {
	CString csDir;
	GetFileDirectory(lpNewFileName, csDir);
	EnsureDirExist(csDir);
	return CopyFileW(lpExistingFileName, lpNewFileName, bFailIfExists);
}

