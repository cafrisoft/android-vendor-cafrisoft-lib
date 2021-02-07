#include "Notifier.hpp"

namespace TESysControlHub {
    
    CLASS_SINGLETON_PATTERN_IMPLEMENT(Notifier);

    Notifier::Notifier() 
    {
        _Operator = std::make_shared<Operator>(this);
        assert(_Operator);
    
        _Tester = std::make_shared<Tester>(this);
        assert(_Tester);

    }
    
    std::shared_ptr<Notifier::Operator> Notifier::GetOperator() {
        return _Operator;
    }
    
    std::shared_ptr<Notifier::Tester> Notifier::GetTester() {
        return _Tester;
    }
    
    
};
