#ifndef COMM_DATAEX_PRODUCER_HPP__
#define COMM_DATAEX_PRODUCER_HPP__

#include <Comm/Base/Object.hpp>

namespace Comm {
namespace DataEx {

    class Exchanger;

    class Producer  : public Base::Object {

        friend class Exchanger;

    protected:
        Producer();
        virtual ~Producer();

    protected:
        void ThrowData(unsigned char* data, int dataSize);

    private:
        virtual bool StartProduce() = 0;
        virtual bool StopProduce() = 0;
        virtual bool IsProduce() = 0;
    };

}; //namespace DataEx {
}; // namespace Comm {
    
#endif //COMM_DATAEX_PRODUCER_HPP__
