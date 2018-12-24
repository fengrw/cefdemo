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
	////ͬһ��browser�����ж�����������(���µ��Ӵ��ڴ�����,�������ڵ�ǰ������תʱ�����.),��ʱ����ֵ���ܻᱻ������һЩ�ر���.���˽���ο��ٷ�demo.
	//if (CefCurrentlyOn(TID_UI))
	//{
	//	return true;
	//}
	return false;	//����trueȡ���ر�
}
void CWebClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	if (m_BrowserHwnd == browser->GetHost()->GetWindowHandle())
	{// ��������ڱ����ٵĻ�,browserָ����ΪNULL.
		m_cefBrowser = NULL;
	}
}

*/