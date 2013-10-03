// GuMessageDlg.h : header file
//

#pragma once
#include "DICThreadPool/DICThreadPool.h"
#include "WorkerThread/WorkerThread.h"
// CGuMessageDlg dialog
class CGuMessageDlg : public CDialog
{
// Construction
public:
	CGuMessageDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GUMESSAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void InitData();
	void BeginPullData();
	CDICThreadPool m_ThreadPool;
public:
	int m_nview_cnt;
	CRITICAL_SECTION m_lock;
public:
	afx_msg void OnDestroy();
};
