#ifndef PATTERNDRAW_HPP__
#define PATTERNDRAW_HPP__

#include "AppDefine.h"



class PatternDraw {
    
    CLASS_SINGLETON_PATTERN_DECLARE(PatternDraw);

private:
    class RawDataSaver : public Comm::OAL::IThreadService {

    private:    
        PatternDraw* _PatternDraw;
        std::shared_ptr<TESys::Data::DataAcqDB> _DB;
        std::shared_ptr<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketDataAcq>>> _PacketQueue;
        std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;
        unsigned char _PacketRawData[4096];

    public:
        RawDataSaver(PatternDraw* notifier);
        
    private:
        virtual void Service();
        virtual void WaitForNextService();
        virtual bool IsServiceRun();

    public:
        bool BroadCast(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack);
    };

    class TCPServer : public Comm::OAL::IThreadService {

    private:
        PatternDraw* _PatternDraw;
        std::shared_ptr<Comm::Socket::TCP::Server> _SrvTcpSock;
        std::shared_ptr<Comm::Utils::SyncQueue<std::shared_ptr<TESys::Net::PacketDataAcq>>> _PacketQueue;
        std::shared_ptr<Comm::OAL::ThreadService> _ThreadService;

    public:
        TCPServer(PatternDraw* notifier);

    private:
        static void CallbackAcceptStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client);
        static void CallbackReceiveStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client, const unsigned char* data, int dataSize);
        static void CallbackCloseStub(void* arg, std::shared_ptr<Comm::Socket::TCP::Client> client);

        void CallbackAccept(std::shared_ptr<Comm::Socket::TCP::Client> client);
        void CallbackReceive(std::shared_ptr<Comm::Socket::TCP::Client> client, const unsigned char* data, int dataSize);
        void CallbackClose(std::shared_ptr<Comm::Socket::TCP::Client> client);

    private:
        virtual void Service();
        virtual void WaitForNextService();
        virtual bool IsServiceRun();

    public:
        bool BroadCast(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack);
    };
       

private:
    //std::shared_ptr<RawDataSaver> _RawDataSaver;
    std::shared_ptr<TCPServer> _TCPServer;

public:
    PatternDraw();

private:
    //std::shared_ptr<RawDataSaver> GetRawDataSaver();
    std::shared_ptr<TCPServer> GetTCPServer();

//public:
    //  bool BoardCastToRawDataSaver(std::shared_ptr<TESys::Net::PacketDataAcq> notifyPack);
};



#endif

