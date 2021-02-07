#ifndef COMM_OAL_SYNCOBJECT_HPP
#define COMM_OAL_SYNCOBJECT_HPP

#include <Comm/Base/Object.hpp>

namespace Comm {
    namespace OAL {

        class SyncObject : Base::Object {
        
        protected:
            SyncObject();
            virtual ~SyncObject();

        public:
            virtual void Lock() = 0;
            virtual void Unlock() = 0;
        };

    }; //end of namespace Net
}; //end of namespace Comm

#endif // #ifndef TESYSNETCLIENT_HPP

