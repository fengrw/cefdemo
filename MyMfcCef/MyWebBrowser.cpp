#include "stdafx.h"
#include "MyWebBrowser.h"

CWebClient::CWebClient()
{

}

CWebClient::~CWebClient()
{

}

void CWebClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
		m_cefBrowser = browser;
}

bool CWebClient::OnBeforePopup(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	const CefString& target_url,
	const CefString& target_frame_name,
	WindowOpenDisposition target_disposition,
	bool user_gesture,
	const CefPopupFeatures& popupFeatures,
	CefWindowInfo& windowInfo,
	CefRefPtr<CefClient>& client,
	CefBrowserSettings& settings,
	bool* no_javascript_access)
{
	browser->GetMainFrame()->LoadURL(target_url);
	return true; 
}
/*
bool CWebClient::DoClose(CefRefPtr<CefBrowser> browser)
{
	////同一个browser可能有多个浏览器窗口(在新的子窗口打开链接,而不是在当前窗口跳转时会出现.),此时返回值可能会被用来做一些特别处理.想了解请参考官方demo.
	//if (CefCurrentlyOn(TID_UI))
	//{
	//	return true;
	//}
	return false;	//返回true取消关闭
}
void CWebClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	if (m_BrowserHwnd == browser->GetHost()->GetWindowHandle())
	{// 浏览器窗口被销毁的话,browser指针置为NULL.
		m_cefBrowser = NULL;
	}
}

*/