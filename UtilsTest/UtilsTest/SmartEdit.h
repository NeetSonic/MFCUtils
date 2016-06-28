//----------------------------
// SmartEdit for MFC project
// Author:neetsonic
// Date:2016/6/22
//----------------------------

//--------------------------------
// ���ԣ�
//      1.��ͨ����ק�ļ���ȡ�ļ���
//      2.�ɽ���ȡ�����ļ������ø���
//      3.��������������ַ�
//--------------------------------

#pragma once

// ���ڴ�������ַ���������Ҫ�Ĳ���
typedef struct LimitInputData {
	bool(*pfnFilter)(UINT nChar); // ���������ַ��ĺ���ָ��
	LPWSTR lpszBallonTipTitle;    // �û�����Ƿ��ַ�ʱ������ʾ�ı���
	LPWSTR lpszBallonTipText;     // �û�����Ƿ��ַ�ʱ������ʾ������
	INT ttiIcon;				  // �û�����Ƿ��ַ�ʱ������ʾ������
}LIMIT_INPUT_DATA;

class SmartEdit : public CEdit {
	DECLARE_DYNAMIC(SmartEdit)
	DECLARE_MESSAGE_MAP()

private:
	bool m_bLimitInput; // �Ƿ����������ַ�
	LIMIT_INPUT_DATA* m_pData; // �����ַ���������Ҫ�Ĳ���

public:
	SmartEdit();
	virtual ~SmartEdit();
	void HighlightFileName(); // �����ļ���������ѡ�У�
	void LimitInput(bool(*pfnFilter)(UINT nChar), LPCWSTR lpszBallonTipTitle = NULL, LPCWSTR lpszBallonTipText = NULL, INT ttiIcon = TTI_NONE); // ����������ַ���ֻ��һ��NULL������ʾȡ������
	void WriteLog(LPCWSTR lpszLog, bool bPrintTime = true); // ��ӡ��־��Ϣ��������Ϊ��־��Ŀؼ�ʹ�ã�
	afx_msg void OnDropFiles(HDROP hDropInfo); // ��ק�ļ�����Ϣ
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags); // ���������ַ�����Ϣ
};
