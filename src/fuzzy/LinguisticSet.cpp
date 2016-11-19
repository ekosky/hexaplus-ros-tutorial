#include <fuzzy/LinguisticSet.h>

namespace fuzzy {

typedef std::vector<Linguistic>::iterator LinguisticIterator_t;

  void  LinguisticSet::listLinguisticSet()
  {
    LinguisticIterator_t it;
    for (it = linguisticVector.begin(); it != linguisticVector.end(); it++)
    {
      it->listLinguistic();
      std::cout << '\n'; 
    }
  }

  Linguistic* LinguisticSet::getLinguisticByName(const std::string compName)
  {
    LinguisticIterator_t it;

    for (it = linguisticVector.begin(); it != linguisticVector.end(); it++)
    {
        if (it->name.compare(compName)==0) return &(*it);
    }
    return NULL;
  }

}
