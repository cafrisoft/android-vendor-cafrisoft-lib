#include <Comm/Database/RDBMS/Product.hpp>
#include <Comm/Database/RDBMS/MySQL.hpp>

namespace Comm {
    namespace Database {
        namespace RDBMS {

            std::shared_ptr<Product> Product::CreateObject(Type product) {

                std::shared_ptr<Product> obj;

                switch (product) {

                case Type::MySQL:
                    obj = std::make_shared<MySQL>();
                    break;
                }
                assert(obj);

                return obj;
            }

            Product::Product() {

            }

        }; //namespace RDBMS {
    }; //namespace OAL
}; //namespace Comm
