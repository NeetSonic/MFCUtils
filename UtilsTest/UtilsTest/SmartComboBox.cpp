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
	// ComboCoxʵ����ListBox��Edit���ֿؼ���϶��ɣ����Բ���ֱ��ʹ��OnChar�����������ַ�
	// ��ΪĬ�Ͽؼ�������ListBox�����м������Ϣ�ᱻListBoxԤ��������ﲻ�����������Ч��
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor == CTLCOLOR_EDIT) { // ��ȡComboBox�е�Edit�ؼ�
		// SubclassWindow���Զ�̬�����໯һ�����ڲ��ҽ��Լ����ӵ���CWnd����
		if(!m_edit.GetSafeHwnd()) m_edit.SubclassWindow(pWnd->GetSafeHwnd());    
		return CComboBox::OnCtlColor(pDC, pWnd, nCtlColor); 
	}
	return hbr;
}
void SmartComboBox::OnDropFiles(HDROP hDropInfo) {
	m_edit.OnDropFiles(hDropInfo);
}
