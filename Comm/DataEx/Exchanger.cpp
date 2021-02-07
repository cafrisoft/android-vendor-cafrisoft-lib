#define CLOG_TAG "DataExchanger"
#include <Comm/DataEx/Exchanger.hpp>
#include <Comm/DataEx/Producer.hpp>
#include <Comm/DataEx/Consumer.hpp>
#include <Comm/OAL/Lock.hpp>
#include <Comm/OAL/Log.hpp>

namespace Comm {
namespace DataEx {

    std::shared_ptr<Exchanger> Exchanger::_Instance;

    std::shared_ptr<Exchanger> Exchanger::GetInstance() {
    
        if (Exchanger::_Instance == NULL) {
            Exchanger::_Instance = std::make_shared<Exchanger>();
            assert(Exchanger::_Instance);
        }

        return Exchanger::_Instance;
    }

    Exchanger::Exchanger() {
    
        _CriticalSection = OAL::CriticalSection::CreateObject();
        assert(_CriticalSection);
    }

    void Exchanger::Register(class Producer* pDataProducer) {
    
        OAL::Lock lock(_CriticalSection);

        if (!IsRegister(pDataProducer, false)) {
            _DataProducerVector.push_back(pDataProducer);
        }
    }

    void Exchanger::Unregister(class Producer* pDataProducer) {
    
        OAL::Lock lock(_CriticalSection);

#if 0
        for (std::vector<Producer*>::const_iterator it = _DataProducerVector.cbegin(); it != _DataProducerVector.cend(); ++it) {
            Producer* p = *it;
            if (p == pDataProducer) {
                _DataProducerVector.erase(it);
                //_DataProducerVector.remove(it);
                break;
            }
        }
#endif

        for (std::vector<Producer*>::iterator it = _DataProducerVector.begin(); it != _DataProducerVector.end(); ++it) {
            Producer* p = *it;
            if (p == pDataProducer) {
                _DataProducerVector.erase(it);
                //_DataProducerVector.remove(it);
                break;
            }
        }
    }

    bool Exchanger::IsRegister(class Producer* pDataProducer, bool isLock) {

        bool bRet = false;

        if (isLock) {
            OAL::Lock lock(_CriticalSection);
        }

        for (std::vector<Producer*>::const_iterator it = _DataProducerVector.cbegin(); it != _DataProducerVector.cend(); ++it) {

            Producer* p = *it;
            if (p == pDataProducer) {
                bRet = true;
                break;
            }
        }

        return bRet;
    }


    void Exchanger::Register(class Consumer* pTDatConsumer) {
 
        bool startProducer = false;
        _CriticalSection->Lock();
        if (!IsRegister(pTDatConsumer, false)) {
            _DataConsumerVector.push_back(pTDatConsumer);
            startProducer = true;
        }
        _CriticalSection->Unlock();

        if (startProducer) {
            pTDatConsumer->GetProducer()->StartProduce();
        }
        
    }

    void Exchanger::Unregister(class Consumer* pTDatConsumer) {

        Producer* pDataProducer = pTDatConsumer->GetProducer();
        bool isMatchProducer = false;

        assert(pDataProducer);

        _CriticalSection->Lock();
#if 0
        for (std::vector<Consumer*>::const_iterator it = _DataConsumerVector.cbegin(); it != _DataConsumerVector.cend(); ++it) {
            Consumer* p = *it;
            if (p == pTDatConsumer) {
                _DataConsumerVector.erase(it);
                break;
            }
        }
#else

        for (std::vector<Consumer*>::iterator it = _DataConsumerVector.begin(); it != _DataConsumerVector.end(); ++it) {
            Consumer* p = *it;
            if (p == pTDatConsumer) {
                _DataConsumerVector.erase(it);
                break;
            }
        }

#endif
        
        if (IsRegister(pDataProducer, false)) {
            for (std::vector<Consumer*>::const_iterator it = _DataConsumerVector.cbegin(); it != _DataConsumerVector.cend(); ++it) {
                Consumer* p = *it;
                if (p->IsThisProducer(pDataProducer)) {
                    isMatchProducer = true;
                    break;
                }
            }
        }
        _CriticalSection->Unlock();

        if (isMatchProducer == false) {
            pDataProducer->StopProduce();
        }
    }

    bool Exchanger::IsRegister(class Consumer* pTDatConsumer, bool islock) {

        bool bRet = false;

        if (islock) {
            _CriticalSection->Lock();
        }

        for (std::vector<Consumer*>::const_iterator it = _DataConsumerVector.cbegin(); it != _DataConsumerVector.cend(); ++it) {
            Consumer* p = *it;
            if (p == pTDatConsumer) {
                bRet = true;
                break;
            }
        }

        if (islock) {
            _CriticalSection->Unlock();
        }

        return bRet;
    }


    void Exchanger::ThrowData(Producer* pDataProducer, unsigned char* data, int dataSize) {

        OAL::Lock lock(_CriticalSection);

        for (std::vector<Consumer*>::const_iterator it = _DataConsumerVector.cbegin(); it != _DataConsumerVector.cend(); ++it) {
            Consumer* pDataConsumer = *it;

            //CLOGD("0x%016llX  0x%016llX", pDataProducer, pDataConsumer->GetProducer());

            if (pDataConsumer->IsThisProducer(pDataProducer)) {
                pDataConsumer->CatchDataFromProducer(data, dataSize);
            }
            
        }


    }

}; //namespace DataEx {
}; // namespace Comm {



