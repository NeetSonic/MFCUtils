//--------------------------------
// SmartComboBox for MFC project
// Author:neetsonic
// Date:2016/6/25
//--------------------------------

#include "stdafx.h"
#include "SmartComboBox.h"

IMPLEMENT_DYNAMIC(SmartComboBox, CComboBox)

BEGIN_MESSAGE_MAP(SmartComboBox, CComboBox)
	ON_WM_CTLCOLOR()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

SmartComboBox::SmartComboBox() {}
SmartComboBox::~SmartComboBox() {}

HBRUSH SmartComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	// ComboCox实际由ListBox和Edit两种控件组合而成，所以不能直接使用OnChar来限制输入字符
	// 因为默认控件焦点在ListBox，所有键入的消息会被ListBox预处理掉，达不到限制输入的效果
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor == CTLCOLOR_EDIT) { // 获取ComboBox中的Edit控件
		// SubclassWindow可以动态的子类化一个窗口并且将自己附加到该CWnd对象
		if(!m_edit.GetSafeHwnd()) m_edit.SubclassWindow(pWnd->GetSafeHwnd());    
		return CComboBox::OnCtlColor(pDC, pWnd, nCtlColor); 
	}
	return hbr;
}
void SmartComboBox::OnDropFiles(HDROP hDropInfo) {
	m_edit.OnDropFiles(hDropInfo);
}
