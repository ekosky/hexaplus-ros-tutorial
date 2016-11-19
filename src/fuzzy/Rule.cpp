#include <fuzzy/Rule.h>


namespace fuzzy {

 typedef std::vector<fuzzy::RuleElement>::iterator ruleElementIterator_t;

 void Rule::listRule() {
    ruleElementIterator_t it;
 
    std::cout << name << "("<< strength << ")" << " IF ";
    for (it = if_RuleElementVector.begin(); it != if_RuleElementVector.end(); it++)
    {
      std::string isOperator     = it->isOperator?"is":"is not";
      std::string logicConnector = it->logicConnector==OR?"OR":
                                   it->logicConnector==AND?"AND":"" ;

      std::cout << it->linguistic->name 
                << "(" << it->linguistic->value << ")"
                << " " << isOperator 
                << " " << it->membershipFunction->name
                << "(" << it->membershipFunction->degree << ")" 
                << " " << logicConnector;
    }
    
    std::cout << " THEN ";

    for (it = then_RuleElementVector.begin(); it != then_RuleElementVector.end(); it++)
    {
      std::string isOperator     = it->isOperator?"is":"is not";
      std::string logicConnector = it->logicConnector==OR?"OR":
                                   it->logicConnector==AND?"AND":"" ;
      std::cout << it->linguistic->name 
                << "(" << it->linguistic->value << ")"
                << " " << isOperator 
                << " " << it->membershipFunction->name
                << "(" << it->membershipFunction->degree << ")" 
                << " " << logicConnector
                << std::endl;
    }
  }
}
