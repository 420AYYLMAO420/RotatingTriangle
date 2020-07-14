#pragma once

#if defined(EE_BUILD_DLL)
	#define EXAPI __declspec(dllexport)
#elif defined(EE_DLL)
	#define EXAPI __declspec(dllimport)
#endif