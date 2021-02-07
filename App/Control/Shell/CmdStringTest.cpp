#include "Cmd.hpp"
#include <TESys/Property/Tester.hpp>
#include <TESys/Net/PacketControl.hpp>
#include <Comm/Utils/Queue.hpp>
#include <Comm/Utils/StringTool.hpp>

namespace AppControlShell {
    namespace Cmd {

#if 0
        template<typename ... Args>
        std::string my_string_format(const std::string& format, Args ... args)
        {
            size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
            //if (size <= 0) { throw std::runtime_error("Error during formatting."); }
            std::unique_ptr<char[]> buf(new char[size]);
            snprintf(buf.get(), size, format.c_str(), args ...);
            return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
        }
#endif

        bool StringTest::StringFormatTest(int argc, const char** argv) {
        
            //unsigned int t1, t2;
            
            printf("start \n");

            for (int i = 0; i < 100; i++) {
             
                char* tmpBuf = new char[1024 * 1024];
                assert(tmpBuf);


                std::string str1 = Comm::Utils::StringFormat("%s:%d", "my_string_format", i);
                sprintf(tmpBuf, "%s:%d", "sprintf", i);
                printf("%s %s\n", str1.c_str(), tmpBuf);

                delete[] tmpBuf;
            }

            

            return true;
        }
        
    };
};


