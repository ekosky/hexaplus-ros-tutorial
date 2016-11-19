#ifndef _MEMBERSHIP_FUNCTION_
#define _MEMBERSHIP_FUNCTION_
#include <fuzzy/fuzzyDefine.h>

namespace fuzzy {

   class MembershipFunction {
      public:
         MembershipFunction() {};        
         MembershipFunction(char* newName) 
           { name.assign(newName);
             degree     = 0;
             a=b=c=d    = 0;
             slopeLeft  = 0;
             slopeRight = 0;
           };
         virtual ~MembershipFunction() {};
         std::string  name;
         float        degree;
         float   a,b,c,d;
         float   slopeLeft;
         float   slopeRight;
         void calcDegreeMembership(float inputValue);
         float calcTrapeziumArea();
   };
}


#endif
