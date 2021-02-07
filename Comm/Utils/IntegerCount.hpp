#ifndef COMM_UTILS_INTEGERCOUNT_HPP__
#define COMM_UTILS_INTEGERCOUNT_HPP__

#include <Comm/Base/Object.hpp>

namespace Comm {
    namespace Utils{

        class IntegerCount : public Base::Object {

        private:
            int _CountPerSec;
            int _Count;
            int _CountTotal;
            long long _BeforeTick;
          
        public:
            IntegerCount();

        public:
            void Reset();
            void Increase(int inc = 1, bool isAutoReset=true);
            void operator += (int inc);
            int GetCountPerSec();
            int GetCountTotal();
            int GetCount();
        };

        
    }; //namespace Socket {
}; // namespace Comm {

#endif //COMM_DATAEX_PRODUCER_HPP__
