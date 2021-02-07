#ifndef APP_TESYSOPERATOR_APPDEFINE_HPP__
#define APP_TESYSOPERATOR_APPDEFINE_HPP__

#include <Comm/Socket/TCP/TCPServer.hpp>
#include <Comm/Shell/Main.hpp>

#include <TESys/Global/BuildOptions.h>
#include <TESys/Net/PacketControl.hpp>
#include <TESys/Control/Operator.hpp>
#include <TESys/Data/Status.hpp>
#include <TESys/Data/DataAcqDB.hpp>

#define CLOG_TAG "TESysOperator"

using namespace Comm;

extern int GetExtraBoardCount();
extern std::vector<int> GetExtraBoardID();

#endif
