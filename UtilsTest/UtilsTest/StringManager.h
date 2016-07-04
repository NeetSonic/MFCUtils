//--------------------------------
// StringManager for MFC project
// Author:neetsonic
// Date:2016/6/29
//--------------------------------

//-----------------------------------
// ���ԣ�
//      1.��ת���ַ������뷽ʽ
//      2.�ɷ���Ŀ����ַ������Ѻ�ջ��
//      3.���ж�CString�Ŀ�ͷ���β
//-----------------------------------

#pragma once
namespace StringManager {
	void UnicodeToAnsi(LPCWSTR srcStr, LPSTR destStr, UINT nMaxBytesToConvert); // UnicodeתAnsi
	void UnicodeToUTF8(LPCWSTR srcStr, LPSTR destStr, UINT nMaxBytesToConvert); // UnicodeתUTF-8
	void AnsiToUnicode(LPCSTR srcStr, LPWSTR destStr, UINT nMaxWordsToConvert); // AnsiתUnicode
	void WcscpyPtr(LPWSTR* dstPtrAddr, LPCWSTR src); // ������Heap�ռ��е������ַ���
	void WcscpyArray(LPWSTR dstArr, size_t sizeInWords, LPCWSTR src); // ������Stack�ռ��е��ַ������ַ����飩
	bool CStringStartWith(const CString & cs, LPCWSTR startStr); // CString�����Ƿ���ĳһ�ַ���������ʼ
	bool CStringEndWith(const CString & cs, LPCWSTR endStr); // CString�����Ƿ���ĳһ�ַ���������β
};

