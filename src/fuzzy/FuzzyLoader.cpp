#include <fuzzy/FuzzyLoader.h>

namespace fuzzy {

int deBlankDoubleSpace(char *ln)  {
    char *outln=ln;
    int i,j;
    for (i=0,j=0; i<strlen(ln); i++,j++) {
        if (ln[i]==' ' && ln[i+1]==' ') j--;
        else  outln[j]=ln[i];
    }
    ln[j]='\0';
}

void tokenize(const std::string& str
             ,std::vector<std::string>& token
             ,const std::string& delim= " ")
{
    std::string::size_type lastPos = str.find_first_not_of(delim, 0);
    std::string::size_type pos     = str.find_first_of(delim, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        token.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delim, pos);
        pos = str.find_first_of(delim, lastPos);
    }
}

   void FuzzyLoader::loadLing(FILE *LFile, LinguisticSet* lingSet)
   {
     std::string line;
     char *lingName;
     char *newLingName;
     char *memName;
     char *pLine;
     lingName    = (char*) malloc(FZ_MAX_NAME+1);
     newLingName = (char*) malloc(FZ_MAX_NAME+1);
     memName     = (char*) malloc(FZ_MAX_NAME+1);
     pLine       = (char*) malloc(FZ_MAX_LINE+1);

     float a,b,c,d;
     std::vector<Linguistic>::iterator lastLing;
     std::vector<MembershipFunction>::iterator lastMf;

     while (fgets(pLine,FZ_MAX_LINE,LFile) != NULL) 
     {
         pLine[strlen(pLine)-1]='\0'; // put out the newline
         deBlankDoubleSpace(pLine);
        if (pLine[0] == '#') continue;
        if (pLine[0] == '\0') continue;

        sscanf(pLine,"%s %s %f %f %f %f\n",newLingName, memName,&a,&b,&c,&d);

        if(newLingName==NULL || memName==NULL) continue;

        if (strcmp(lingName,newLingName) != 0)
        {
           strcpy(lingName,newLingName);
           Linguistic l = Linguistic(lingName);
           lingSet->linguisticVector.push_back(l);
           lastLing = lingSet->linguisticVector.end();
           lastLing--;
        } 
        MembershipFunction mf = MembershipFunction(memName);
        lastLing->membershipFunctionVector.push_back(mf);
        lastMf = lastLing->membershipFunctionVector.end();        
        lastMf--;

        lastLing->value=0;
        lastMf->a = a; 
        lastMf->b = b; 
        lastMf->c = c; 
        lastMf->d = d; 
        lastMf->slopeLeft  = (float) FZ_MAX_LIMIT/(b-a);
        lastMf->slopeRight = (float) FZ_MAX_LIMIT/(d-c);
     }
   }

   void FuzzyLoader::loadRule(FILE *rFile
                ,LinguisticSet* iLSet
                ,LinguisticSet* oLSet
                ,RuleSet* rSet)
   {
     std::string line;
     char dlin[3]=" ";
     char *pLine;
     pLine = (char*) malloc(FZ_MAX_LINE+1);

     std::vector<Rule>::iterator lastRule;
     std::vector<RuleElement>::iterator lastRuleElement;

     while (fgets(pLine,FZ_MAX_LINE,rFile) != NULL) 
     {
       pLine[strlen(pLine)-1]='\0'; // put out the newline

       deBlankDoubleSpace(pLine);
       if (pLine[0] == '#') continue;
       if (pLine[0] == '\0') continue;

       std::vector<std::string> token;
       std::vector<std::string>::iterator itToken,endToken;
       std::string spLine(pLine);
       tokenize(spLine,token," ");
       itToken = token.begin();
       endToken = token.end();

       bool isOperator;
       LogicConnector prevLogicConnector = NONE;

       // Get the rule's name
       Rule newRule(*itToken);

       rSet->ruleVector.push_back (newRule);
       lastRule = rSet->ruleVector.end();
       lastRule--;

       lastRule->strength = 0;
       //====================================
       // loading the premises (if clause)
       //====================================
       itToken++;
       if (itToken->compare("if") && itToken->compare("IF"))
       {
          std::cout << "FuzzyLoader::loadRule: Error loading the rule "
                    << ", expectd 'if' " 
                    << ", Rule: " <<lastRule->name << std::endl;
          exit(1);
       }

       while ( (itToken!=endToken ) || 
               (!itToken->compare("then") && !itToken->compare("THEN"))
             )
       {
           itToken++;
           Linguistic *ling;
           MembershipFunction *mf;
           ling = iLSet->getLinguisticByName(*itToken);
           if (ling == NULL) 
           { std::cout << "FuzzyLoader::loadRule: Error loading the rule " 
                       << ", Linguistic not exist: " << *itToken
                       << ", Rule: " <<lastRule->name << std::endl; exit(1); }
           itToken++;
           if (      itToken->compare("is") 
                  && itToken->compare("IS")
                  && itToken->compare("not is") 
                  && itToken->compare("NOT IS")
              ) 
           {
              std::cout <<"FuzzyLoader::loadRule: Error loading the rule "
                    << ", expected 'is' or 'not is' " 
                    << ", Rule: " <<lastRule->name << std::endl;
              exit(1);
           }

           if (!itToken->compare("is") || !itToken->compare("IS"))
              isOperator = true;
           else
              isOperator = false;

           itToken++;

           mf =ling->getMembershipFunctionByName(*itToken);
           if (mf == NULL) 
           { std::cout <<"FuzzyLoader::loadRule: Error loading the rule " 
                       << ", Memberfunction not exist: " << *itToken
                       << ", Rule: " <<lastRule->name << std::endl;
              exit(1);
           }
           RuleElement newRuleElement;
           lastRule->if_RuleElementVector.push_back(newRuleElement);
           lastRuleElement = lastRule->if_RuleElementVector.end();
           lastRuleElement--;
          
           lastRuleElement->linguistic = ling;
           lastRuleElement->isOperator = isOperator;
           lastRuleElement->logicConnector = prevLogicConnector;
           lastRuleElement->membershipFunction = mf;
           
           itToken++;

           if(!itToken->compare("and") || !itToken->compare("AND"))
             prevLogicConnector = AND; 
           else if(!itToken->compare("or") || !itToken->compare("OR"))
             prevLogicConnector = AND; 
           else if (!itToken->compare("then") || !itToken->compare("THEN"))
             break;   
           else
           {
              std::cout <<"FuzzyLoader::loadRule: Error loading the rule "
                    << ", expected 'AND' or 'OR' "
                    << ", Rule: " <<lastRule->name << std::endl;
              exit(1);
           }
       } // end of while, the "if" clause.

       //====================================
       // loading the consequence (then clause)
       //====================================

       prevLogicConnector = NONE;
       while ( itToken!=endToken ) 
       {
           itToken++;
           Linguistic *ling;
           MembershipFunction *mf;
           ling = oLSet->getLinguisticByName(*itToken);
           itToken++;

           if (    itToken->compare("is") 
                && itToken->compare("IS")
                && itToken->compare("not is") 
                && itToken->compare("NOT IS")
              )
           {
              std::cout <<"FuzzyLoader::loadRule: Error loading the rule set "
                    << ", expected 'is' or 'not is' "
                    << ", Rule: " <<lastRule->name << std::endl;
              exit(1);
           }

           if (!itToken->compare("is") || !itToken->compare("IS"))
              isOperator = true;
           else
              isOperator = false;

           itToken++;

           mf =ling->getMembershipFunctionByName(*itToken);

           RuleElement newRuleElement;
           lastRule->then_RuleElementVector.push_back(newRuleElement);
           lastRuleElement = lastRule->then_RuleElementVector.end();
           lastRuleElement--;

           lastRuleElement->linguistic = ling;
           lastRuleElement->isOperator = isOperator;
           lastRuleElement->logicConnector = prevLogicConnector;
           lastRuleElement->membershipFunction = mf;

           itToken++;
           if  (itToken==endToken) break;
           if(!itToken->compare("and") || !itToken->compare("AND"))
             prevLogicConnector = AND;
           else if(!itToken->compare("or") || !itToken->compare("OR"))
             prevLogicConnector = AND;
           else
           {
              std::cout <<"FuzzyLoader::loadRule: Error loading the rule set "
                    << ", expected 'AND' or 'OR' "
                    << ", Rule: " <<lastRule->name << std::endl;
              exit(1);
           }
       } //end of while, the  "then"clause
     } //end of while 
   } // end of method 
 
   void FuzzyLoader::loadFromFile
           (FuzzySet* fuzzySet
           ,const char* inputLinguisticSetFileName
           ,const char* outputLinguisticSetFileName
           ,const char* ruleSetFileName) 
   { 
      FILE *iLFile;
      FILE *oLFile;
      FILE *rFile;

      iLFile = fopen(inputLinguisticSetFileName,"r");
      if (!iLFile) 
      {
         std::cerr << "Error open the input Linguistic file: " << inputLinguisticSetFileName << std::endl;
         exit(1);
      }

      oLFile = fopen(outputLinguisticSetFileName,"r");
      if (!oLFile) 
      {
         std::cerr << "Error open the uput Linguistic file: " << outputLinguisticSetFileName << std::endl;
         exit(1);
      }

      rFile = fopen(ruleSetFileName,"r");
      if (!rFile) 
      {
         std::cerr << "Error open the rules file: " << ruleSetFileName << std::endl;
         exit(1);
      }
      loadLing(iLFile,fuzzySet->inputLinguisticSet);
      fclose(iLFile);

      loadLing(oLFile,fuzzySet->outputLinguisticSet);
      fclose(oLFile);

      loadRule(rFile
              ,fuzzySet->inputLinguisticSet
              ,fuzzySet->outputLinguisticSet
              ,fuzzySet->ruleSet);
      fclose(rFile);
   }
} // end of inamespace fuzzy 


