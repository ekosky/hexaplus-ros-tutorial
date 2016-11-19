#include <fuzzy/MembershipFunction.h>

namespace fuzzy {

  void  MembershipFunction::calcDegreeMembership(float inputValue)
  {
       float delta1, delta2;
       delta1 = inputValue - a;
       delta2 = d - inputValue; 
        if ((delta1 <= 0) || (delta2 <=0 )) {
          degree = 0;
        } else {
          degree= minimum((slopeLeft*delta1)
                             ,(slopeRight*delta2));
        }
        degree = minimum(degree,FZ_MAX_LIMIT);
  }

  float MembershipFunction::MembershipFunction::calcTrapeziumArea() 
  {
    float areaTrap;
    float top;
    float base;
    float temp1, temp2;
    temp1 = (degree/slopeRight);
    temp2 = (degree/slopeLeft);

    base = d - a;
    top = base - temp1 - temp2;

    areaTrap = degree * (base + top)/2.0;
    return (areaTrap);
  }
}
