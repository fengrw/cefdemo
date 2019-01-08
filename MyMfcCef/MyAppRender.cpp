#include "stdafx.h"
#include "MyAppRender.h"
#include <tchar.h>


CAppRender::CAppRender()
{

}

CAppRender::~CAppRender()
{

}

void CAppRender::OnContextCreated(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context)
{
	OutputDebugString(L"CAppRender::OnContextCreated, create window binding\r\n");

	// Retrieve the context's window object.
	CefRefPtr<CefV8Value> object = context->GetGlobal();

	// Create the "NativeLogin" function.
	CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction("NativeLogin", new CV8HandlerEx(this));

	// Add the "NativeLogin" function to the "window" object.
	object->SetValue("NativeLogin", func, V8_PROPERTY_ATTRIBUTE_NONE);
}

void CAppRender::OnWebKitInitialized()
{
	OutputDebugString(L"ClientAppRenderer::OnWebKitInitialized, create js extensions\r\n");
	std::string app_code =
		"var app;"
		"if (!app)"
		"    app = {};"
		"(function() {"
		"    app.GetId = function() {"
		"        native function GetId2();"
		"        return GetId2();"
		"    };"
		"    app.GetIp = function() {"
		"        native function GetIp();"
		"        return GetIp();"
		"    };"
		"})();";
	CefRegisterExtension("v8/app", app_code, new CV8HandlerEx(this));
}