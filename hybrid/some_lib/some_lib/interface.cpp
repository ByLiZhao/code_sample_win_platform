#include "stdafx.h"
#include "interface.h"
#include "some_lib.h"


device* device_object = nullptr;

int64_t   init_device() {
	try {
		if (device_object != nullptr) {
			device_object = new (device_object) device();
		}
		else {
			device_object = new device();
		}
		return 1;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return -1;
	}
}

int64_t  get_data(
	INT_PTR RGGB_image_ptr,
	INT_PTR data_set1_ptr,
	INT_PTR data_set2_ptr
) {
	try {
		device_object->update_data();
		memcpy((void *)RGGB_image_ptr, device_object->RGGB_image, 320 * 320);
		memcpy((void *)data_set1_ptr, device_object->data_set1, sizeof(data) * 160);
		memcpy((void *)data_set2_ptr, device_object->data_set2, sizeof(data) * 160);
		return 1;
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
		return -1;
	}
}

int64_t   clean_up_device() {
	try {
		if (device_object != nullptr) {
			delete device_object;
		}
		device_object = nullptr;
		return 1;
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
		return -1;
	}
}