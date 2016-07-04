#pragma once
#include "stdafx.h"

//--------------------标准数字定义--------------------
#ifndef MAX_PATH
#define MAX_PATH 260
#endif /* MAX_PATH */
#define BUFFER_SIZE MAX_PATH

//--------------------字符（串）操作相关定义--------------------
#define WCS_EMPTY L""
#define WCS_SPACE L" "
#define WCS_SEMICOLON L";"
#define WCS_BACK_SLASH L"\\"
#define WCS_NEW_LINE L"\r\n"
#define WCS_LEFT_SQUARE_BRACKET L"["
#define WCS_RIGHT_SQUARE_BRACKET L"]"
#define WCS_WILD_CARD L"*.*"
#define WCHAR_UPPER_CASE_A L'A'
#define WCHAR_PLUS L'+'
#define WCHAR_MINUS L'-'
#define WCHAR_MULTIPLE L'*'
#define WCHAR_DIVIDE L'/'
#define WCHAR_LEFT_BRACKET L'('
#define WCHAR_RIGHT_BRACKET L')'
#define WCHAR_LEFT_BRACKET_DOUBLE_BYTE L'（'
#define WCHAR_RIGHT_BRACKET_DOUBLE_BYTE L'）'
#define WCHAR_DOT L'.'
#define WCHAR_BACK_SLASH '\\'

//--------------------常用宏操作--------------------
#define CHECK_HRESULT(hr, errMsgW) if(FAILED(hr)) AfxMessageBox(errMsgW)
#define WCS_SIZE_IN_WORDS(buff) (sizeof(buff) / sizeof(wchar_t))

//--------------------MFC控件常用相关值定义--------------------
#define LC_NOT_SELECTED -1
#define CSTRING_FIND_FAILED -1

namespace MFCUtils {
	template<class T>
	void SingleDelete(T & t) {
		if(t) {
			delete t;
			t = NULL;
		}
	}
	template<class T>
	void MultiDelete(T & t) {
		if(t) {
			delete[]t;
			t = NULL;
		}
	}
}

