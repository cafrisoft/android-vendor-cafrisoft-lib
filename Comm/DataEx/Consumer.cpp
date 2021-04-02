#include <Comm/Global/BuildOptions.h>
#include <Comm/DataEx/Exchanger.hpp>
#include <Comm/DataEx/Producer.hpp>
#include <Comm/DataEx/Consumer.hpp>

/*
   DataConsumer클레스(데이타 소비자 클레스)는  DataProducer클레스(데이타 생산자 클레스)와  짝을 이룬다.
   1:1 교환만 허락한다. 
*/

namespace Comm {
namespace DataEx {

    Consumer::Consumer(Producer* pDataProducer) :
        _DataProducerPtr(pDataProducer)
    {
    
        assert(pDataProducer);

        //Data교환자에서 자신을 등록한다.
        Exchanger::GetInstance()->Register(this);

    }

    Consumer::~Consumer() {

        //Data교환자에서 자신을 등록해제할 것을 요청한다.
        Exchanger::GetInstance()->Unregister(this);
    }

    bool Consumer::IsThisProducer(Producer* pDataProducer) {

        bool bRet = false;
        
        if (_DataProducerPtr == pDataProducer) {
            bRet = true;
        }
        
        return bRet;
    }
  
    Producer* Consumer::GetProducer() {
        return _DataProducerPtr;
    }

}; //namespace DataEx {
}; // namespace Comm {



