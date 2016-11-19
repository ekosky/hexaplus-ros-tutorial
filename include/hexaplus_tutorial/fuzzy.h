// Robotica Movel
// by Emanoel Koslosky

#ifndef FUZZY
#define FUZZY 1
#define FZ_MAX_NAME 101
#define FZ_MAX_LIMIT 1
#define FZ_MAX_OUTPUT 0 
#define minimum(a,b) a<b?a:b
#define maximum(a,b) a>b?a:b

//Membership function struct
typedef struct mftp {
  char   name[FZ_MAX_NAME]; 
  float  value;     
  float  a,b,c,d;   
  float  slope_left, slope_right;  
  struct mftp *next; 
} mf_tp;

// Linguistic struct, input or output
typedef struct linguistictp {
   char   name[FZ_MAX_NAME];
   float  value;       
   mf_tp  *mf;       
   struct linguistictp *next;

} linguistic_tp;

typedef struct element_ruletp {
  char    *name_mf;            
  char    *name_ling;            
  float   *value;    
  char     operador_is;     
  struct   element_ruletp *next;
} element_rule_tp;

typedef struct ruletp {
  char name[FZ_MAX_NAME];
  float strength;
  element_rule_tp *e_rule_if;
  element_rule_tp *e_rule_then;
  struct ruletp   *next;
} rule_tp;

linguistic_tp* read_ling(const char *firead_mf);

int calc_degree_membership (mf_tp *mf, float vl_input);

float calc_area_trapezio (mf_tp *mf);

void fuzzification(linguistic_tp *input_base); 

void rule_evaluation(rule_tp  *rule_base); 

linguistic_tp* find_ling(linguistic_tp *ling_base, const char *nm_ling);

mf_tp* find_mf(linguistic_tp* ling, const char *mf_name); 

rule_tp* read_rules(const char *firead_rule, linguistic_tp *input_base, linguistic_tp *output_base);

void defuzzification(linguistic_tp *so_base); 

linguistic_tp* copia_ling(linguistic_tp *ling_base); 

void print_ling (linguistic_tp *input_base); 

void print_rules( rule_tp *rule_base);

void print_rules_strength( rule_tp *rule_base);

void print_io(linguistic_tp *input_base,linguistic_tp *output_base);

linguistic_tp* find_ling(linguistic_tp *ling_base, const char *nm_ling); 

void fuzzing (linguistic_tp *l_in, rule_tp *rule, linguistic_tp *l_out); 


#endif
