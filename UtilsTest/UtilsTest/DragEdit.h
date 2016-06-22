#pragma once
#include "afxwin.h"
class CDragEdit :public CEdit { DECLARE_DYNAMIC(CDragEdit)
public:
	CDragEdit();
	virtual ~CDragEdit();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDropFiles(HDROP hDropInfo);
};

