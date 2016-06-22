#include "stdafx.h"
#include "DragEdit.h"

IMPLEMENT_DYNAMIC(CDragEdit, CEdit)

CDragEdit::CDragEdit() {}
CDragEdit::~CDragEdit() {}

BEGIN_MESSAGE_MAP(CDragEdit, CEdit)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

void CDragEdit::OnDropFiles(HDROP hDropInfo) {
	if(hDropInfo){
		int nDragFileCount; 
		nDragFileCount = DragQueryFileW(hDropInfo, 0xFFFFFFFF, NULL, 0);
		// hDrop Handle sent by Message
		// iFile File index
		//         if pass 0xFFFFFFFF, function returns count of files being dragged.
		//         if pass 0 to n, function will copy the file path indexed by iFile to lpszFile
		// lpszFile save the specified file name.
		//		   if pass NULL, function returns count of files being dragged.
		//		   if NOT NULL, function returns length of file path in word. 
		// cch size of lpszFile in word.
		if(nDragFileCount == 1) {
			wchar_t wcsPath[MAX_PATH + 1] = {0};
			int len;
			len = DragQueryFileW(hDropInfo, 0, wcsPath, MAX_PATH);
			SetWindowTextW(wcsPath); // Display file path in the Edit
		}
		else{
			AfxMessageBox(L"Once only one file can be dragged!");
		}
	}
}