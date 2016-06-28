//--------------------------------
// SmartComboBox for MFC project
// Author:neetsonic
// Date:2016/6/25
//--------------------------------

//--------------------------------
// ���ԣ�
//      1.��SmartEdit���󸽼ӵ�ComboBox�ϣ��滻��CEdit������SmartEdit�����й���
//--------------------------------

#pragma once
#include "SmartEdit.h"
#include "MFCUtils.h"
using namespace MFCUtils;

class SmartComboBox : public CComboBox {
	DECLARE_DYNAMIC(SmartComboBox)
	DECLARE_MESSAGE_MAP()

public:
	SmartEdit m_edit;
	SmartComboBox();
	virtual ~SmartComboBox();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor); // ���ƿؼ�����Ϣ
	afx_msg void OnDropFiles(HDROP hDropInfo); // ��ק�ļ�����Ϣ
};


