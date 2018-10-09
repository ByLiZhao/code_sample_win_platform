#include"stdafx.h"
#include"some_lib.h"

device::device() {
	//initilization of a new device object
}

device:: ~device() {
	// clean up code goes here
}
void device::update_data() {
	// pull data from the underlying device, and update public fields
	memset(this->data_set1, 1, 160 * sizeof(data));
	memset(this->data_set1, 1, 160 * sizeof(data));
	memset(this->RGGB_image, 128, 320 * 320);
}

