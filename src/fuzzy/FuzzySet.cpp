#include <fuzzy/FuzzySet.h>

namespace fuzzy {
         //RuleSet ruleset;
         //LinguisticSet inputLinguisticSet;
         //LinguisticSet outputLinguisticSet;
         FuzzySet::FuzzySet()
         {
             inputLinguisticSet  = new LinguisticSet();
             outputLinguisticSet = new LinguisticSet();
             ruleSet             = new RuleSet();
             name = "";
         }
         FuzzySet::FuzzySet(const std::string newName):name(newName)
         {
             inputLinguisticSet  = new LinguisticSet();
             outputLinguisticSet = new LinguisticSet();
             ruleSet             = new RuleSet();
         }

         void FuzzySet::fuzzyfication()
         {

            typedef std::vector<Linguistic>::iterator linguisticIterator_t;
            typedef std::vector<MembershipFunction>::iterator membershipFunctionIterator_t;
            linguisticIterator_t it_Ling; 
            membershipFunctionIterator_t it_Mem; 

            for (it_Ling=inputLinguisticSet->linguisticVector.begin()
                ;it_Ling !=inputLinguisticSet->linguisticVector.end(); it_Ling++) {
                for (it_Mem=it_Ling->membershipFunctionVector.begin() 
                     ;it_Mem!=it_Ling->membershipFunctionVector.end(); it_Mem++) {
                     it_Mem->calcDegreeMembership(it_Ling->value);
                }
             }
         }

         void FuzzySet::ruleInference()
         {
            typedef std::vector<Rule>::iterator RuleIterator_t;
            typedef std::vector<RuleElement>::iterator RuleElementIterator_t;
            
            RuleIterator_t        it_r;
            RuleElementIterator_t it_e;

            //Clean up IF elements for new round
            for (it_r=ruleSet->ruleVector.begin(); it_r != ruleSet->ruleVector.end(); it_r++)
            {
                it_r->strength=0;
                for (it_e=it_r->then_RuleElementVector.begin(); it_e != it_r->then_RuleElementVector.end(); it_e++)
                {
                    it_e->linguistic->value= 0;
                    it_e->membershipFunction->degree = 0;
                }
            }

            // Inference
            float strength_tmp;
            for (it_r=ruleSet->ruleVector.begin(); it_r != ruleSet->ruleVector.end(); it_r++)
            {
                // Calculate the stregth of the Rule
                strength_tmp = FZ_MAX_LIMIT;
                for (it_e=it_r->if_RuleElementVector.begin(); it_e != it_r->if_RuleElementVector.end(); it_e++)
                {
                    strength_tmp = minimum(strength_tmp, it_e->membershipFunction->degree);
                    if (!it_e->isOperator)
                       strength_tmp = 1-strength_tmp; 
                }

                // Calculate the stregth of the Rule
                for (it_e=it_r->then_RuleElementVector.begin(); it_e != it_r->then_RuleElementVector.end(); it_e++)
                {
                    it_e->membershipFunction->degree = maximum(strength_tmp,it_e->membershipFunction->degree);
                    if (!it_e->isOperator)
                       it_e->membershipFunction->degree = 1 - it_e->membershipFunction->degree;
                }
                it_r->strength = strength_tmp;
            }
         }

         void FuzzySet::defuzzification()
         {

            typedef std::vector<Linguistic>::iterator LinguisticIterator_t;
            typedef std::vector<MembershipFunction>::iterator MembershipFunctionIterator_t;
            
            LinguisticIterator_t         it_l;
            MembershipFunctionIterator_t it_m;

            float sum_prod;
            float sum_area;
            float area, centroide;

            for (it_l=outputLinguisticSet->linguisticVector.begin(); it_l != outputLinguisticSet->linguisticVector.end(); it_l++)
            {
                sum_prod=sum_area=0;
                for (it_m = it_l->membershipFunctionVector.begin(); it_m !=  it_l->membershipFunctionVector.end(); it_m++)
                {
                    area = it_m->calcTrapeziumArea();
                    centroide = it_m->a + ((it_m->d - it_m->a) /2.0);
                    sum_prod += area * centroide;
                    sum_area += area;
                }   

                if (sum_area==0)
                   it_l->value = FZ_MAX_OUTPUT;
                else
                  {
                   it_l->value = sum_prod/sum_area;
                  }
            }
         }

         void FuzzySet::fuzzifying()
         {
           fuzzyfication();
           ruleInference();
           defuzzification();
         }

}

