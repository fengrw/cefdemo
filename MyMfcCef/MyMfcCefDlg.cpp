
// MyMfcCefDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MyMfcCef.h"
#include "MyMfcCefDlg.h"
#include "afxdialogex.h"

#include "MyAppRender.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyMfcCefDlg 对话框
CMyMfcCefDlg::CMyMfcCefDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MYMFCCEF_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyMfcCefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyMfcCefDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_GO, &CMyMfcCefDlg::OnBnClickedBtnGo)
	ON_BN_CLICKED(IDC_BTN_FORWARD, &CMyMfcCefDlg::OnBnClickedBtnForward)
	ON_BN_CLICKED(IDC_BTN_BACK, &CMyMfcCefDlg::OnBnClickedBtnBack)
END_MESSAGE_MAP()


// CMyMfcCefDlg 消息处理程序

BOOL CMyMfcCefDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//申请cef对象内存
	CefRefPtr<CWebClient> client(new CWebClient());
	m_WebClient = client;

	CefRefPtr<CAppRender> app(new CAppRender());
	
	//全局CEF配置
	CefSettings settings;
	CefSettingsTraits::init(&settings);
	settings.multi_threaded_message_loop = true;
	//settings.remote_debugging_port = 8088;//如果不定义，则不能运行调试工具
	settings.single_process = false;

	//传递参数
	CefMainArgs mainArgs;
	CefRefPtr<CefApp> cefApp;
	cefApp = app;
	CefInitialize(mainArgs, settings, cefApp, NULL);

	RECT rect;
	GetClientRect(&rect);
	RECT rectnew = rect;
	rectnew.top = rect.top + 50;
	rectnew.bottom = rect.bottom;
	rectnew.left = rect.left;
	rectnew.right = rect.right;
	CefWindowInfo winInfo;
	winInfo.SetAsChild(GetSafeHwnd(), rectnew);

	std::wstring domain = L"C:\\Users\\Administrator\\Desktop\\login.html";

	//创建一个Browser实例
	CefBrowserSettings browserSettings;
	CefBrowserHost::CreateBrowser(winInfo, m_WebClient, domain.c_str(), browserSettings, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyMfcCefDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyMfcCefDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyMfcCefDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyMfcCefDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CefShutdown();
	CDialog::OnClose();
}


void CMyMfcCefDlg::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
}


void CMyMfcCefDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	RECT rect;
	GetClientRect(&rect);

	if (m_WebClient.get())
	{
		CefRefPtr<CefBrowser> browser = m_WebClient->GetBrowser();
		if (browser)
		{
			CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
			::MoveWindow(hwnd, 0,50, rect.right - rect.left, rect.bottom - 50, true);
		}
	}
}


void CMyMfcCefDlg::OnBnClickedBtnGo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strUrl;
	GetDlgItem(IDC_EDIT_URL)->GetWindowText(strUrl);
	if (strUrl.Trim().IsEmpty())
	{
		AfxMessageBox(_T("请输入网址"));
		return;
	}
	const CefString cefStrUrl(strUrl);
	m_WebClient->GetBrowser()->GetMainFrame()->LoadURL(cefStrUrl);
}


void CMyMfcCefDlg::OnBnClickedBtnForward()
{
	// TODO: 在此添加控件通知处理程序代码
	m_WebClient->GetBrowser()->GoForward();
}


void CMyMfcCefDlg::OnBnClickedBtnBack()
{
	// TODO: 在此添加控件通知处理程序代码
	m_WebClient->GetBrowser()->GoBack();
}
