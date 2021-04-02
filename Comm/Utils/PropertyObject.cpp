#include <Comm/Global/BuildOptions.h>
#include <Comm/Utils/Property.hpp>

namespace Comm {
    namespace Utils {
        namespace Property {

            /************************************************************************************************
            class Property
            ************************************************************************************************/

            std::shared_ptr<Object> Object::CreateObject(ValueType valueType, const char* name, const char* value) {

                std::shared_ptr<Object> prop;

                switch (valueType) {
                case ValueType::String:  prop = std::make_shared<ObjectString>(name, value); break;
                }
                assert(prop);

                return prop;
            }

            Object::Object(const char* name, ValueType valueType) :
                _Name(name)
                , _ValueType(valueType)
            {

            }

            bool Object::IsThisName(const char* name) {

                return _Name.compare(name) == 0 ? true : false;
            }

            std::string Object::GetName() {
                return _Name;
            }

            /************************************************************************************************
            class PropertyString
            ************************************************************************************************/
            ObjectString::ObjectString(const char* name, const char* value) :
                Object(name, ValueType::String)
                , _Value(value ? value : "")
            {

            }


            bool ObjectString::SetValueString(const char* value) {
                _Value = value;
                return true;
            }

            bool ObjectString::SetValueString(std::string strValue) {
                _Value = strValue;
                return true;
            }

            std::string ObjectString::GetValueString() {
                return _Value;
            }

            long long ObjectString::GetValueLongLong() {
                return atoll(_Value.c_str());
            }
        };
    };
};