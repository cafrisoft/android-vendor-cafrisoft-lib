#include "RemotePython.hpp"
#include <TED/Api.h>

using namespace TESys::Net;

namespace RemotePython {

    static std::vector<std::string> s_funcNameVector;

    std::string Debug::FuncNameStack() {
    
        std::string sfunName;
        int i = 0;
        for (std::vector<std::string>::const_iterator it = s_funcNameVector.cbegin(); it != s_funcNameVector.cend(); ++it) {
            std::string s = *it;
            
            if (i > 0) {
                sfunName.append("::");
            }
            sfunName.append(s);

            i++;
        }

        return sfunName;
    }

    std::string Debug::FuncNameStack(char delim) {

        char szDelim[2];
        std::string sfunName;
        int i = 0;

        szDelim[0] = delim;
        szDelim[1] = '\0';

        for (std::vector<std::string>::const_iterator it = s_funcNameVector.cbegin(); it != s_funcNameVector.cend(); ++it) {
            std::string s = *it;

            if (i > 0) {
                sfunName.append(szDelim);
            }
            sfunName.append(s);

            i++;
        }

        return sfunName;
    }

#if (CommOS == CommOS_WIN)
    const char* ExecelTxtFileName = "d:\\work\\RemotePythonExecel.txt";
#elif (CommOS == CommOS_ANDROID)
    const char* ExecelTxtFileName = "/tmp/RemotePythonExecel.txt";
#endif

    bool Debug::_ExecelTxtEnable = false;

    void Debug::ExecelTxtInit(bool isEnable) {
    
        Debug::_ExecelTxtEnable = isEnable;
        if (Debug::_ExecelTxtEnable) {
            FILE* fp = fopen(ExecelTxtFileName, "w");
            assert(fp);
            fclose(fp);
        }
    }

    void Debug::ExecelTxtPrint(const char* lpszFormat, ...) {

        if (Debug::_ExecelTxtEnable) {

            FILE* fp = fopen(ExecelTxtFileName, "a");
            assert(fp);

            va_list args;
            char* szBuffer = new char[1024 * 16];

            va_start(args, lpszFormat);
#if (CommOS == CommOS_WIN)
            _vstprintf(szBuffer, lpszFormat, args);
#else
            vsprintf(szBuffer, lpszFormat, args);
#endif
            va_end(args);

            fprintf(fp, "%s\t%s\n", szBuffer, Debug::FuncNameStack('\t').c_str());

            delete[] szBuffer;
            fclose(fp);
        }
    }

    bool Debug::FuncEnter(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

        int funcNameBufByteSize;
        unsigned char* funcName;
        bool bRet = false;

        funcNameBufByteSize = rcvPack->GetInt(0);
        funcName = new unsigned char[funcNameBufByteSize];
        assert(funcName);

        rcvPack->GetData(funcName, funcNameBufByteSize);

        bRet = true; // TedMipiReadReg(addr, byteOffset, readCount, regValue, readCount);
        //PRINTF("TxtCmd : %s ", txtCmd);
        //PRINTF("+++++++++++++++++++++++++ Function Enter :  %s ++++++++++++++++++++++++++++++", funcName);

        std::string s = (char*)funcName;
        s_funcNameVector.push_back(s);


        //Send Response
        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, funcNameBufByteSize);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        delete[] funcName;

        return true;
    }

    bool Debug::FuncLeave(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

        int funcNameBufByteSize;
        unsigned char* funcName;
        bool bRet = false;

        funcNameBufByteSize = rcvPack->GetInt(0);
        funcName = new unsigned char[funcNameBufByteSize];
        assert(funcName);

        rcvPack->GetData(funcName, funcNameBufByteSize);

        bRet = true; // TedMipiReadReg(addr, byteOffset, readCount, regValue, readCount);
        //PRINTF("TxtCmd : %s ", txtCmd);
        //PRINTF("[Debug::FuncLeave] %s", funcName);
        //PRINTF("------------------------- Function Leave :  %s ------------------------------", funcName);

        std::string s = (char*)funcName;
        std::string s1 = s_funcNameVector.back();
        //Top이름이 다르면 ASSERT
        if (s.compare(s1)!=0) {
            assert(1);
        }
        s_funcNameVector.pop_back();

        //Send Response
        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, funcNameBufByteSize);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        delete[] funcName;

        return true;
    }

    bool Debug::Message(std::shared_ptr<Socket::TCP::Client> client, std::shared_ptr<TESys::Net::PacketPython> rcvPack) {

        int msgBufByteSize;
        unsigned char* msg;
        bool bRet = false;

        msgBufByteSize = rcvPack->GetInt(0);
        msg = new unsigned char[msgBufByteSize];
        assert(msg);

        rcvPack->GetData(msg, msgBufByteSize);

        bRet = true; // TedMipiReadReg(addr, byteOffset, readCount, regValue, readCount);
        //PRINTF("TxtCmd : %s ", txtCmd);
        //PRINTF("[Debug::FuncLeave] %s", funcName);
        //PRINTF("------------------------- Function Leave :  %s ------------------------------", funcName);
        CLOGI("MESSAGE=%s [%s] ", msg, Debug::FuncNameStack().c_str());
        Debug::ExecelTxtPrint("MESSAGE=\"%s\"", msg);

        //Send Response
        std::shared_ptr<PacketPython> sendPack = std::make_shared<PacketPython>();
        sendPack->SetCommand(rcvPack->GetCommand());
        sendPack->SetInt(0, msgBufByteSize);
        sendPack->SetResult(bRet);
        sendPack->GenCRC();

        client->Send(sendPack);

        delete[] msg;

        return true;
    }

};