// test_dll_main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"..\wrap_rs_dll\interface.h"

int main()
{
	const char * file_name = nullptr;
	get_type(&file_name);
	std::ofstream fs(file_name, std::ofstream::binary | std::ofstream::trunc);
	const size_t * sp=nullptr;
	get_size(&sp);
	void *p=nullptr;
	get_data(&p);
	unsigned char * cp = static_cast<unsigned char *>(p);
	for (size_t i = 0; i < *sp; ++i) {
		fs.put(*cp++);
	}
    return 0;
}

