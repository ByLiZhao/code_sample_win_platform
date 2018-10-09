#pragma once
#include <cstdint>
#include <iostream>
#include "some_lib.h"
//interface exposed to dll user
#ifdef SOME_LIB_DLL_EXPORTS
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif


extern "C" {
	API int64_t  __cdecl init_device();
	API int64_t __cdecl get_data(
		INT_PTR RGGB_image_ptr,
		INT_PTR data_set1_ptr,
		INT_PTR data_set2_ptr
	);
	API int64_t  __cdecl clean_up_device();	//
}