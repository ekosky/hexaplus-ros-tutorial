#ifndef _LINGUISTIC_
#define _LINGUISTIC_
#include <fuzzy/fuzzyDefine.h>
#include <fuzzy/MembershipFunction.h>

namespace fuzzy {

   class Linguistic {
      public:
         Linguistic() {}; 
         Linguistic(std::string newName):name(newName) {}; 
         Linguistic(char* newName) {name.assign(newName);};
         virtual ~Linguistic() {};
 
         std::string  name;
         float   value;
         std::vector<MembershipFunction> membershipFunctionVector;
         void listLinguistic();
         MembershipFunction* getMembershipFunctionByName(std::string name);

   };
}
#endif
