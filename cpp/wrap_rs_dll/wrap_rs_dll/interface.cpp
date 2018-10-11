#include "stdafx.h"
#include"interface.h"
#include"def.h"
void get_type(const char ** tp) {
	*tp = type;
}
void get_data(void ** p_) {
	*p_ = (void *)p;
}
void get_size(const size_t ** sp) {
	*sp = &size;
}