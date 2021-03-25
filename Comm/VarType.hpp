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

            //������ ����Ÿ Ÿ��
            Char = 0,    //fixed string data Type (�ִ� 255byte)  ������ ���̺��� ª�� ����Ÿ �Է½� ������ ���� ����ó�� 
            VarChar,     //��������Ÿ�� (�ִ� 65535byte) ������ ���̺��� ª�� ����Ÿ �Է½� ������ ������ ä���� �ʴ´�.  
            TinyText,    //string data type (max 255b byte) 
            Text,        //string data type (max 65535 byte) 
            MediumText,  //string data type (max 16777215 byte) 
            LongText,    //string data type (max 4294967295 byte) 

            //������ ����Ÿ Ÿ��
            TinyUint,     // 1byte 0~255
            TinyInt,     // 1byte  -128 ~ 127
            SmallUint,   // 2byte  0~65535
            SmallInt,    // 2byte  -32768 ~ 327677
            MediumInt,   // 3byte  -8388608 ~ +8388607 �Ǵ� 0 ~ 16777215
            Uint,        // 4byte   0 ~ 16777215     
            Int,         // 4byte  -8388608 ~ +8388607
            BigUint,     // 8byte
            BigInt,      // 8byte
            Float,       // �ε� �Ҽ��� ����Ÿ Ÿ�� (4byte)
            Decimal,     // ���� �Ҽ��� ����Ÿ Ÿ�� (���� + 1byte)  �Ҽ��� ��� ���� 
            Double,      // �ε� �Ҽ��� ����Ÿ Ÿ�� (8byte)

            //��¥�� ����Ÿ Ÿ��
            Date,       // ��¥ (�⵵, ��, ��) ������ �Ⱓ ǥ�� ����Ÿ Ÿ�� (3byte)
            Time,       // �ð� (��, ��, ��) ������ �Ⱓ ǥ�� ����Ÿ Ÿ�� (3byte)
            DateTime,   // ��¥�� �ð� ������ �Ⱓ ǥ�� ����Ÿ Ÿ�� (8byte)
            TimeStamp,  // ��¥�� �ð� ������ �Ⱓ ǥ�� ����Ÿ Ÿ�� (4yte)  �ý��� ����� �ڵ����� �� ��¥�� �ð��� �����
            Year,        // �⵵ ǥ�� 

            //Binary Data Type
            Binary,     // Char������ ���� ����Ÿ Ÿ�� Max 255Byte
            VarBinary,  // Var Char������ ���� ����Ÿ Ÿ�� (�ִ� 65535byte)
            TinyBlob,   // ���� ����ŸŸ��, ( Max : 255byte)
            Blob,       // ���� ����ŸŸ��, ( Max : 65535byte)
            MediumBlob, // ���� ����ŸŸ��, ( Max : 16777215byte)
            LongBlob,   // ���� ����ŸŸ��, ( Max : 16777215byte)

        };

        CPP StringToCppVarType(std::string strVarType);
        std::string VarTypeName(CPP vt);

        SQL StringToSqlVarType(std::string strDataType);
        std::string VarTypeName(SQL vt);

        long long VarTypeMaxByteSize(SQL vt);

    };  // namespace VarType
}; // namespace Comm

#endif

