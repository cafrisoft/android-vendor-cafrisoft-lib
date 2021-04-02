#ifndef COMM_MATH_FILTER_BASE_HPP__
#define COMM_MATH_FILTER_BASE_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/Utils/Queue.hpp>

namespace Comm {
    namespace Math {
        namespace Filter {

            class Base : public Comm::Base::Object {

            private:
                std::shared_ptr<Comm::OAL::CriticalSection> _Cs;
                Comm::Utils::Queue<float> _ValueQueue;
                float _ResultValue;
                int _WindowWidth;

            public:
                Base(int windowWidth);
                virtual ~Base();

            protected:
                virtual float Calculate(float inputValue, float outputValue) = 0;
                virtual float Calculate(float inputValue) = 0;
                int GetCurDataCount();

            public:
                bool IsFull();
                float Add(float value);
                float Get();
            };

        };//namespace Filter
    };//namespace Math
};//namespace Comm

#endif  //#ifndef COMM_MATH_FILTER_BASE_HPP__


