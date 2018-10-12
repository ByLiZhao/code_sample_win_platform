// test_main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include "..\deleter\deleter.h"

auto destroy = [](factory * p) {
	factory::destroy(p);
};

class ref_counted_factory_object{
private: 
	std::shared_ptr <factory> fsptr;
public:
	ref_counted_factory_object() :fsptr(factory::create(), destroy) {
		//some other code
	};
};
int main()
{
	ref_counted_factory_object obj;
	//do something with obj
    return 0;
}

