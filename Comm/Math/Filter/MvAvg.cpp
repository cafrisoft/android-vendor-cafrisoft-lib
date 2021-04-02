#include <Comm/Global/BuildOptions.h>
#include <Comm/Math/Filter/MvAvg.hpp>

/*
*   A[n] = (a[0] + a[1] ----- a[n-1]) / n
*   A[n+1] = (a[0] + a[1] ----- a[n-1] + a[n]) / (n + 1)
* 
*   n * A[n] = (a[0] + a[1] ----- a[n-1])                <1>
*   (n+1) * A[n+1] = (a[0] + a[1] ----- a[n-1] + a[n])   <2> 

*   <2> - <1>
*       (n+1) * A[n+1]  - n * A[n] = a[n]
*       (n+1) * A[n+1]  = a[n]  +  n * A[n]
*        A[n+1]  = ( a[n]  +  n * A[n] )  / (n+1) 
*/ 


namespace Comm {
    namespace Math {
        namespace Filter {

            MvAvg::MvAvg(int windowWidth) : Base(windowWidth) 
            ,_A(0.0f)
            {
            
            }

            MvAvg::~MvAvg() {
            
            }


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
            */
            float MvAvg::Calculate(float inputValue) {
            
                float n1 = (float)this->GetCurDataCount();
                float n0 = (n1 - 1.0f);
                assert(n1 >= 1.0f);
                float An1 = (inputValue + n0 * _A) / n1;

                _A = An1;

                return _A;
            }

            /*
            * Case2) One Input and One Output
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
            *
            */

            float MvAvg::Calculate(float inputValue, float outputValue) {

                float n = (float)this->GetCurDataCount();
                assert(n >= 1.0f);
                float An1 = (inputValue - outputValue + n * _A) / n;

                _A = An1;

                return _A;
            };

        };//namespace Filter
    };//namespace Math
};//namespace Comm

