//--------------------------------
// FileManager for MFC project
// Author:neetsonic
// Date:2016/6/30
//--------------------------------

//----------------------------------------
// ���ԣ�
//      1.�ɸ��ݲ�ͬ������ȡ�ļ�·���е�����
//      2.�ɷ���Ĵ���ָ��·��
//      3.�����ܿ����ļ�
//----------------------------------------

#pragma once
namespace FileManager {
	void RemoveFilePostfix(CString & filePath); // ȥ���ļ����еĺ�׺
	void GetPathFilePostfix(LPCWSTR filePath, CString & postfix); // ��ȡ�ļ����еĺ�׺����"."�ţ�
	void GetPathFilePostfix(const CString & filePath, CString & postfix); // ��ȡ�ļ����еĺ�׺����"."�ţ�
	void GetPathFileName(LPCWSTR filePath, CString & name); // ��ȡ�ļ�·���е��ļ���
	void GetPathFileName(const CString & filePath, CString & name); // ��ȡ�ļ�·���е��ļ���
	void GetFileDirectory(LPCWSTR filePath, CString & dir); // ��ȡ�ļ������ļ��е�·��
	void GetFileDirectory(const CString & filePath, CString & dir);// ��ȡ�ļ������ļ��е�·��
	void EnsureDirExist(LPCWSTR dir); // ȷ��ָ��·�����ڣ������������Զ������ļ��У�
	void EnsureDirExist(const CString & dir); // ȷ��ָ��·�����ڣ������������Զ������ļ��У�
	BOOL SmartCopyFile(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists); // �ļ����������ָ����Ŀ��·�������ڽ��Զ�����
	BOOL SmartCopyFile(const CString & existingFileName, const CString & newFileName, BOOL bFailIfExists); // �ļ����������ָ����Ŀ��·�������ڽ��Զ�����
};

