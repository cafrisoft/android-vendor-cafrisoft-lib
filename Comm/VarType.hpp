#ifndef COMM_VARTYPE_HPP
#define COMM_VARTYPE_HPP

#include <Comm/Global/BuildOptions.h>

namespace Comm {
    namespace VarType {

        enum class CPP {
            void_ = 0,
            char_,
            unsigned_char_,
            short_,
            unsiged_short,
            int_,
            unsigned_int_,
            long_long_,
            unsigned_long_long_,
            float_,
            double_,
            std_string_, 
            time_t_,
            MaxCnt
        };

        enum class SQL {

            //문자형 데이타 타입
            Char = 0,    //fixed string data Type (최대 255byte)  지정될 길이보다 짧은 데이타 입력시 나머지 공간 공백처리 
            VarChar,     //가변길이타입 (최대 65535byte) 지정될 길이보다 짧은 데이타 입력시 나머지 공간은 채우지 않는다.  
            TinyText,    //string data type (max 255b byte) 
            Text,        //string data type (max 65535 byte) 
            MediumText,  //string data type (max 16777215 byte) 
            LongText,    //string data type (max 4294967295 byte) 

            //숫자형 데이타 타입
            TinyUint,     // 1byte 0~255
            TinyInt,     // 1byte  -128 ~ 127
            SmallUint,   // 2byte  0~65535
            SmallInt,    // 2byte  -32768 ~ 327677
            MediumInt,   // 3byte  -8388608 ~ +8388607 또는 0 ~ 16777215
            Uint,        // 4byte   0 ~ 16777215     
            Int,         // 4byte  -8388608 ~ +8388607
            BigUint,     // 8byte
            BigInt,      // 8byte
            Float,       // 부동 소수형 데이타 타입 (4byte)
            Decimal,     // 고정 소수형 데이타 타입 (길이 + 1byte)  소수점 사용 형태 
            Double,      // 부동 소수형 데이타 타입 (8byte)

            //날짜형 데이타 타입
            Date,       // 날짜 (년도, 월, 일) 형태의 기간 표현 데이타 타입 (3byte)
            Time,       // 시간 (시, 분, 초) 형태의 기간 표현 데이타 타입 (3byte)
            DateTime,   // 날짜와 시간 형태의 기간 표현 데이타 타입 (8byte)
            TimeStamp,  // 날짜와 시간 형태의 기간 표현 데이타 타입 (4yte)  시스템 변경시 자동으로 그 날짜와 시간이 저장됨
            Year,        // 년도 표현 

            //Binary Data Type
            Binary,     // Char형태의 이진 데이타 타입 Max 255Byte
            VarBinary,  // Var Char형태의 이진 데이타 타입 (최대 65535byte)
            TinyBlob,   // 이진 데이타타입, ( Max : 255byte)
            Blob,       // 이진 데이타타입, ( Max : 65535byte)
            MediumBlob, // 이진 데이타타입, ( Max : 16777215byte)
            LongBlob,   // 이진 데이타타입, ( Max : 16777215byte)

        };

        CPP StringToCppVarType(std::string strVarType);
        std::string VarTypeName(CPP vt);

        SQL StringToSqlVarType(std::string strDataType);
        std::string VarTypeName(SQL vt);

        long long VarTypeMaxByteSize(SQL vt);

    };  // namespace VarType
}; // namespace Comm

#endif

