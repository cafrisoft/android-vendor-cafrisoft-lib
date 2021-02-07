#include "Cmd.hpp"
#include <TESys/Property/Hub.hpp>
#include <TESys/Property/Net.hpp>

namespace AppControlShell {
    namespace Cmd {

        const char* Hub::CMD_TESTER = "hub";
        const char* Hub::CMD_DISPLAY_INFO = "info";
      
         bool Hub::DisplayInfo(int argc, const char** argv) {
        
             
             PRINTF("Hub IP Addr : [%s] \n", TESys::Property::Net::GetHubMachIPAddr().c_str());
             PRINTF("\n");

             PRINTF("%d  Hub CommanderAgent Operator Tcp Port\n", TESys::Property::Net::GetHubCommanderAgentOperatorTcpPort());
             PRINTF("%d  Hub CommanderAgent Tester Tcp Port\n", TESys::Property::Net::GetHubCommanderAgentTesterTcpPort());
             PRINTF("%d  Hub Notifier Operator Tcp Port\n", TESys::Property::Net::GetHubNotifierOperatorTcpPort());
             PRINTF("%d  Hub Notifier Operator Udp Port\n", TESys::Property::Net::GetHubNotifierTesterUdpPort());
             PRINTF("\n");
         
             return true;
         }

         bool Hub::ChangeIPAddr(int argc, const char** argv) {

#if 0
             const char* inputIPAddr; 

             if (argc != 1) {
                 PRINTF("ERROR :  Input IPAddr\n");
                 return false;
             }

             inputIPAddr = argv[0];

             PRINTF("Current Hub IPAddr : [%s] \n", TESys::Property::Net::GetHubMachIPAddr().c_str());
             PRINTF("New Input IPAddr : [%s] \n", inputIPAddr);
             TESys::Property::Hub::SetPropIpAddr(inputIPAddr);
             PRINTF("New IPAddr : [%s] \n", TESys::Property::Hub::GetIpAddr().c_str());

             if (TESys::Property::Hub::GetIpAddr().compare(inputIPAddr) == 0) {
             
                 PRINTF("Hub IP Change OK \n");
             }
             else {
                 PRINTF("Hub IP Change FAIL!! \n");
             }

#else
             PRINTF("Not Support Now!! \n");

#endif
                      
             return true;
         }
         
         bool Hub::ClearIPAddr(int argc, const char** argv) {
         
#if 0
             PRINTF("Current Hub IPAddr : [%s] \n", TESys::Property::Hub::GetIpAddr().c_str());
             TESys::Property::Hub::SetPropIpAddr("");
             PRINTF("New IPAddr : [%s] \n", TESys::Property::Hub::GetIpAddr().c_str());
#else
             PRINTF("Not Support Now!! \n");

#endif

             return true;
         }

    };
};


