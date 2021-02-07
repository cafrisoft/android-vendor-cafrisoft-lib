// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LIBTESYSNET_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LIBTESYSNET_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LIBTESYSNET_EXPORTS
#define LIBTESYSNET_API __declspec(dllexport)
#else
#define LIBTESYSNET_API __declspec(dllimport)
#endif

// This class is exported from the dll
class LIBTESYSNET_API ClibTESysNet {
public:
	ClibTESysNet(void);
	// TODO: add your methods here.
};

extern LIBTESYSNET_API int nlibTESysNet;

LIBTESYSNET_API int fnlibTESysNet(void);
