#pragma once
#include "stdafx.h"
#include <cstdint>

#pragma pack(push, 8)
struct data {
	bool is_OK;
	BYTE counter;
	float X;
	float Y;
	float Z;
};
#pragma pack(pop) 

class device {
public:
	data data_set1[160];
	data data_set2[160];
	BYTE RGGB_image[320][320];	//RGGB image from the camera
	
public:
	device();	//constructor
	void	update_data();	//receive data and update public fields
	~device();	//destructor
private:
	
};

extern device* device_object;
