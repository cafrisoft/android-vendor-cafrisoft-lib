// libTED.cpp : Defines the exported functions for the DLL.
//

#include "framework.h"
#include "libTED.h"


// This is an example of an exported variable
LIBTED_API int nlibTED=0;

// This is an example of an exported function.
LIBTED_API int fnlibTED(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
ClibTED::ClibTED()
{
    return;
}
