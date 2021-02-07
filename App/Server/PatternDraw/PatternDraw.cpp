#include "PatternDraw.hpp"


    
CLASS_SINGLETON_PATTERN_IMPLEMENT(PatternDraw);

PatternDraw::PatternDraw() 
{
    //_RawDataSaver = std::make_shared<RawDataSaver>(this);
    //assert(_RawDataSaver);
    
    _TCPServer = std::make_shared<TCPServer>(this);
    assert(_TCPServer);

  

}
    
//std::shared_ptr<PatternDraw::RawDataSaver> PatternDraw::GetRawDataSaver() {
  //  return _RawDataSaver;
//}
    
    
std::shared_ptr<PatternDraw::TCPServer> PatternDraw::GetTCPServer() {
    return _TCPServer;
}


