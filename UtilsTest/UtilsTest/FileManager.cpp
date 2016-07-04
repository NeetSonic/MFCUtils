//--------------------------------
// FileManager for MFC project
// Author:neetsonic
// Date:2016/6/30
//--------------------------------

#include "stdafx.h"
#include "FileManager.h"
#include "MFCUtils.h"

void FileManager::RemoveFilePostfix(CString & filePath) {
	int nFlag = filePath.ReverseFind(WCHAR_DOT);
	if(nFlag != CSTRING_FIND_FAILED) filePath = filePath.Left(nFlag);
}
void FileManager::GetPathFilePostfix(LPCWSTR filePath, CString & postfix) {
	FileManager::GetPathFilePostfix(CString(filePath), postfix);
}
void FileManager::GetPathFilePostfix(const CString & filePath, CString & postfix) {
	int nFlag = filePath.ReverseFind(WCHAR_DOT);
	postfix = (nFlag != CSTRING_FIND_FAILED) ? filePath.Right(filePath.GetLength() - nFlag) : WCS_EMPTY;
}
void FileManager::GetPathFileName(LPCWSTR filePath, CString & name) {
	FileManager::GetPathFileName(CString(filePath), name);
}
void FileManager::GetPathFileName(const CString & filePath, CString & name) {
	int nFlag = filePath.ReverseFind(WCHAR_BACK_SLASH);
	name = (nFlag != CSTRING_FIND_FAILED) ? filePath.Right(filePath.GetLength() - nFlag - 1) : filePath;
}
void FileManager::GetFileDirectory(LPCWSTR filePath, CString & dir) {
	FileManager::GetFileDirectory(CString(filePath), dir);
}
void FileManager::GetFileDirectory(const CString & filePath, CString & dir) {
	int nFlag = filePath.ReverseFind(WCHAR_BACK_SLASH);
	dir = (nFlag != CSTRING_FIND_FAILED) ? filePath.Left(nFlag) : filePath;
}
void FileManager::EnsureDirExist(LPCWSTR dir) {
	FileManager::EnsureDirExist(CString(dir));
}
void FileManager::EnsureDirExist(const CString & dir) {
	if(::PathFileExistsW(dir) || (dir.Find(WCHAR_BACK_SLASH) == CSTRING_FIND_FAILED)) return;
	CString csFatherDir;
	FileManager::GetFileDirectory(dir, csFatherDir);
	FileManager::EnsureDirExist(csFatherDir);
	::CreateDirectoryW(dir, NULL);
}
BOOL FileManager::SmartCopyFile(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists) {
	CString csDir;
	FileManager::GetFileDirectory(lpNewFileName, csDir);
	FileManager::EnsureDirExist(csDir);
	return ::CopyFileW(lpExistingFileName, lpNewFileName, bFailIfExists);
}
BOOL FileManager::SmartCopyFile(const CString & existingFileName, const CString & newFileName, BOOL bFailIfExists) {
	return FileManager::SmartCopyFile(existingFileName.GetString(), newFileName.GetString(), bFailIfExists);
}