// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DELETER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DELETER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DELETER_EXPORTS
#define DELETER_API __declspec(dllexport)
#else
#define DELETER_API __declspec(dllimport)
#endif

// This class is exported from the deleter.dll
class DELETER_API factory
{
public:
	static factory * create() ;
	static void destroy(factory*) ;
	factory(const factory &) = delete;
	factory & factory:: operator= (const factory &) = delete;
	// TODO: add your methods here.
private:
	char * p;
	factory();
	~factory();
};


