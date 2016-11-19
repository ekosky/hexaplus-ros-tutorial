#ifndef _RULE_ELEMENT_
#define _RULE_ELEMENT_
#include <fuzzy/fuzzyDefine.h>
#include <fuzzy/Linguistic.h>
#include <fuzzy/MembershipFunction.h>

namespace fuzzy {

   class RuleElement{
      public:
         RuleElement() {};
         virtual ~RuleElement() {};
         bool isOperator;
         LogicConnector logicConnector;
         Linguistic* linguistic;
         MembershipFunction* membershipFunction;
   };
}

#endif
