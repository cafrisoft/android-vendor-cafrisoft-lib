// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LIBTED_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LIBTED_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LIBTED_EXPORTS
#define LIBTED_API __declspec(dllexport)
#else
#define LIBTED_API __declspec(dllimport)
#endif

// This class is exported from the dll
class LIBTED_API ClibTED {
public:
	ClibTED(void);
	// TODO: add your methods here.
};

extern LIBTED_API int nlibTED;

LIBTED_API int fnlibTED(void);
