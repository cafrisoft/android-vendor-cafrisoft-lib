#include <Comm/Global/BuildOptions.h>
#include <Comm/Utils/Counter.hpp>
#include <Comm/OAL/Lock.hpp>

namespace Comm {
    namespace Utils {

        #define CHECK_IDX(idx) ((idx>=0) && (idx<_ArrayCount))

        Counter::Counter(int maxCount) :
            _ValueArray(NULL)
            , _ArrayCount(maxCount)
        {
            _Cs = Comm::OAL::CriticalSection::CreateObject();
            assert(_Cs);

            _ValueArray = new int[_ArrayCount];
            assert(_ValueArray);

            this->Reset();
        }
        
        Counter::~Counter() {

            if (_ValueArray) {
                delete[] _ValueArray;
            }
        }

        void Counter::Reset() {
        
            for (int i = 0; i < _ArrayCount; i++) {
                _ValueArray[i] = 0;
            }
        }

        void Counter::Inc(int idx) {
        
            Comm::OAL::Lock lock(_Cs);

            if (CHECK_IDX(idx)) {
                _ValueArray[idx]++;
            }
        }

        void Counter::Dec(int idx) {
        
            Comm::OAL::Lock lock(_Cs);

            if (CHECK_IDX(idx)) {
                _ValueArray[idx]--;
            }
        }

        int Counter::GetValue(int idx) {

            int value = -1;
            Comm::OAL::Lock lock(_Cs);

            if (CHECK_IDX(idx)) {
                value = _ValueArray[idx];
            }

            return value;
        }
    };
};

