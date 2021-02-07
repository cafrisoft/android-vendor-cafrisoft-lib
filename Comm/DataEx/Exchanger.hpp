#ifndef COMM_DATAEX_EXCHANGER_HPP__
#define COMM_DATAEX_EXCHANGER_HPP__

#include <Comm/Base/Object.hpp>
#include <Comm/OAL/CriticalSection.hpp>

namespace Comm {
namespace DataEx {

    class Producer;
    class Consumer;

    class Exchanger : public Base::Object {

        friend class Producer;
        friend class Consumer;

    private:
        static std::shared_ptr<Exchanger> _Instance;
        static std::shared_ptr<Exchanger> GetInstance();


    private:
        std::shared_ptr<OAL::CriticalSection> _CriticalSection;
        std::vector<Producer*> _DataProducerVector;
        std::vector<Consumer*> _DataConsumerVector;

    public:
        Exchanger();

    private:
        void Register(class Producer* pDataProducer);
        void Unregister(class Producer* pDataProducer);
        bool IsRegister(class Producer* pDataProducer, bool islock = true);

        void Register(class Consumer* pTDatConsumer);
        void Unregister(class Consumer* pTDatConsumer);
        bool IsRegister(class Consumer* pTDatConsumer, bool islock=true);
      
        void ThrowData(Producer* pDataProducer, unsigned char* data, int dataSize);
    };

}; //namespace DataEx {
}; // namespace Comm {

#endif //COMM_DATAEX_EXCHANGER_HPP__
