//--------------------------------
// StringManager for MFC project
// Author:neetsonic
// Date:2016/6/29
//--------------------------------

#include "stdafx.h"
#include "StringManager.h"
#include "MFCUtils.h"

static void UnicodeToCharset(LPCWSTR srcStr, LPSTR destStr, UINT nMaxBytesToConvert, UINT type) {
	int nLen = ::WideCharToMultiByte(type, 0, srcStr, -1, NULL, 0, NULL, NULL); // 得到转换后的字符串长度，包含结尾符\0
	if(nLen) {
		char* p = new char[nLen];
		::WideCharToMultiByte(type, 0, srcStr, -1, p, nLen, NULL, NULL); // 转换
		::strcpy_s(destStr, nMaxBytesToConvert, p); // 在nMaxBytesToConvert范围内遇到\0则停止拷贝
		MFCUtils::MultiDelete(p);
	}
}
static bool CStringWith(const CString & cs, LPCWSTR str, bool bStart) {
	int nLen;
	nLen = ::wcslen(str);
	if(cs.GetLength() < nLen) return false;
	return !(((bStart) ? cs.Left(nLen) : cs.Right(nLen)).Compare(str));
}

void StringManager::UnicodeToAnsi(LPCWSTR srcStr, LPSTR destStr, UINT nMaxBytesToConvert) {
	UnicodeToCharset(srcStr, destStr, nMaxBytesToConvert, CP_ACP);
}
void StringManager::UnicodeToUTF8(LPCWSTR srcStr, LPSTR destStr, UINT nMaxBytesToConvert) {
	UnicodeToCharset(srcStr, destStr, nMaxBytesToConvert, CP_UTF8);
}
void StringManager::AnsiToUnicode(LPCSTR srcStr, LPWSTR destStr, UINT nMaxWordsToConvert) {
	int nLen = ::MultiByteToWideChar(CP_ACP, 0, srcStr, -1, NULL, 0);
	if(nLen) {
		wchar_t * pUnicode = new wchar_t[nLen];
		::MultiByteToWideChar(CP_ACP, 0, srcStr, -1, pUnicode, nLen);
		::wcscpy_s(destStr, nMaxWordsToConvert, pUnicode);
		MFCUtils::MultiDelete(pUnicode);
	}
}
void StringManager::WcscpyPtr(LPWSTR* dstPtrAddr, LPCWSTR src) {
	ASSERT(src);
	size_t nLen;
	nLen = ::wcslen(src) + 1;
	MFCUtils::MultiDelete(*dstPtrAddr);
	(*dstPtrAddr) = new wchar_t[nLen];
	::wmemset(*dstPtrAddr, 0, nLen);
	::wcscpy_s(*dstPtrAddr, nLen, src);
}
void StringManager::WcscpyArray(LPWSTR dstArr, size_t sizeInWords, LPCWSTR src) {
	ASSERT(dstArr && src);
	size_t nLen;
	nLen = ::wcslen(src) + 1;
	ASSERT(sizeInWords >= nLen);
	::wmemset(dstArr, 0, sizeInWords);
	::wcscpy_s(dstArr, nLen, src);
}
bool StringManager::CStringStartWith(const CString & cs, LPCWSTR startStr) {
	return CStringWith(cs, startStr, true);
}
bool StringManager::CStringEndWith(const CString & cs, LPCWSTR endStr) {
	return CStringWith(cs, endStr, false);
}