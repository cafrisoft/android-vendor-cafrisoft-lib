#ifndef COMM_UTILS_VECTOR_HPP__
#define COMM_UTILS_VECTOR_HPP__

#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Lock.hpp>
#include <Comm/OAL/CriticalSection.hpp>
#include <Comm/OAL/Mutex.hpp>
#include <Comm/OAL/Cond.hpp>

namespace Comm {
    namespace Utils {

        template<class Type> class Vector
        {
        private:
            std::vector<Type> _Vector;
            std::shared_ptr<OAL::CriticalSection> _CsIF;
            
        public:
            Vector() {
                _CsIF = OAL::CriticalSection::CreateObject();
                assert(_CsIF);
            }

            virtual ~Vector() {
            
            }

            int GetItemCount() {
                OAL::Lock lock(_CsIF);
                return (int)_Vector.size();
            }

            virtual bool PushBack(Type t) {
                OAL::Lock lock(_CsIF);
                _Vector.push_back(t);
                return true;
            }
            
        };

    };
};

#endif
