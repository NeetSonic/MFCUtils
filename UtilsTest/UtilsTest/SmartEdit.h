//----------------------------
// SmartEdit for MFC project
// Author:neetsonic
// Date:2016/6/22
//----------------------------

//--------------------------------
// ���ԣ�
//      1.��ͨ����ק�ļ���ȡ�ļ���
//--------------------------------

#pragma once

class SmartEdit : public CEdit {
	DECLARE_DYNAMIC(SmartEdit)
	DECLARE_MESSAGE_MAP()

public:
	SmartEdit();
	virtual ~SmartEdit();
	void HighlightFileName(); // �����ļ���
	afx_msg void OnDropFiles(HDROP hDropInfo); // ��ק�ļ���Ϣ
};


