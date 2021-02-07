#ifndef COMM_UTILS_COUNTER_HPP__
#define COMM_UTILS_COUNTER_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/OAL/CriticalSection.hpp>


namespace Comm {
    namespace Utils {

        class Counter : public Comm::Base::Object {

        private:
            std::shared_ptr<Comm::OAL::CriticalSection> _Cs;
            int* _ValueArray;
            int _ArrayCount;

        public:
            Counter(int maxCount);
            virtual ~Counter();
            
            void Reset();

        public:
            void Inc(int idx);
            void Dec(int idx);
            int GetValue(int idx);
        };
    };
};

#endif
