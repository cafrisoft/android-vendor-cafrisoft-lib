#ifndef COMM_UTILS_QUEUE_HPP__
#define COMM_UTILS_QUEUE_HPP__

#include <Comm/Global/BuildOptions.h>
#include <Comm/OAL/Lock.hpp>
#include <Comm/OAL/CriticalSection.hpp>
#include <Comm/OAL/Mutex.hpp>
#include <Comm/OAL/Cond.hpp>
#include <Comm/OAL/Semaphore.hpp>

namespace Comm {
    namespace Utils {

        template<class Type> class Queue
        {
        private:
            std::queue<Type> _Queue;
            std::shared_ptr<OAL::CriticalSection> _CsIF;
            
        public:
            Queue() {
                _CsIF = OAL::CriticalSection::CreateObject();
                assert(_CsIF);
            }

            virtual ~Queue() {
            
            }

            void Flush() {
                OAL::Lock lock(_CsIF);
                while (!_Queue.empty()) {
                    _Queue.pop();
                }
            }

            bool IsEmpty() {
                OAL::Lock lock(_CsIF);
                return _Queue.empty();
            }

            int Count() {
                OAL::Lock lock(_CsIF);
                return (int)_Queue.size();
            }


            virtual bool Push(Type t) {
                OAL::Lock lock(_CsIF);
                _Queue.push(t);
                return true;
            }

            virtual Type Pop() {
                OAL::Lock lock(_CsIF);
                Type t = _Queue.front();
                _Queue.pop();
                return t;
            }
            
            virtual Type Peek() {
                OAL::Lock lock(_CsIF);
                Type t = _Queue.front();
                return t;
            }

        };

        template<class Type> class SyncQueue :  public Queue<Type> 
        {
        private:
            std::shared_ptr<OAL::Semaphore> _Semaphore;
            

        public:
            SyncQueue() {
                _Semaphore = OAL::Semaphore::CreateObject(0 /*initial value*/);
                assert(_Semaphore);
            }

            virtual bool Push(Type t) {

                bool bflag;

                
                bflag = Queue<Type>::Push(t);
                _Semaphore->Increase();

                return bflag;
            }

            virtual Type Pop() {

                Type t;

                _Semaphore->Wait_Decrease();

                if (!this->IsEmpty()) {
                    t = Queue<Type>::Pop();
                }

                return t;
            }
        };
        
    };
};

#endif
