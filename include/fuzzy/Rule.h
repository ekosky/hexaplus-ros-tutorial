#ifndef _RULE_ELEMENT
#define _RULE_ELEMENT
#include <fuzzy/fuzzyDefine.h>
#include <fuzzy/RuleElement.h>

namespace fuzzy {

   class Rule{
      public:
         Rule() {};
         Rule(std::string newName): name(newName) {strength = 0;}; 
         Rule(std::string newName
             ,std::vector<RuleElement> newIf_RureElemVector
             ,std::vector<RuleElement> newThen_RureElemVector)
             :name(newName)
             ,if_RuleElementVector(newIf_RureElemVector)
             ,then_RuleElementVector(then_RuleElementVector) {strength = 0;};
         virtual ~Rule() {};

         std::string name;
         float strength;
         std::vector<RuleElement> if_RuleElementVector;
         std::vector<RuleElement> then_RuleElementVector;
         void listRule();
   };
}

#endif
