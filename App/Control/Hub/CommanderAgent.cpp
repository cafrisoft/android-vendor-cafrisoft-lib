#include "CommanderAgent.hpp"

namespace TESysControlHub {
    
    CLASS_SINGLETON_PATTERN_IMPLEMENT(CommanderAgent);


    CommanderAgent::CommanderAgent() {
    
        _Operator = std::make_shared<Operator>(this);
        assert(_Operator);

        _Tester = std::make_shared<Tester>(this);
        assert(_Tester);
    }
    
    std::shared_ptr<CommanderAgent::Operator> CommanderAgent::GetOperator() {
        return _Operator;
    }

    std::shared_ptr<CommanderAgent::Tester> CommanderAgent::GetTester() {
        return _Tester;
    }

};