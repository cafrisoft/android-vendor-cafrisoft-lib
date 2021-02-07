#include <Comm/DataEx/Exchanger.hpp>
#include <Comm/DataEx/Producer.hpp>

namespace Comm {
namespace DataEx {


    Producer::Producer() {
    
        Exchanger::GetInstance()->Register(this);
    }

    Producer::~Producer() {
        Exchanger::GetInstance()->Unregister(this);
    }

    void Producer::ThrowData(unsigned char* data, int dataSize) {

        Exchanger::GetInstance()->ThrowData(this, data, dataSize);
    }

}; //namespace DataEx {
}; // namespace Comm {



