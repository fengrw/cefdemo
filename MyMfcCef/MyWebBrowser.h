#pragma once

#include "include/cef_client.h"
#include "include/cef_app.h"

class CWebClient : public CefClient,public CefLifeSpanHandler
{
public:
	CWebClient();
	~CWebClient();

	//CefLifeSpanHandler����Browser������������
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE { return this; }
	// CefLifeSpanHandler methods:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& target_url,
		const CefString& target_frame_name,
		WindowOpenDisposition target_disposition,
		bool user_gesture,
		const CefPopupFeatures& popupFeatures,
		CefWindowInfo& windowInfo,
		CefRefPtr<CefClient>& client,
		CefBrowserSettings& settings,
		bool* no_javascript_access) OVERRIDE;
	//virtual bool DoClose(CefRefPtr<CefBrowser> browser);
	//virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser);

	//Browser
	CefRefPtr<CefBrowser> GetBrowser() { return m_cefBrowser; }

private:
	CefRefPtr<CefBrowser> m_cefBrowser;
	//CefWindowHandle m_BrowserHwnd;

	// ���CEF��SP�麯��
	IMPLEMENT_REFCOUNTING(CWebClient);
};
