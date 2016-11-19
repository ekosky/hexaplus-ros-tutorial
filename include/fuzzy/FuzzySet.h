#ifndef _FUZZY_SET_
#define _FUZZY_SET_
#include <fuzzy/fuzzyDefine.h>
#include <fuzzy/RuleSet.h>
#include <fuzzy/LinguisticSet.h>

namespace fuzzy {

   class FuzzySet {
      public:
         FuzzySet();
         FuzzySet(const std::string newName);
         virtual ~FuzzySet() {};

         std::string name;
         RuleSet* ruleSet;
         LinguisticSet* inputLinguisticSet;
         LinguisticSet* outputLinguisticSet;

         void fuzzyfication();
         void defuzzification();
         void ruleInference();
         // Just for fun, call fuzzyfication, defuzzification and ruleInference
         void fuzzifying(); 
   };
}

#endif
