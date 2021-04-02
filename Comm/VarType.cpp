#include <Comm/Global/BuildOptions.h>
#include <Comm/VarType.hpp>
#include <Comm/Utils/StringTool.hpp>

namespace Comm {
    namespace VarType {
                        
        CPP StringToCPPVarType(std::string strVarType);

        std::string VarTypeName(CPP vt) {
            
            const char* s = "";

            switch (vt) {
                
                case CPP::void_:            s = typeid(void).name(); break;
                case CPP::char_:            s = typeid(char).name(); break;
                case CPP::unsigned_char_:   s = typeid(unsigned char).name(); break;
                case CPP::short_:           s = typeid(short).name(); break;
                case CPP::unsiged_short:    s = typeid(unsigned short).name(); break;
                case CPP::int_:             s = typeid(int).name(); break;
                case CPP::unsigned_int_:    s = typeid(unsigned int).name(); break;
                case CPP::long_long_:       s = typeid(long long).name(); break;
                case CPP::unsigned_long_long_:  s = typeid(unsigned long long).name(); break;
                case CPP::float_:           s = typeid(float).name(); break;
                case CPP::double_:          s = typeid(double).name(); break;
                    
                case CPP::std_string_:      
                    //s = typeid(std::string).name();  //  class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>,  Too long
                    s = "std::string";
                    break;
                case CPP::time_t_:          s = typeid(time_t).name(); break;
                default:
                    assert(0);
            }
                
            return s;
        }


        SQL StringToSqlVarType(std::string strDataType) {

            SQL vt = SQL::Char;
            char szDataType[128];

            strcpy(szDataType, strDataType.c_str());
            Comm::Utils::StringTool::MakeLower(szDataType);


            if (strcmp(szDataType, "bigint") == 0) {
                vt = SQL::BigInt;
            }
            else if (strcmp(szDataType, "int") == 0) {
                vt = SQL::Int;
            }
            else if (strcmp(szDataType, "date") == 0) {
                vt = SQL::Date;
            }
            else {
                assert(0);
            }

            return vt;
        }

        std::string VarTypeName(SQL vt) {

            const char* s = "";

            switch (vt) {

                //문자형 데이타 타입
                case SQL::Char:        s = "Char"; break; //fixed string data Type (최대 255byte)  지정될 길이보다 짧은 데이타 입력시 나머지 공간 공백처리 
                case SQL::VarChar:     s = "VarChar"; break;      //가변길이타입 (최대 65535byte) 지정될 길이보다 짧은 데이타 입력시 나머지 공간은 채우지 않는다.  
                case SQL::TinyText:    s = "TinyText"; break;     //string data type (max 255b byte) 
                case SQL::Text:        s = "Text"; break;         //string data type (max 65535 byte) 
                case SQL::MediumText:  s = "MidumText"; break;   //string data type (max 16777215 byte) 
                case SQL::LongText:    s = "LongText"; break;     //string data type (max 4294967295 byte) 

                //숫자형 데이타 타입
                case SQL::TinyInt:     s = "TinyInt"; break;      // 1byte  -128 ~ 127,  0~255
                case SQL::SmallInt:    s = "SmallInt"; break;     // 2byte  -32768 ~ 327677,  0~65535
                case SQL::MediumInt:   s = "MediumInt"; break;    // 3byte  -8388608 ~ +8388607 또는 0 ~ 16777215
                case SQL::Int:         s = "Int"; break;          // 4byte  -8388608 ~ +8388607 또는 0 ~ 16777215        
                case SQL::BigInt:      s = "BigInt"; break;       // 8byte
                case SQL::Float:       s = "Float"; break;        // 부동 소수형 데이타 타입 (4byte)
                case SQL::Decimal:     s = "Decimal"; break;      // 고정 소수형 데이타 타입 (길이 + 1byte)  소수점 사용 형태 
                case SQL::Double:      s = "Double"; break;       // 부동 소수형 데이타 타입 (8byte)

                //날짜형 데이타 타입
                case SQL::Date:        s = "Date"; break;        // 날짜 (년도, 월, 일) 형태의 기간 표현 데이타 타입 (3byte)
                case SQL::Time:        s = "Time"; break;        // 시간 (시, 분, 초) 형태의 기간 표현 데이타 타입 (3byte)
                case SQL::DateTime:    s = "DateTime"; break;    // 날짜와 시간 형태의 기간 표현 데이타 타입 (8byte)
                case SQL::TimeStamp:   s = "TimeStamp"; break;   // 날짜와 시간 형태의 기간 표현 데이타 타입 (4yte)  시스템 변경시 자동으로 그 날짜와 시간이 저장됨
                case SQL::Year:        s = "Year"; break;         // 년도 표현 

                //Binary Data Type
                case SQL::Binary:      s = "Binary"; break;      // Char형태의 이진 데이타 타입 Max 255Byte
                case SQL::VarBinary:   s = "VarBinary"; break;   // Var Char형태의 이진 데이타 타입 (최대 65535byte)
                case SQL::TinyBlob:    s = "TinyBlob"; break;    // 이진 데이타타입, ( Max : 255byte)
                case SQL::Blob:        s = "Blob"; break;        // 이진 데이타타입, ( Max : 65535byte)
                case SQL::MediumBlob:  s = "MediumBlob"; break;  // 이진 데이타타입, ( Max : 16777215byte)
                case SQL::LongBlob:    s = "LongBlob"; break;    // 이진 데이타타입, ( Max : 16777215byte)


            default:
                assert(0);
            }

            return s;
        }

        long long VarTypeMaxByteSize(SQL vt) {
            
            long long maxDataByteSize = -1;

            switch (vt) {

                //문자형 데이타 타입
            case SQL::Char:        maxDataByteSize = 1; break; //fixed string data Type (최대 255byte)  지정될 길이보다 짧은 데이타 입력시 나머지 공간 공백처리 
            case SQL::VarChar:     maxDataByteSize = 65536; break;      //가변길이타입 (최대 65535byte) 지정될 길이보다 짧은 데이타 입력시 나머지 공간은 채우지 않는다.  
            case SQL::TinyText:    maxDataByteSize = 256; break;     //string data type (max 255b byte) 
            case SQL::Text:        maxDataByteSize = 65536; break;         //string data type (max 65535 byte) 
            case SQL::MediumText:  maxDataByteSize = 16777215+1; break;   //string data type (max 16777215 byte) 
            case SQL::LongText:    maxDataByteSize = 4294967295LL+1; break;     //string data type (max 4294967295 byte) 

            //숫자형 데이타 타입
            case SQL::TinyUint:
            case SQL::TinyInt:     maxDataByteSize = 1; break;      // 1byte  -128 ~ 127,  0~255
            
            case SQL::SmallUint:
            case SQL::SmallInt:    maxDataByteSize = 2; break;     // 2byte  -32768 ~ 327677,  0~65535

            case SQL::MediumInt:   maxDataByteSize = 3; break;    // 3byte  -8388608 ~ +8388607 또는 0 ~ 16777215
            
            case SQL::Uint:  
            case SQL::Int:         maxDataByteSize = 4; break;          // 4byte  -8388608 ~ +8388607 또는 0 ~ 16777215        
            
            case SQL::BigUint:
            case SQL::BigInt:      maxDataByteSize = 8; break;       // 8byte
            case SQL::Float:       maxDataByteSize = 4; break;        // 부동 소수형 데이타 타입 (4byte)
            case SQL::Decimal:     maxDataByteSize = 255; break;      // 고정 소수형 데이타 타입 (길이 + 1byte)  소수점 사용 형태 
            case SQL::Double:      maxDataByteSize = 8; break;       // 부동 소수형 데이타 타입 (8byte)

            //날짜형 데이타 타입
            case SQL::Date:        maxDataByteSize = 8; break;        // 날짜 (년도, 월, 일) 형태의 기간 표현 데이타 타입 (3byte)
            case SQL::Time:        maxDataByteSize = 8; break;        // 시간 (시, 분, 초) 형태의 기간 표현 데이타 타입 (3byte)
            case SQL::DateTime:    maxDataByteSize = 8; break;    // 날짜와 시간 형태의 기간 표현 데이타 타입 (8byte)
            case SQL::TimeStamp:   maxDataByteSize = 8; break;   // 날짜와 시간 형태의 기간 표현 데이타 타입 (4yte)  시스템 변경시 자동으로 그 날짜와 시간이 저장됨
            case SQL::Year:        maxDataByteSize = 8; break;         // 년도 표현 

            //Binary Data Type
            case SQL::Binary:      maxDataByteSize = 256; break;      // Char형태의 이진 데이타 타입 Max 255Byte
            case SQL::VarBinary:   maxDataByteSize = 65536; break;   // Var Char형태의 이진 데이타 타입 (최대 65535byte)
            case SQL::TinyBlob:    maxDataByteSize = 256; break;    // 이진 데이타타입, ( Max : 255byte)
            case SQL::Blob:        maxDataByteSize = 65536; break;        // 이진 데이타타입, ( Max : 65535byte)
            case SQL::MediumBlob:  maxDataByteSize = 16777216; break;  // 이진 데이타타입, ( Max : 16777215byte)
            case SQL::LongBlob:    maxDataByteSize = 16777216; break;    // 이진 데이타타입, ( Max : 16777215byte)


            default:
                assert(0);
            }

            return maxDataByteSize; 

        }


    };  // namespace VarType
}; // namespace Comm



