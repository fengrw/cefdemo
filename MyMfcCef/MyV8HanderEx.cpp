#include "stdafx.h"
#include "MyV8HanderEx.h"
#include <tchar.h>
#include <Windows.h>

CV8HandlerEx::CV8HandlerEx(CefRefPtr<CefApp> app)
{
	this->app = app;
}

CV8HandlerEx::~CV8HandlerEx()
{

}

bool CV8HandlerEx::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{

	if (name == "NativeLogin")
	{
		if (arguments.size() == 2)
		{

			CefString strUser = arguments.at(0)->GetStringValue();
			CefString strPassword = arguments.at(1)->GetStringValue();

			TCHAR szLog[256] = { 0 };
			_stprintf_s(szLog, 256, L"user - %s, password - %s\r\n", strUser.c_str(), strPassword.c_str());

			OutputDebugString(szLog);

			::MessageBoxW(NULL, szLog, L"µÇÂ½", MB_OK);

			////TODO: doSomething() in native way
			//
			//retval = CefV8Value::CreateInt(0);
			//MessageBox(NULL, szLog, L"ssss", NULL);

			//CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create("login_msg");

			// Retrieve the argument list object.
			//<CefListValue> args = msg->GetArgumentList();

			// Populate the argument values.
			/*args->setsize(2);
			args->setstring(0, struser);
			args->setstring(1, strpassword);*/

			// Send the process message to the browser process.
			//CefV8Context::GetCurrentContext()->GetBrowser()->SendProcessMessage(PID_BROWSER, msg);

		}
		else
		{
			retval = CefV8Value::CreateInt(1);
		}

		return true;
	}
	else if (name == "GetId2")
	{
		if (arguments.size() == 0)
		{
			// execute javascript 
			// just for test
			OutputDebugString(L"askdhjakshdkjahskjdhakjshdkjahsdkjah");

			CefRefPtr<CefFrame> frame = CefV8Context::GetCurrentContext()->GetBrowser()->GetMainFrame();
			frame->ExecuteJavaScript("alert('Hello, I came from native world.')", frame->GetURL(), 0);

			// return to JS
			retval = CefV8Value::CreateString("asdasd");
			return true;
		}
	}
	else if (name == "GetIp")
	{
		if (arguments.size() == 0)
		{
			// execute javascript 

			// return to js
			retval = CefV8Value::CreateString("192.168.1.2");
			return true;
		}
	}
	return false;
}