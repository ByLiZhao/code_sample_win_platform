// csv_writer.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#pragma pack(push, 8)
struct data {
	bool is_succeed;
	BYTE counter;
	float X;
	float Y;
	float Z;
};
#pragma pack(pop) 

class CSV_writer {
public:
	std::ofstream my_ofstream;
private:
	HANDLE my_handle = INVALID_HANDLE_VALUE;
	int file_descriptor = -1;
	FILE * my_file = nullptr;	//FILE type is actually a IO buff.
	const static unsigned int fl = 256;
public:
	explicit CSV_writer(const TCHAR * file_name_) {
		//get current directory
		TCHAR current_path[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, current_path);

		TCHAR filename[fl]{ 0 };
		_tcscat_s(filename, file_name_);
		_tcscat_s(filename, _T(".csv"));
		if (current_path[_tcslen(current_path) - 1] != _T('\\') && _tcslen(current_path) < MAX_PATH - 1) {
			_tcscat_s(current_path, _T("\\"));
		}
		else {
			throw std::exception("path length exceeding limit.");
		}

		if (_tcslen(current_path) + _tcslen(filename) + 1 < MAX_PATH) {
			_tcscat_s(current_path, filename);
		}
		else {
			//current path exceeds the max path length defined in MAX_PATH
			throw std::exception("path length exceeding limit.");
		}

		this->my_handle = CreateFile(
			current_path,
			GENERIC_READ | GENERIC_WRITE,	//access permit, both read and write
			0,			//cannot be shared and cannot be opened again until the handle to the file or device is closed
			nullptr,	//returned handle can not be inherited by child process
			CREATE_ALWAYS,	//always create a new file, overwrite old one if it exists
			FILE_ATTRIBUTE_NORMAL,
			nullptr
		);

		if (my_handle != INVALID_HANDLE_VALUE) {
			int file_descriptor = _open_osfhandle((intptr_t)my_handle, _O_TEXT);
			if (file_descriptor != -1) {
				this->my_file = _fdopen(file_descriptor, "w");
				if (this->my_file != nullptr) {
					this->my_ofstream = std::ofstream(this->my_file);

				}
			}
		}
	}

	~CSV_writer() {
		// Closes stream, file, file_descriptor, and file_handle.
		this->my_ofstream.flush();
		this->my_ofstream.close();
		this->my_file = nullptr;
		this->file_descriptor = -1;
		this->my_handle = INVALID_HANDLE_VALUE;
	}
};

int main(int argc, char* argv[])
{
	data imu_data_x64;
	CSV_writer csv_writer(L"memory_layout");

	void * start_ptr = &(imu_data_x64);
	void * first_ptr = &(imu_data_x64.is_succeed);
	void * second_ptr = &(imu_data_x64.counter);
	void * third_ptr = &(imu_data_x64.X);
	void * fourth_ptr = &(imu_data_x64.Y);
	void * fifth_ptr = &(imu_data_x64.Z);


	int offset1 = offsetof(data, is_succeed);
	int offset2 = offsetof(data, counter);
	int offset3 = offsetof(data, X);
	int offset4 = offsetof(data, Y);
	int offset5 = offsetof(data, Z);

	int s1 = sizeof(imu_data_x64.is_succeed);
	int s2 = sizeof(imu_data_x64.counter);
	int s3 = sizeof(imu_data_x64.X);
	int s4 = sizeof(imu_data_x64.Y);
	int s5 = sizeof(imu_data_x64.Z);

	char t1[] = "Bool";
	char t2[] = "BYTE";
	char t345[] = "Float";

	csv_writer.my_ofstream << "Memory layout of struct IMU_data_x64, size of IMU_data_x64 is " << sizeof(imu_data_x64) << "\n";
	csv_writer.my_ofstream << "Type,\t" << "Size,\t" << "Offset,\t" <<"Address\n";
	csv_writer.my_ofstream << t1 << ",\t" << s1 << ",\t" << offset1 << ",\t" << start_ptr << ",\n";
	csv_writer.my_ofstream << t2 << ",\t" << s2 << ",\t" << offset2 << ",\t" << second_ptr << ",\n";
	csv_writer.my_ofstream << t345 << ",\t" << s3 << ",\t" << offset3 << ",\t" << third_ptr << ",\n";
	csv_writer.my_ofstream << t345 << ",\t" << s4 << ",\t" << offset4 << ",\t" << fourth_ptr << ",\n";
	csv_writer.my_ofstream << t345 << ",\t" << s5 << ",\t" << offset5 <<  ",\t"<< fifth_ptr << ",\n";
	getchar();
	return 0;
}

