#include <Comm/Global/BuildOptions.h>
#include <Comm/Utils/IntegerCount.hpp>
#include <Comm/OAL/System.hpp>

namespace Comm {
    namespace Utils {

        IntegerCount::IntegerCount() :
            _CountPerSec(0)
            , _Count(0)
            , _CountTotal(0)
        {
            this->Reset();
        }

        void IntegerCount::Reset() {
            _Count = 0;
            _BeforeTick = OAL::System::GetTickCount64();
        }

        void IntegerCount::Increase(int inc, bool isAutoReset) {

            _Count += inc;
            _CountTotal += inc;

            if (isAutoReset) {
                long long curTick = OAL::System::GetTickCount64();
                if ((curTick - _BeforeTick) > 1000LL)
                {
                    _CountPerSec = _Count;
                    Reset();
                }
            }
        }

        void IntegerCount::operator += (int inc) {
            _Count += inc;
            _CountTotal += inc;
        }

        int IntegerCount::GetCountPerSec() {
            return _CountPerSec;
        }

        int IntegerCount::GetCountTotal() {
            return _CountTotal;
        }

        int IntegerCount::GetCount() {
            return _Count;
        }


    }; //namespace Utils {
}; // namespace Comm {


