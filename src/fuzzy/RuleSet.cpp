#include <fuzzy/RuleSet.h>

namespace fuzzy {

typedef std::vector<Rule>::iterator RuleIterator_t;

  void  RuleSet::listRuleSet()
  {
    RuleIterator_t it;
    
    for (it = ruleVector.begin(); it != ruleVector.end(); it++)
    {
      it->listRule();
      std::cout << std::endl; 
    }
  }
}
