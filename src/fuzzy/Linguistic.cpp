#include <fuzzy/Linguistic.h>

namespace fuzzy {

typedef std::vector<MembershipFunction>::iterator membershipFunctionIterator_t;

  void  Linguistic::listLinguistic()
  {
    membershipFunctionIterator_t it;

    for (it = membershipFunctionVector.begin(); it != membershipFunctionVector.end(); it++)
    {
      std::cout << name << ' ' 
                << it->name  
                << " a: " << it->a
                << " b: " << it->b
                << " c: " << it->c
                << " d: " << it->d
                << " degree: " << it->degree
                << " lopeLeft: " << it->slopeLeft 
                << " lopeRight: " << it->slopeRight
                << '\n'; 
    }
  }

  MembershipFunction* Linguistic::getMembershipFunctionByName(std::string compName)
  {
    membershipFunctionIterator_t it;

    for (it = membershipFunctionVector.begin(); it != membershipFunctionVector.end(); it++)
    {
        if (it->name.compare(compName)==0) return &(*it);
    }
    return NULL;
  }


}
