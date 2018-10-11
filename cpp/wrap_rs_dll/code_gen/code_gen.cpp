// code_gen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char * argv[])
{
	if (argc != 3) {
		std::cout << "the program takes only 2 parameters." << std::endl;
		return -1;
	}
	std::string source_file = argv[1];
	std::string dest_file = argv[2];
	struct stat stat_s;
	if (source_file == dest_file) {
		std::cout << "the source file and destination file have the same name. No OP." << std::endl;
		return 1;
	}
	//check the source file
	int rc = stat(source_file.c_str(), &stat_s);
	if (rc != 0) {
		std::cout << "Error: could not find the file." << std::endl;
		return -2;
	}
	if (!(stat_s.st_mode & _S_IREAD)) {
		std::cout << "Error: don't have permission to read the source file." << std::endl;
		return -3;
	}
	//check dest dir
	char dest_dir[MAX_PATH];
	char dest_name[128];
	char ext[16];
	_splitpath_s(dest_file.c_str(), nullptr, 0, dest_dir, MAX_PATH, dest_name, 128, ext, 16);

	struct stat stat_d;
	rc = stat(dest_dir, &stat_d);
	if (rc != 0) {
		std::cout << "Error: the directory specified does not exist." << std::endl;
		return -4;
	}
	if (!(stat_d.st_mode & _S_IFDIR)) {
		std::cout << "Error: the directory specified is not a directory." << std::endl;
		return -5;
	}
	if (!(stat_d.st_mode & _S_IWRITE)) {
		std::cout << "Error: have no permission to write to the directory." << std::endl;
	}

	//create dest file
	HANDLE my_handle = CreateFileA(dest_file.c_str(),    // name of the file
		GENERIC_WRITE, // open for writing
		0,             // sharing mode, none in this case
		0,             // use default security descriptor
		CREATE_ALWAYS, // overwrite if exists
		FILE_ATTRIBUTE_NORMAL,
		0);
	if (my_handle == INVALID_HANDLE_VALUE)
	{
		std::cout << "create file failed";
		return -6;
	}
	std::ofstream dest_ofstream;
	//int file_descriptor = _open_osfhandle((intptr_t)my_handle, _O_APPEND);//when dest file meant be binary.
	int file_descriptor = _open_osfhandle((intptr_t)my_handle, _O_TEXT);//when dest file is text file
	if (file_descriptor != -1) {
		FILE* my_file = _fdopen(file_descriptor, "w");
		if (my_file != nullptr) {
			dest_ofstream = std::ofstream(my_file);
		}
	}
	if (!dest_ofstream) {
		std::cout << "failed to open source file to read." << std::endl;
		return -8;
	}
	std::ifstream source_ifstream(source_file.c_str(), std::ifstream::binary);
	if (!source_ifstream) {
		std::cout << "failed to open destination file to write." << std::endl;
		return -9;
	}
	//For test purpose
	/*char c;
	while (source_ifstream.get(c)) {
		dest_ofstream << c;
	}*/
	char source_dir[MAX_PATH];
	char source_name[128];
	char sext[16];
	_splitpath_s(source_file.c_str(), nullptr, 0, source_dir, MAX_PATH, source_name, 128, sext, 16);
	dest_ofstream << "#pragma once\n";
	dest_ofstream << "const char* type =" << "\"" << source_name << sext << "\";\n";
	dest_ofstream << "const size_t size =" << stat_s.st_size << ";\n";
	dest_ofstream << "const unsigned char p[] = {";
	char c;
	source_ifstream.get(c);
	dest_ofstream << (int)c;
	while (source_ifstream.get(c)) {
		dest_ofstream << "," << (int)c;
	}
	dest_ofstream << "};";
	source_ifstream.close();
	dest_ofstream.close();
	return 0;
}

