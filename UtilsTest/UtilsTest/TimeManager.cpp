//----------------------------
// TimeManager for MFC project
// Author:neetsonic
// Date:2016/6/30
//----------------------------

#include "stdafx.h"
#include "TimeManager.h"

#define WCS_GET_YEAR L"%Y"
#define WCS_GET_FOMATTED_TIME L"%Y/%m/%d %H:%M:%S"

int TimeManager::GetCurrYear() {
	return ::_wtoi(CTime::GetCurrentTime().Format(WCS_GET_YEAR).GetString());
}
CString TimeManager::GetCurrTimeFormattedString() {
	return CTime::GetCurrentTime().Format(WCS_GET_FOMATTED_TIME);
}