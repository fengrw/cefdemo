
// MyMfcCefDlg.h: 头文件
//

#pragma once

#include "MyWebBrowser.h"

// CMyMfcCefDlg 对话框
class CMyMfcCefDlg : public CDialog
{
// 构造
public:
	CMyMfcCefDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYMFCCEF_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CefRefPtr<CWebClient> m_WebClient;
	CefRefPtr<CefApp>spApp;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnGo();
	afx_msg void OnBnClickedBtnForward();
	afx_msg void OnBnClickedBtnBack();
};
