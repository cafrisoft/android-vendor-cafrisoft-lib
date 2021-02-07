#include <Comm/Global/BuildOptions.h>
#include <Comm/Base/Object.hpp>
#include <Comm/API/Base.h>


extern "C" Bool MyAPIObjectDestroy(COMM_HANDLE hdl) {

    Bool bRet = False;
    std::shared_ptr<Comm::Base::Object>* pSharedPtr = (std::shared_ptr<Comm::Base::Object>*)hdl;
    if (pSharedPtr) {
        delete pSharedPtr;
        bRet = True;
    }
    return bRet;
}


