
// UtilsTestDlg.h : ͷ�ļ�
//

#pragma once
#include "SmartEdit.h"
#include "SmartComboBox.h"
#include "SmartListCtrl.h"


// CUtilsTestDlg �Ի���
class CUtilsTestDlg : public CDialogEx
{
// ����
public:
	CUtilsTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UTILSTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	SmartEdit m_editTest1;
	virtual void OnOK();
	SmartComboBox m_cbTest1;
	SmartListCtrl m_lcTest1;
};
