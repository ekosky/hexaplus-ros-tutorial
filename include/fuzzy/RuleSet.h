#ifndef _RULE_SET_
#define _RULE_SET_
#include <fuzzy/fuzzyDefine.h>
#include <fuzzy/Rule.h>

namespace fuzzy {

   class RuleSet {
      public:
         RuleSet() {};
         RuleSet(std::vector<Rule> NewRuleVector): ruleVector(NewRuleVector) {};
         virtual ~RuleSet() {};

         std::vector<Rule> ruleVector;
         void listRuleSet();
   };
}

#endif
