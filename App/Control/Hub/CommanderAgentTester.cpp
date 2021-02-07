#include "CommanderAgent.hpp"
#include <TESys/Property/Hub.hpp>
#include <TESys/Property/Tester.hpp>
#include <TESys/Property/Net.hpp>

namespace TESysControlHub {

    /************************************************************************************
    class CommanderAgent::Tester::TesterItem
    ************************************************************************************/
    CommanderAgent::Tester::TesterItem::TesterItem() :
        _BoardID(-1)
        ,_BoardOS(-1)
    {
        _CS = OAL::CriticalSection::CreateObject();
        assert(_CS);

    }

    bool CommanderAgent::Tester::TesterItem::Reset() {
        
        OAL::Lock lock(_CS);

        _BoardID = -1;
        _BoardOS = -1;
        _CliSock.reset();

        return true;
    }

    bool CommanderAgent::Tester::TesterItem::IsRegister() {
        
        OAL::Lock lock(_CS);
        bool bRet = false;

        if (_BoardID > 0) {
            bRet = true;
        }

        return bRet;
    }

    bool CommanderAgent::Tester::TesterItem::Register(int boardID, int boardOS, std::shared_ptr<Socket::TCP::Client> cliSock) {
        
        OAL::Lock lock(_CS);

        _BoardID = boardID;
        _BoardOS = boardOS;
        _CliSock = cliSock;

        return true;
    }

    int CommanderAgent::Tester::TesterItem::GetBoardID() {

        OAL::Lock lock(_CS);

        return _BoardID;
    }

    int CommanderAgent::Tester::TesterItem::GetBoardOS() {

        OAL::Lock lock(_CS);

        return _BoardOS;
    }

    int CommanderAgent::Tester::TesterItem::GetSocketID() {

        OAL::Lock lock(_CS);

        int sockID = -1;
        if (_CliSock) {
            sockID = _CliSock->GetID();
        }
        return sockID;
    }

    /************************************************************************************
    class CommanderAgent::Tester::TesterItemArray
    ************************************************************************************/

    CommanderAgent::Tester::TesterItemArray::TesterItemArray() :
         _TesterItemValidCount(0)
    {

        _Cs = OAL::CriticalSection::CreateObject();
        assert(_Cs);

        _TesterItem = new TesterItem[TESys::Property::Tester::Board::GetAvailMaxCount()];
        assert(_TesterItem);
    }

    CommanderAgent::Tester::TesterItemArray::~TesterItemArray() {
        if (_TesterItem) {
            delete[] _TesterItem;
        }
    }

    int CommanderAgent::Tester::TesterItemArray::GetTesterItemIndex(int boardID) {

        OAL::Lock lock(_Cs);
        int idx = -1;

        for (int i = 0; i < TESys::Property::Tester::Board::GetAvailMaxCount(); i++) {
            if (_TesterItem[i].GetBoardID() == boardID) {
                idx = i;
                break;
            }
        }

        return idx;
    }

    bool CommanderAgent::Tester::TesterItemArray::AddNewTester(int boardID, int boardOS, std::shared_ptr<Socket::TCP::Client> cliSock) {
        
        OAL::Lock lock(_Cs);
        bool bRet = false;

        for (int i = 0; i < TESys::Property::Tester::Board::GetAvailMaxCount(); i++) {
            if (!_TesterItem[i].IsRegister()) {
                bRet = _TesterItem[i].Register(boardID, boardOS, cliSock);
                if (bRet) {

                    CLOGI("Tester Add to Hub : BoardID(%d)", _TesterItem[i].GetBoardID());

                    _TesterItemValidCount++;
                }
                break;
            }
        }

        return bRet;
    }

    bool CommanderAgent::Tester::TesterItemArray::DeleteThisTester(std::shared_ptr<Socket::TCP::Client> cliSock) {

        OAL::Lock lock(_Cs);
        bool bRet = false;

        for (int i = 0; i < TESys::Property::Tester::Board::GetAvailMaxCount(); i++) {
            if (_TesterItem[i].GetSocketID()  == cliSock->GetID()) {

                CLOGI("Tester Delete from Hub : BoardID(%d)", _TesterItem[i].GetBoardID());

                _TesterItem[i].Reset();
                bRet = true;
                _TesterItemValidCount--;
                break;
            }
        }

        return bRet;
    }

    int CommanderAgent::Tester::TesterItemArray::GetTesterItemCount() {
    
        return _TesterItemValidCount;
    }


    /************************************************************************************
    class CommanderAgent::Tester
    ************************************************************************************/

    CommanderAgent::Tester::Tester(CommanderAgent* cmdAgent) :

        _CommanderAgent(cmdAgent)
    {
        
        _CsExtern = OAL::CriticalSection::CreateObject();
        assert(_CsExtern);

        _TesterItemArray = std::make_shared<TesterItemArray>();
        assert(_TesterItemArray);
        
        /*
            Tester TCP 辑滚 家南 积己
        */
        struct Socket::TCP::Server::CreateConfig  createConfigTester = {
            TESys::Property::Net::GetHubCommanderAgentTesterTcpPort(),
            TESys::Net::PacketControl::GetFixedPacketByteSize(),
            TESys::Property::Tester::Board::GetAvailMaxCount(),
            CommanderAgent::Tester::CallbackAcceptStub,
            CommanderAgent::Tester::CallbackReceiveStub,
            CommanderAgent::Tester::CallbackCloseStub,
            this
        };

        _SrvTcpSock = Socket::TCP::Server::CreateObject(createConfigTester);
        assert(_SrvTcpSock);

        _SrvTcpSock->SelectLoop(true);

        CLOGI("[CommanderAgent::Tetser] UDPServerSocket Create ... OK (Port=%d)", _SrvTcpSock->GetPortNum());
    }

    CommanderAgent::Tester::~Tester() {

        int portNum = _SrvTcpSock->GetPortNum();

        _SrvTcpSock.reset();
        CLOGI("[CommanderAgent::Tetser] TCPServerSocket Destroy (Port=%d)", portNum);
    }

    
    
};
