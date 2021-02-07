#ifndef COMM_PROPERTY_PATH_HPP__
#define COMM_PROPERTY_PATH_HPP__

#include <Comm/Global/BuildOptions.h>

namespace Comm {
    namespace Property {

        namespace Path {

            std::string GetTmpRoot();  //�ֹ߼� ����Ÿ ����� 

            char GetFilePathDelimChar();
            std::string GetFilePathDelimString();
        
        };


    }; //namespace Net {
}; // namespace Comm {

#endif //COMM_DATAEX_PRODUCER_HPP__
