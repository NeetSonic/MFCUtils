//--------------------------------
// StringManager for MFC project
// Author:neetsonic
// Date:2016/6/29
//--------------------------------

//-----------------------------------
// 特性：
//      1.可转换字符串编码方式
//      2.可方便的拷贝字符串到堆和栈中
//      3.可判断CString的开头与结尾
//-----------------------------------

#pragma once
namespace StringManager {
	void UnicodeToAnsi(LPCWSTR srcStr, LPSTR destStr, UINT nMaxBytesToConvert); // Unicode转Ansi
	void UnicodeToUTF8(LPCWSTR srcStr, LPSTR destStr, UINT nMaxBytesToConvert); // Unicode转UTF-8
	void AnsiToUnicode(LPCSTR srcStr, LPWSTR destStr, UINT nMaxWordsToConvert); // Ansi转Unicode
	void WcscpyPtr(LPWSTR* dstPtrAddr, LPCWSTR src); // 拷贝至Heap空间中的连续字符串
	void WcscpyArray(LPWSTR dstArr, size_t sizeInWords, LPCWSTR src); // 拷贝至Stack空间中的字符串（字符数组）
	bool CStringStartWith(const CString & cs, LPCWSTR startStr); // CString对象是否以某一字符（串）开始
	bool CStringEndWith(const CString & cs, LPCWSTR endStr); // CString对象是否以某一字符（串）结尾
};

