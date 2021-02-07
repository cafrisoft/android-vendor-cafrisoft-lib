#ifndef COMM_DATAEX_CONSUMER_HPP__
#define COMM_DATAEX_CONSUMER_HPP__

#include <Comm/Base/Object.hpp>

namespace Comm {
namespace DataEx {

    class Exchanger;
    class Producer;
    
    class Consumer : public Base::Object  {

        friend class Exchanger;

    private:
        Producer* _DataProducerPtr;

    protected:
        Consumer(Producer* pDataProducer);
        virtual ~Consumer();

    private:
        virtual bool CatchDataFromProducer(unsigned char* data, int dataSize) = 0;

    private:
        bool IsThisProducer(Producer* pDataProducer);
        Producer* GetProducer();
    };

}; //namespace DataEx {
}; // namespace Comm {

#endif //COMM_DATAEX_PRODUCER_HPP__
