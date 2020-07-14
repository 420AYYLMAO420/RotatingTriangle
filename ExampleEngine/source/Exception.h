#pragma once

#include <comdef.h>
#include <sstream>

#pragma comment(lib, "comsuppw.lib")

static std::wstringstream wstream;

//macro used for outputting the error message of function that returns HRESULT to the Output window
#define HRESULT_LOG(x) HRESULT hr = x; _com_error err(hr); wstream << "\n" << __FILE__ << "(" << __LINE__ << "): " << err.ErrorMessage(); OutputDebugStringW(wstream.str().c_str());