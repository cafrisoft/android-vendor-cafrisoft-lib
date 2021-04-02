#ifndef COMM_MATH_FILTER_MVAVG_HPP__
#define COMM_MATH_FILTER_MVAVG_HPP__

#include <Comm/Math/Filter/Base.hpp>

/*
* Case1) Only Input
* 
*   A[n] = (a[0] + a[1] ----- a[n-1]) / n
*   A[n+1] = (a[0] + a[1] ----- a[n-1] + a[n]) / (n + 1)
*
*   n * A[n] = (a[0] + a[1] ----- a[n-1])                <1>
*   (n+1) * A[n+1] = (a[0] + a[1] ----- a[n-1] + a[n])   <2>

*   <2> - <1>
*       (n+1) * A[n+1]  - n * A[n] = a[n]
*       (n+1) * A[n+1]  = a[n]  +  n * A[n]
*        A[n+1]  = ( a[n]  +  n * A[n] )  / (n+1)
* 
* 
*  Case2) One Input and One Output
*
*   A[n] = (a[0] + a[1] ----- a[n-1]) / n
*   A[n+1] = (a[1] ----- a[n-1] + a[n]) / n
*
*   n * A[n] = (a[0] + a[1] ----- a[n-1])     <1>
*   n * A[n+1] = (a[1] ----- a[n-1] + a[n])   <2>

*   <2> - <1>
*       n * A[n+1]  - n * A[n] = a[n] - a[0]
*       n * A[n+1]  = a[n] - a[0] +  n * A[n]
*       A[n+1]  = ( a[n] - a[0] +  n * A[n] )  / n
*/

namespace Comm {
    namespace Math {
        namespace Filter {

            class MvAvg : public Base {
            
            private:
                float _A;

            public:
                MvAvg(int windowWidth);
                virtual ~MvAvg();

            protected:
                virtual float Calculate(float inputValue);
                virtual float Calculate(float inputValue, float outputValue);

            };

        };//namespace Filter
    };//namespace Math
};//namespace Comm

#endif  //#ifndef COMM_MATH_FILTER_BASE_HPP__


