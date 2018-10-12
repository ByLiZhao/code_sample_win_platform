// deleter.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "deleter.h"

// This is the constructor of a class that has been exported.
// see deleter.h for the class definition
factory * factory::create()
{
	return new factory();
}
void factory::destroy(factory * fp)  {
	fp->~factory();
}
factory::factory() {
	char*p = new char[100];
}

factory::~factory() {
	delete[] p;
}