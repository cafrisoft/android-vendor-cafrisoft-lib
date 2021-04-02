#include <Comm/Global/BuildOptions.h>
#include <Comm/DataEx/Exchanger.hpp>
#include <Comm/DataEx/Producer.hpp>
#include <Comm/DataEx/Consumer.hpp>

/*
   DataConsumerŬ����(����Ÿ �Һ��� Ŭ����)��  DataProducerŬ����(����Ÿ ������ Ŭ����)��  ¦�� �̷��.
   1:1 ��ȯ�� ����Ѵ�. 
*/

namespace Comm {
namespace DataEx {

    Consumer::Consumer(Producer* pDataProducer) :
        _DataProducerPtr(pDataProducer)
    {
    
        assert(pDataProducer);

        //Data��ȯ�ڿ��� �ڽ��� ����Ѵ�.
        Exchanger::GetInstance()->Register(this);

    }

    Consumer::~Consumer() {

        //Data��ȯ�ڿ��� �ڽ��� ��������� ���� ��û�Ѵ�.
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



