//--------------------------------
// FileManager for MFC project
// Author:neetsonic
// Date:2016/6/30
//--------------------------------

//----------------------------------------
// 特性：
//      1.可根据不同条件获取文件路径中的内容
//      2.可方便的创建指定路径
//      3.可智能拷贝文件
//----------------------------------------

#pragma once
namespace FileManager {
	void RemoveFilePostfix(CString & filePath); // 去掉文件名中的后缀
	void GetPathFilePostfix(LPCWSTR filePath, CString & postfix); // 获取文件名中的后缀（含"."号）
	void GetPathFilePostfix(const CString & filePath, CString & postfix); // 获取文件名中的后缀（含"."号）
	void GetPathFileName(LPCWSTR filePath, CString & name); // 获取文件路径中的文件名
	void GetPathFileName(const CString & filePath, CString & name); // 获取文件路径中的文件名
	void GetFileDirectory(LPCWSTR filePath, CString & dir); // 获取文件所在文件夹的路径
	void GetFileDirectory(const CString & filePath, CString & dir);// 获取文件所在文件夹的路径
	void EnsureDirExist(LPCWSTR dir); // 确保指定路径存在（若不存在则自动创建文件夹）
	void EnsureDirExist(const CString & dir); // 确保指定路径存在（若不存在则自动创建文件夹）
	BOOL SmartCopyFile(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists); // 文件拷贝，如果指定的目标路径不存在将自动创建
	BOOL SmartCopyFile(const CString & existingFileName, const CString & newFileName, BOOL bFailIfExists); // 文件拷贝，如果指定的目标路径不存在将自动创建
};

