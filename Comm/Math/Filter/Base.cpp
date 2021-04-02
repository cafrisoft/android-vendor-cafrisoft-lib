#include <Comm/Global/BuildOptions.h>
#include <Comm/Math/Filter/Base.hpp>

namespace Comm {
    namespace Math {
        namespace Filter {

            Base::Base(int windowWidth) :
                _ResultValue(0)
                , _WindowWidth(windowWidth)
            {

                _Cs = Comm::OAL::CriticalSection::CreateObject();
                assert(_Cs);

            }

            Base::~Base() {

            }

            int Base::GetCurDataCount() {
            
                return _ValueQueue.Count();
            }

            bool Base::IsFull() {
            
                return (_ValueQueue.Count() >= _WindowWidth) ? true : false;
            }
            
            float Base::Add(float value) {

                Comm::OAL::Lock lock(_Cs);

                
                _ValueQueue.Push(value);

                if (_ValueQueue.Count() > _WindowWidth) {
                
                    float outputValue = _ValueQueue.Pop();
                    _ResultValue = this->Calculate(value, outputValue);
                }
                else {
                    _ResultValue = this->Calculate(value);
                }

                return _ResultValue;
            }

            
            float Base::Get() {

                return _ResultValue;
            }

        }; //namespace Filter
    };//namespace Math
};//namespace Comm

