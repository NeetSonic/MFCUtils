//----------------------------
// SmartListBox for MFC project
// Author:neetsonic
// Date:2016/6/27
//----------------------------

//------------------------------------
// ���ԣ�
//      1.�����Զ������ı��������ɹ�����
//------------------------------------

#pragma once

class SmartListBox : public CListBox {
	DECLARE_DYNAMIC(SmartListBox)
	DECLARE_MESSAGE_MAP()

public:
	SmartListBox(void) {};
	virtual ~SmartListBox(void) {};
	void SetHSBar(void); // ����ˮƽ���������

	// �������·����Ա����ˮƽ������������һ�·�������Զ�����ˮƽ������
	int AddString(LPCTSTR lpszItem);
	int InsertString(int nIndex, LPCTSTR lpszItem);
};