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

                //������ ����Ÿ Ÿ��
                case SQL::Char:        s = "Char"; break; //fixed string data Type (�ִ� 255byte)  ������ ���̺��� ª�� ����Ÿ �Է½� ������ ���� ����ó�� 
                case SQL::VarChar:     s = "VarChar"; break;      //��������Ÿ�� (�ִ� 65535byte) ������ ���̺��� ª�� ����Ÿ �Է½� ������ ������ ä���� �ʴ´�.  
                case SQL::TinyText:    s = "TinyText"; break;     //string data type (max 255b byte) 
                case SQL::Text:        s = "Text"; break;         //string data type (max 65535 byte) 
                case SQL::MediumText:  s = "MidumText"; break;   //string data type (max 16777215 byte) 
                case SQL::LongText:    s = "LongText"; break;     //string data type (max 4294967295 byte) 

                //������ ����Ÿ Ÿ��
                case SQL::TinyInt:     s = "TinyInt"; break;      // 1byte  -128 ~ 127,  0~255
                case SQL::SmallInt:    s = "SmallInt"; break;     // 2byte  -32768 ~ 327677,  0~65535
                case SQL::MediumInt:   s = "MediumInt"; break;    // 3byte  -8388608 ~ +8388607 �Ǵ� 0 ~ 16777215
                case SQL::Int:         s = "Int"; break;          // 4byte  -8388608 ~ +8388607 �Ǵ� 0 ~ 16777215        
                case SQL::BigInt:      s = "BigInt"; break;       // 8byte
                case SQL::Float:       s = "Float"; break;        // �ε� �Ҽ��� ����Ÿ Ÿ�� (4byte)
                case SQL::Decimal:     s = "Decimal"; break;      // ���� �Ҽ��� ����Ÿ Ÿ�� (���� + 1byte)  �Ҽ��� ��� ���� 
                case SQL::Double:      s = "Double"; break;       // �ε� �Ҽ��� ����Ÿ Ÿ�� (8byte)

                //��¥�� ����Ÿ Ÿ��
                case SQL::Date:        s = "Date"; break;        // ��¥ (�⵵, ��, ��) ������ �Ⱓ ǥ�� ����Ÿ Ÿ�� (3byte)
                case SQL::Time:        s = "Time"; break;        // �ð� (��, ��, ��) ������ �Ⱓ ǥ�� ����Ÿ Ÿ�� (3byte)
                case SQL::DateTime:    s = "DateTime"; break;    // ��¥�� �ð� ������ �Ⱓ ǥ�� ����Ÿ Ÿ�� (8byte)
                case SQL::TimeStamp:   s = "TimeStamp"; break;   // ��¥�� �ð� ������ �Ⱓ ǥ�� ����Ÿ Ÿ�� (4yte)  �ý��� ����� �ڵ����� �� ��¥�� �ð��� �����
                case SQL::Year:        s = "Year"; break;         // �⵵ ǥ�� 

                //Binary Data Type
                case SQL::Binary:      s = "Binary"; break;      // Char������ ���� ����Ÿ Ÿ�� Max 255Byte
                case SQL::VarBinary:   s = "VarBinary"; break;   // Var Char������ ���� ����Ÿ Ÿ�� (�ִ� 65535byte)
                case SQL::TinyBlob:    s = "TinyBlob"; break;    // ���� ����ŸŸ��, ( Max : 255byte)
                case SQL::Blob:        s = "Blob"; break;        // ���� ����ŸŸ��, ( Max : 65535byte)
                case SQL::MediumBlob:  s = "MediumBlob"; break;  // ���� ����ŸŸ��, ( Max : 16777215byte)
                case SQL::LongBlob:    s = "LongBlob"; break;    // ���� ����ŸŸ��, ( Max : 16777215byte)


            default:
                assert(0);
            }

            return s;
        }

        long long VarTypeMaxByteSize(SQL vt) {
            
            long long maxDataByteSize = -1;

            switch (vt) {

                //������ ����Ÿ Ÿ��
            case SQL::Char:        maxDataByteSize = 1; break; //fixed string data Type (�ִ� 255byte)  ������ ���̺��� ª�� ����Ÿ �Է½� ������ ���� ����ó�� 
            case SQL::VarChar:     maxDataByteSize = 65536; break;      //��������Ÿ�� (�ִ� 65535byte) ������ ���̺��� ª�� ����Ÿ �Է½� ������ ������ ä���� �ʴ´�.  
            case SQL::TinyText:    maxDataByteSize = 256; break;     //string data type (max 255b byte) 
            case SQL::Text:        maxDataByteSize = 65536; break;         //string data type (max 65535 byte) 
            case SQL::MediumText:  maxDataByteSize = 16777215+1; break;   //string data type (max 16777215 byte) 
            case SQL::LongText:    maxDataByteSize = 4294967295LL+1; break;     //string data type (max 4294967295 byte) 

            //������ ����Ÿ Ÿ��
            case SQL::TinyUint:
            case SQL::TinyInt:     maxDataByteSize = 1; break;      // 1byte  -128 ~ 127,  0~255
            
            case SQL::SmallUint:
            case SQL::SmallInt:    maxDataByteSize = 2; break;     // 2byte  -32768 ~ 327677,  0~65535

            case SQL::MediumInt:   maxDataByteSize = 3; break;    // 3byte  -8388608 ~ +8388607 �Ǵ� 0 ~ 16777215
            
            case SQL::Uint:  
            case SQL::Int:         maxDataByteSize = 4; break;          // 4byte  -8388608 ~ +8388607 �Ǵ� 0 ~ 16777215        
            
            case SQL::BigUint:
            case SQL::BigInt:      maxDataByteSize = 8; break;       // 8byte
            case SQL::Float:       maxDataByteSize = 4; break;        // �ε� �Ҽ��� ����Ÿ Ÿ�� (4byte)
            case SQL::Decimal:     maxDataByteSize = 255; break;      // ���� �Ҽ��� ����Ÿ Ÿ�� (���� + 1byte)  �Ҽ��� ��� ���� 
            case SQL::Double:      maxDataByteSize = 8; break;       // �ε� �Ҽ��� ����Ÿ Ÿ�� (8byte)

            //��¥�� ����Ÿ Ÿ��
            case SQL::Date:        maxDataByteSize = 8; break;        // ��¥ (�⵵, ��, ��) ������ �Ⱓ ǥ�� ����Ÿ Ÿ�� (3byte)
            case SQL::Time:        maxDataByteSize = 8; break;        // �ð� (��, ��, ��) ������ �Ⱓ ǥ�� ����Ÿ Ÿ�� (3byte)
            case SQL::DateTime:    maxDataByteSize = 8; break;    // ��¥�� �ð� ������ �Ⱓ ǥ�� ����Ÿ Ÿ�� (8byte)
            case SQL::TimeStamp:   maxDataByteSize = 8; break;   // ��¥�� �ð� ������ �Ⱓ ǥ�� ����Ÿ Ÿ�� (4yte)  �ý��� ����� �ڵ����� �� ��¥�� �ð��� �����
            case SQL::Year:        maxDataByteSize = 8; break;         // �⵵ ǥ�� 

            //Binary Data Type
            case SQL::Binary:      maxDataByteSize = 256; break;      // Char������ ���� ����Ÿ Ÿ�� Max 255Byte
            case SQL::VarBinary:   maxDataByteSize = 65536; break;   // Var Char������ ���� ����Ÿ Ÿ�� (�ִ� 65535byte)
            case SQL::TinyBlob:    maxDataByteSize = 256; break;    // ���� ����ŸŸ��, ( Max : 255byte)
            case SQL::Blob:        maxDataByteSize = 65536; break;        // ���� ����ŸŸ��, ( Max : 65535byte)
            case SQL::MediumBlob:  maxDataByteSize = 16777216; break;  // ���� ����ŸŸ��, ( Max : 16777215byte)
            case SQL::LongBlob:    maxDataByteSize = 16777216; break;    // ���� ����ŸŸ��, ( Max : 16777215byte)


            default:
                assert(0);
            }

            return maxDataByteSize; 

        }


    };  // namespace VarType
}; // namespace Comm



