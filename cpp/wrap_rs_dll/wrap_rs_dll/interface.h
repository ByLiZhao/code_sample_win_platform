#pragma once
#ifdef WRAP_RS_DLL_EXPORTS
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif


extern "C" {
	API void __cdecl get_type(const char ** tp);
	API void __cdecl get_data(void ** p_);
	API void __cdecl get_size(const size_t ** sp);
}
