#ifndef COMM_API_BASE_H__
#define COMM_API_BASE_H__

#define  INIT_INSTANCE_ON_API_FUNC(ClassType, handle, pSharedPtr, sharedObject) \
    std::shared_ptr<ClassType>* pSharedPtr = (std::shared_ptr<ClassType>*)handle; \
    assert(pSharedPtr); \
    std::shared_ptr<ClassType> sharedObject = *pSharedPtr; \
    assert(sharedObject); 

extern "C" Bool MyAPIObjectDestroy(COMM_HANDLE hdl);

#endif
