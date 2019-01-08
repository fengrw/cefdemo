#pragma once

#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_v8.h"
#include "MyV8HanderEx.h"

class CAppRender : public CefApp, public CefRenderProcessHandler
{
	public:
		CAppRender();
		~CAppRender();
		CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE
		{
			return this;
		}
		//virtual void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) OVERRIDE;
		
		void OnContextCreated(
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefV8Context> context);

		void OnWebKitInitialized() OVERRIDE;
/*
		bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message) OVERRIDE;
			*/
private:
		IMPLEMENT_REFCOUNTING(CAppRender);
};

