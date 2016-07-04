//----------------------------
// TimeManager for MFC project
// Author:neetsonic
// Date:2016/6/30
//----------------------------

//--------------------------------------
// 特性：
//      1.可获取当前时间（单独的年月日等）
//      2.可生成表示时间的字符串
//--------------------------------------

#pragma once
namespace TimeManager {
	int GetCurrYear();
	CString GetCurrTimeFormattedString();
};

