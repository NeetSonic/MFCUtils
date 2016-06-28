
// UtilsTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UtilsTest.h"
#include "UtilsTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUtilsTestDlg �Ի���



CUtilsTestDlg::CUtilsTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUtilsTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUtilsTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEST_1, m_editTest1);
	DDX_Control(pDX, IDC_COMBO_TEST1, m_cbTest1);
	DDX_Control(pDX, IDC_LIST_TEST1, m_lcTest1);
}

BEGIN_MESSAGE_MAP(CUtilsTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CUtilsTestDlg ��Ϣ�������

BOOL CUtilsTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	double pColWidth[] = {0.1, 0.2, 0.5, 0.1, 0.1};
	LPCWSTR lpszHeaders[] = {L"h1", L"h2", L"h3", L"h4", L"h5"};
	m_lcTest1.Init(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_FLATSB, 5, LVCFMT_LEFT, lpszHeaders, pColWidth);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUtilsTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CUtilsTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUtilsTestDlg::OnOK() {}
