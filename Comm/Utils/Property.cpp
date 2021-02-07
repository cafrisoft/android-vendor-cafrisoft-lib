#include <Comm/Utils/Property.hpp>

namespace Comm {
    namespace Utils {


        /************************************************************************************************
        class Property
        ************************************************************************************************/

        std::shared_ptr<Property> Property::CreateObject(ValueType valueType, const char* name, const char* value) {
        
            std::shared_ptr<Property> prop;

            switch (valueType) {
                case ValueType::String:  prop = std::make_shared<PropertyString>(name, value); break;
            }
            assert(prop);

            return prop;
        }

        Property::Property(const char* name, ValueType valueType) :
            _Name(name)
            ,_ValueType(valueType)
        {

        }

        bool Property::IsThisName(const char* name) {

            return _Name.compare(name) == 0 ? true : false;
        }

        std::string Property::GetName() {
            return _Name;
        }

        /************************************************************************************************
        class PropertyString
        ************************************************************************************************/
        PropertyString::PropertyString(const char* name, const char* value) :
            Property(name, ValueType::String)
            ,_Value(value?value:"")
        {

        }


        bool PropertyString::SetValueString(const char* value) {
            _Value = value;
            return true;
        }

        bool PropertyString::SetValueString(std::string strValue) {
            _Value = strValue;
            return true;
        }
                
        std::string PropertyString::GetValueString() {
            return _Value;
        }

        long long PropertyString::GetValueLongLong() {
            return atoll(_Value.c_str());
        }
    };
};