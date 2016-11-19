#ifndef _LINGUISTIC_SET
#define _LINGUISTIC_SET
#include <fuzzy/fuzzyDefine.h>
#include <fuzzy/Linguistic.h>
#include <string>
#include <vector>
#include <iostream>

namespace fuzzy {

   class LinguisticSet {
      public:
         LinguisticSet() {};
         LinguisticSet(std::vector<Linguistic> newLingVector): linguisticVector(newLingVector) {};
         virtual ~LinguisticSet() {};
         std::vector<Linguistic> linguisticVector;
         Linguistic* getLinguisticByName(const std::string name);
         void listLinguisticSet();
   };
}


#endif
