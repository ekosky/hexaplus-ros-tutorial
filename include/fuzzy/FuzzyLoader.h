#ifndef _FUZZYLOADER_
#define _FUZZYLOADER_
#include <fuzzy/fuzzyDefine.h>
#include <fuzzy/FuzzySet.h>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <iterator>

namespace fuzzy {

   class FuzzyLoader {
      public:
         void loadFromFile(FuzzySet* fuzzySet
                          ,const char* inputLinguisticSetFileName 
                          ,const char* outputLinguisticSetFileName 
                          ,const char* ruleSetFileName);

         void loadLing(FILE *LFile, LinguisticSet* lingSet); 

         void loadRule(FILE *rFile
              ,LinguisticSet* iLSet
              ,LinguisticSet* oLSet
              ,RuleSet* rSet);

   };
}


#endif
