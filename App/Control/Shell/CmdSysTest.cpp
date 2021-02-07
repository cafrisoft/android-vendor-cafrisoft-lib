#include "Cmd.hpp"
#include <TESys/Property/Tester.hpp>
#include <TESys/Net/PacketControl.hpp>
#include <Comm/Utils/Queue.hpp>
#include <TESys/Property/Tester.hpp>
#include <TED/Api.h>

namespace AppControlShell {
    namespace Cmd {

        const char* SysTest::CMD_TESTER = "sys";
        const char* SysTest::CMD_TEST_1 = "test1";
      
        static void StdSharedPtr_Printf() {
        
            std::shared_ptr<int> obj = std::make_shared<int>();
            long long v = 0xABCD;


            printf("0x%016llX \n", (long long)obj.get());
            printf("0x%016llX \n", v);

        }

        

        static void StdArrayTest() {

            class ClientWin {
            private:
                int dummy;
            };

            //std::array<ClientWin, 1024> a1;// _ClientArray;
            //std::array<std::shared_ptr<ClientWin>, 1024> a2;// _ClientArray;
        }

        static void StdQueue_INT_Test() {
        
            std::queue<int> q;
            std::shared_ptr<TESys::Net::PacketControl> notifyPack = std::make_shared<TESys::Net::PacketControl>();

            PRINTF("Queue Sz : %d \n", q.size());
            // push
            q.push(1);
            PRINTF("Queue Sz : %d \n", q.size());
            q.push(2);
            PRINTF("Queue Sz : %d \n", q.size());
            q.push(3);
            PRINTF("Queue Sz : %d \n", q.size());
            q.push(4);
            PRINTF("Queue Sz : %d \n", q.size());
            q.push(5);
            PRINTF("Queue Sz : %d \n", q.size());
            q.push(6);
            PRINTF("Queue Sz : %d \n", q.size());


            // pop
            q.pop();
            PRINTF("Queue Sz : %d \n", q.size());
            q.pop();
            PRINTF("Queue Sz : %d \n", q.size());
            q.pop();
            PRINTF("Queue Sz : %d \n", q.size());
        }

        static void StdQueue_Test() {

            std::queue<std::shared_ptr<TESys::Net::PacketControl>> q;
            std::shared_ptr<TESys::Net::PacketControl> notifyPack;
            
            PRINTF("Queue Sz : %d \n", q.size());

            // push
            notifyPack = std::make_shared<TESys::Net::PacketControl>();
            q.push(notifyPack);
            PRINTF("Queue Sz : %d \n", q.size());

            notifyPack = std::make_shared<TESys::Net::PacketControl>();
            q.push(notifyPack);
            PRINTF("Queue Sz : %d \n", q.size());

            notifyPack = std::make_shared<TESys::Net::PacketControl>();
            q.push(notifyPack);
            PRINTF("Queue Sz : %d \n", q.size());

            notifyPack = std::make_shared<TESys::Net::PacketControl>();
            q.push(notifyPack);
            PRINTF("Queue Sz : %d \n", q.size());

            notifyPack = std::make_shared<TESys::Net::PacketControl>();
            q.push(notifyPack);
            PRINTF("Queue Sz : %d \n", q.size());

            notifyPack = std::make_shared<TESys::Net::PacketControl>();
            q.push(notifyPack);
            PRINTF("Queue Sz : %d \n", q.size());

            // pop
            q.pop();
            PRINTF("Queue Sz : %d \n", q.size());
            q.pop();
            PRINTF("Queue Sz : %d \n", q.size());
            q.pop();
            PRINTF("Queue Sz : %d \n", q.size());
        }




        template<class Type> class TQueue
        {
        public:
            std::queue<Type> _Queue;
            std::shared_ptr<OAL::CriticalSection> _CsIF;

        public:
            TQueue() {
                _CsIF = OAL::CriticalSection::CreateObject();
                assert(_CsIF);
            }

            virtual ~TQueue() {

            }

            bool IsEmpty() {
                OAL::Lock lock(_CsIF);
                return _Queue.empty();
            }

            int Count() {
                OAL::Lock lock(_CsIF);
                return (int)_Queue.size();
            }

            virtual bool Push(Type t) {
                OAL::Lock lock(_CsIF);
                _Queue.push(t);
                return true;
            }

            virtual Type Pop() {
                OAL::Lock lock(_CsIF);
                Type t = _Queue.front();
                _Queue.pop();
                return t;
            }

        };



        static void MyQueue_INT_Test() {

            //Comm::Utils::TQueue<int> q;
            TQueue<int> q;
            
            PRINTF("Queue Sz : %d \n", q.Count());
            // push
            q.Push(1);
            PRINTF("Queue Sz : %d \n", q.Count());
            q.Push(2);
            PRINTF("Queue Sz : %d \n", q.Count());
            q.Push(3);
            PRINTF("Queue Sz : %d \n", q.Count());
            q.Push(4);
            PRINTF("Queue Sz : %d \n", q.Count());
            q.Push(5);
            PRINTF("Queue Sz : %d \n", q.Count());
            q.Push(6);
            PRINTF("Queue Sz : %d \n", q.Count());


            // pop
            q.Pop();
            PRINTF("Queue Sz : %d \n", q.Count());
            q.Pop();
            PRINTF("Queue Sz : %d \n", q.Count());
            q.Pop();
            PRINTF("Queue Sz : %d \n", q.Count());
        }

        static void BoardErrFlag_Test() {
        
            long long curErrFlag = 0;
            //long long errBit;

            for (long long errBit = 0; errBit < 64; errBit++) {
                curErrFlag = TESys::Property::Tester::ErrorClass::GenSysFlag(curErrFlag, (TESys::Property::Tester::ErrorClass::SysFlagBit)errBit);
                PRINTF("Bit=%lld curErrFlag=0x%016llX \n", errBit, curErrFlag);
            }
        }

        static void UTCTimeTest() {
        
            long long curT = TedSysGetCurUtcTime();
            long long wT = TedSysGetUtcTimeKST(2020, 11, 10, 12, 0, 0);
            printf("curT : %lld \n", curT);
            printf("wT : %lld \n", wT);
        }

        bool SysTest::Test1(int argc, const char** argv) {

            //StdSharedPtr_Printf();
            //StdQueue_Test();
            //MyQueue_INT_Test();
            //BoardErrFlag_Test();
            UTCTimeTest();
        
            return true;
        }
        
        bool SysTest::ServerStorageCal(int argc, const char** argv) {

            const long long serverOpt1kblocks = 379598600;  //  /opt 공간크기 
            const long long serverOpt1kblocksAvail = 345952940; // DB없을떄 opt Avail크기 

            const long long job0001_1try_rawdata_bytesize = 42393600;  // JOB_0000.py를 실행했을때  DBRawData크기   Tester는 51~500번까지 실행중

            long long serverOptStorageByteSize = serverOpt1kblocksAvail * 1024;
            long long maxTCRunCount = serverOptStorageByteSize / job0001_1try_rawdata_bytesize;
            
            long long agingDurSecond = 3600 * 24 * 3; //사흘간 

            PRINTF("Server Avail 공간 크기 :  %lld Mbyte \n", serverOptStorageByteSize / (1024 * 1024));
            
            
            agingDurSecond = 3600 * 24 * 2; //2일
            PRINTF("2일 JOB RUN최대 개수 :  %lld 번 \n", maxTCRunCount); 
            PRINTF("2일 TRY Dur 간격 :  %lld sec \n", agingDurSecond/maxTCRunCount);
            PRINTF("\n");

            agingDurSecond = 3600 * 24 * 3; //3일
            PRINTF("3일 JOB RUN최대 개수 :  %lld 번 \n", maxTCRunCount);
            PRINTF("3일 TRY Dur 간격 :  %lld sec \n", agingDurSecond / maxTCRunCount);

            return true;
        }
    };
};


