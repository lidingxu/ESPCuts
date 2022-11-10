/**@file   term_signomial.c
 * @brief  handler for a signomial term 
 * @author Liding Xu
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __SCIP_TERM_SIGNOM_H__
#define __SCIP_TERM_SIGNOM_H__

#include "scip/scip.h"
#include <vector>
#include <list>
#include <tuple>
#include <utility>
#include <map>

using namespace std;

enum BIN_RELATION {LE, EQ, GE};
enum CURVE {Concave, Convex, NonConvex};

typedef struct Power_Term
{
   SCIP_VAR* var;
   SCIP_Real exponent;
} POWER_TERM;

class SIGNOM_TERM
{
private:
    int size;
    SCIP_VAR* liftvar; 
    vector<POWER_TERM> powterms;
    list<SCIP_VAR *> vars;
    map<SCIP_VAR *, SCIP_Real> vars_val;
    //map<SCIP_VAR*, tuple<SCIP_Real, SCIP_Real, SCIP_Real, SCIP_Bool>> vars_info; // vars to value, lower bound, upper bound and is integer. 

    // leftpowerterms* innerrelation rightpowterms*
    // if innererlation is LE
    // leftaffine* + leftaffine0* innerrelation rightpowterms*;
    // else
    // leftpowterms* innerrelation rightaffine* + rightaffine0*
    vector<POWER_TERM> leftpowterms;
    vector<POWER_TERM> rightpowterms;
    vector<SCIP_Real> leftaffine, rightaffine;
    SCIP_Real leftaffine0, rightaffine0;

    vector<SCIP_Real> leftnormexponents;
    vector<SCIP_Real> rightnormexponents;
 
    int yleftind; // the position of y index in left
    SCIP_Real y_lb, y_ub;
    enum BIN_RELATION innerrelation; // violated relation in transformed form, left_val * innerrelation right_val*
    SCIP_Bool isConstructed; // is S-free set constructed
    SCIP_Bool isnormalized; // is normalized

public:

   SIGNOM_TERM(
       SCIP * scip,
       SCIP_VAR * liftvar_,
       list<POWER_TERM>& powterms_
   );


    void printSignomTerm(SCIP * scip); // helper method to print an recorded signomial term

    void initSep(); // initialize the term's internal parameters

    SCIP_Bool isNonNeg(SCIP * scip); // is all variable in Nonnegative orthant

    SCIP_Bool isviolatedOriginal(SCIP * scip); // is the contraint violated in original form

    SCIP_Bool isviolatedTransfrom(SCIP * scip); // is the contraint violated in transfromed form

    SCIP_Bool isviolatedTransfromDiscrete(SCIP * scip); // is the contraint violated in transfromed form with dicrete domain

    SCIP_Bool constructSfree(SCIP * scip); // construct the S-free set

    //SCIP_Bool constructSfreeDiscrete(SCIP * scip); // construct the S-free set using discrete and bound information

    SCIP_Real evalRay(SCIP * scip, map<SCIP_VAR*, SCIP_Real> & ray, SCIP_Real t); // eval the function value gamma(zlp+t*ray)

    SCIP_Real uppert(SCIP * scip, map<SCIP_VAR*, SCIP_Real> & ray); // the upper bound: argmax_t zlp+t*ray>=0

    SCIP_Bool sepouter_supermodular(SCIP * scip,  map<SCIP_VAR *, SCIP_Real> & coefficient, SCIP_Real & constant);

    SCIP_Bool sepouter_lcp(SCIP * scip,  map<SCIP_VAR *, SCIP_Real> & coefficient, SCIP_Real & constant);

    SCIP_Bool sepouter(SCIP * scip,  map<SCIP_VAR *, SCIP_Real> & coefficient, SCIP_Real & constant, int outer_cut); // separate outer approximation cuts

    //SCIP_Real evalRayDiscrete(SCIP * scip, map<SCIP_VAR*, SCIP_Real> & ray, SCIP_Real t); // eval the function value gamma(zlp+t*ray)
 
    inline list<SCIP_VAR *> & getVars(){ return vars;};
    inline int getSize(){ return size;};
};



#endif