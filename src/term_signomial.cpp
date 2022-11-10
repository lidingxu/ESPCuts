/**@file   term_signomial.cpp
 * @brief  handler for a signomial term 
 * @author Liding Xu
 *
 */
/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/
#define SCIP_DEBUG
#include "term_signomial.h"
#include<algorithm>

SIGNOM_TERM::SIGNOM_TERM(
    SCIP * scip,  
    SCIP_VAR * liftvar_,
    list<POWER_TERM>& powterms_
){
    liftvar = liftvar_;
    powterms = vector<POWER_TERM>(powterms_.begin(), powterms_.end());
    vars.push_back(liftvar);
    vars_val[liftvar] = 0; 
    //vars_info[liftvar] = make_tuple(0, -SCIPinfinity(scip), SCIPinfinity(scip), FALSE); 
    for(auto & powterm: powterms){
        vars.push_back(powterm.var);
        vars_val[powterm.var] = 0; 
        //vars_info[powterm.var] = make_tuple(0, -SCIPinfinity(scip), SCIPinfinity(scip), FALSE);
    }
    size = vars.size();
    isConstructed = FALSE;
    //isContinuous = FALSE;
    POWER_TERM powterm = {.var = liftvar, .exponent = 1};
    // y = \prod_{ j in J} x_j^{p_j}
    // contruct the normalized DC representation
    SCIP_Real leftexponentsum = 0;
    SCIP_Real rightexponentsum = 0;
    leftpowterms.push_back(powterm);
    leftexponentsum += 1;
    for(auto powterm_: powterms){
        if(SCIPisNegative(scip, powterm_.exponent)){
            powterm_.exponent = -powterm_.exponent;
            leftexponentsum += powterm_.exponent;
            leftpowterms.push_back(powterm_);
        }
        else{
            rightexponentsum += powterm_.exponent;
            rightpowterms.push_back(powterm_);
        }
    }
    SCIP_Real maxexponent = max(leftexponentsum, rightexponentsum);
    for(auto & powterm_: leftpowterms){
        powterm_.exponent /= maxexponent;
    }
    for(auto & powterm_: rightpowterms){
        powterm_.exponent /= maxexponent;
    }
    //printf("%d %d\n", int(leftpowterms.size()), int(rightpowterms.size()));
    //printSignomTerm(scip);
    leftaffine = vector<SCIP_Real> (leftpowterms.size());
    rightaffine = vector<SCIP_Real> (rightpowterms.size());
    leftnormexponents = vector<SCIP_Real> (leftpowterms.size());
    rightnormexponents = vector<SCIP_Real> (rightpowterms.size());
}

void SIGNOM_TERM::printSignomTerm(SCIP * scip){
   SCIPdebugMessage("\n original formulation:");
   printf("y: %s. ", SCIPvarGetName(liftvar));
   for(auto & powterm: powterms){
      printf("%s^%f ", SCIPvarGetName(powterm.var), powterm.exponent);
   }
   SCIPdebugMessage("\n extended formulation:");
   for(auto & powterm: leftpowterms){
      printf("%s^%f ", SCIPvarGetName(powterm.var), powterm.exponent);
   }   
   printf("=");
   for(auto & powterm: rightpowterms){
      printf("%s^%f ", SCIPvarGetName(powterm.var), powterm.exponent);
   }   
   printf("\n");
};

void SIGNOM_TERM::initSep(){
    yleftind = 0;
    y_lb = 1;
    y_ub = 1;
    innerrelation = EQ;
    isConstructed = FALSE;
};


SCIP_Bool SIGNOM_TERM::constructSfree(SCIP * scip){
    assert(innerrelation != EQ);
    if(isConstructed){
        return TRUE;
    }
    // construct S-free set
    // compute the value of vars
    for(auto var: vars){
        vars_val[var] = SCIPvarGetLPSol(var);
    }
    // decide the side to linearize
    SCIP_Real & affine0 = innerrelation == LE ? leftaffine0 : rightaffine0;
    vector<SCIP_Real> & affine = innerrelation == LE ? leftaffine : rightaffine;
    vector<POWER_TERM> & sidepowterms = innerrelation == LE ? leftpowterms : rightpowterms;

    // compute the linearized function
    SCIP_Real val = 1; // x_1^{p_1} ... x_n^{p_n}
    SCIP_Real sumeexponant = 0;
    for(auto & sidepowterm: sidepowterms){
        val *= pow(vars_val[sidepowterm.var], sidepowterm.exponent);
        if(SCIPisFeasLE(scip, vars_val[sidepowterm.var], 1e-4)){ // if the lowerbound is too small, some numerical erros may occur, quit
            return FALSE;
        }
        sumeexponant += sidepowterm.exponent;
    }   
    affine0 = val * (1-sumeexponant);
    // gradient_i = p_i x_1^{p_1} ..x_i^{p_i-1}.. x_n^{p_n}=  p_i x_1^{p_1} ..x_i^{p_i}.. x_n^{p_n} /x_i
    for(int i = 0; i < sidepowterms.size(); i++){
        affine[i] = sidepowterms[i].exponent * val / vars_val[sidepowterms[i].var]; // sidepowterms[i].exponent * pow(vars_val[sidepowterms[i].var], sidepowterms[i].exponent - 1);
    }
    return TRUE;
}

SCIP_Real SIGNOM_TERM::uppert(SCIP * scip, map<SCIP_VAR*, SCIP_Real> & ray){
    SCIP_Real uppert = SCIPinfinity(scip) / 2;
    for(auto var: vars){
        if(SCIPisFeasNegative(scip, ray[var])){
            SCIP_Real tzero = - SCIPvarGetLPSol(var) / ray[var];
            uppert = tzero < uppert ? tzero: uppert;
        }   
    }
    return uppert;
}



SCIP_Real SIGNOM_TERM::evalRay(SCIP * scip, map<SCIP_VAR*, SCIP_Real> & ray, SCIP_Real t){
    SCIP_Real affineside = 0;
    SCIP_Real nonlinearside = 1;
    SCIP_Real & affine0 = innerrelation == LE ? leftaffine0 : rightaffine0;
    vector<SCIP_Real> & affine = innerrelation == LE ? leftaffine : rightaffine;
    vector<POWER_TERM> & affinepowterms = innerrelation == LE ? leftpowterms : rightpowterms;    
    vector<POWER_TERM> & nonlinearpowterms = innerrelation == GE ? leftpowterms : rightpowterms;    
    affineside = affine0;
    int affine_id = 0;
    for(auto powterm: affinepowterms){
        affineside += affine[affine_id] * (vars_val[powterm.var] + t* ray[powterm.var]);
        affine_id++;
    }
    for(auto powterm: nonlinearpowterms){
        nonlinearside *= pow(vars_val[powterm.var] + t* ray[powterm.var], powterm.exponent);
    }
    return nonlinearside - affineside;
}



SCIP_Bool SIGNOM_TERM::isNonNeg(SCIP * scip){
    SCIP_Bool isNonNeg_ = TRUE;
    for(auto & powterm: powterms){
        //SCIPdebugMessage("%d\n", powterms.size());
        isNonNeg_ = SCIPisFeasGE(scip, SCIPvarGetLbLocal(powterm.var), 0);
        if(!isNonNeg_){
            break;
        }
        y_lb *=  pow(SCIPvarGetLbLocal(powterm.var), powterm.exponent);
        y_ub *=  pow(SCIPvarGetUbLocal(powterm.var), powterm.exponent);
    }
    if(isNonNeg_){
        //SCIPdebugMessage("%f %f\n", SCIPvarGetLPSol(liftvar), y_lb);
    }
    y_lb = max(y_lb,SCIPvarGetLbLocal(liftvar));
    y_ub = min(y_ub,SCIPvarGetUbLocal(liftvar));
    //SCIPdebugMessage("??\n");
    return isNonNeg_;
}

SCIP_Bool  SIGNOM_TERM::isviolatedOriginal(SCIP * scip){
    SCIP_Real original_y =  SCIPvarGetLPSol(liftvar);
    SCIP_Real original_expr = 1;
    for(auto & powterm: powterms){
        original_expr *= pow(SCIPvarGetLPSol(powterm.var), powterm.exponent);
    }   
    return !SCIPisFeasEQ(scip, original_y, original_expr);
}

SCIP_Bool SIGNOM_TERM::isviolatedTransfrom(SCIP * scip){
    SCIP_Real leftval = 1;
    SCIP_Real rightval = 1;
    for(auto & powterm: leftpowterms){
        //SCIPdebugMessage("%f %f\n", SCIPvarGetLPSol(powterm.var), powterm.exponent);
        leftval *= pow(SCIPvarGetLPSol(powterm.var), powterm.exponent);
    }   
    for(auto & powterm: rightpowterms){
        //SCIPdebugMessage("%f %f\n", SCIPvarGetLPSol(powterm.var), powterm.exponent);
        rightval *= pow(SCIPvarGetLPSol(powterm.var), powterm.exponent);
    }  
    if(SCIPisFeasEQ(scip, leftval, rightval)){
        return FALSE;
    }
    else{
        if(SCIPisFeasGE(scip, leftval, rightval)){
            innerrelation = GE;
            //SCIPdebugMessage("%f %f %f\n",leftval, rightval, leftval - rightval);
        }
        else{
            innerrelation = LE;
            //SCIPdebugMessage("%f %f %f\n", leftval, rightval, -leftval + rightval);
        }
        return TRUE;
    }
}


SCIP_Bool SIGNOM_TERM::sepouter(SCIP * scip, map<SCIP_VAR *, SCIP_Real> & coefficient, SCIP_Real & constant, int outer_cut){
    if(outer_cut == 1){
        return sepouter_supermodular(scip, coefficient, constant);
    }
    else if(outer_cut == 2){
        return sepouter_lcp(scip, coefficient, constant);
    }
    return FALSE;
}

// separate a supermodular inequality
SCIP_Bool SIGNOM_TERM::sepouter_supermodular(SCIP * scip, map<SCIP_VAR *, SCIP_Real> & coefficient, SCIP_Real & constant){
    //printSignomTerm(scip);
    vector<POWER_TERM> & leftconcavepowterms = innerrelation == LE? leftpowterms: rightpowterms;
    vector<POWER_TERM> & rightconcavepowterms = innerrelation == GE? leftpowterms: rightpowterms;
    // we have concave term* <= concave term*, we want concave term* >= concave term*, and the outer approximation of
    // concave term >= concave term is linearized concave term >= linearied concave term. It is violated if we still have
    // linearized concave term* <= linearized concave term*  


    // we want to linearize the rightconcave powerterm
    if(rightconcavepowterms.size() > 6){
        return FALSE;
    }
    // the translated value to [0, 1]
    vector<SCIP_Real> w(rightconcavepowterms.size()); // w, with index
    for(int i = 0; i < rightconcavepowterms.size(); i++){
        auto var = rightconcavepowterms[i].var;
        SCIP_Real val = SCIPvarGetLPSol(var);
        SCIP_Real exponant = rightconcavepowterms[i].exponent;
        SCIP_Real lb = SCIPvarGetLbLocal(var);
        SCIP_Real ub = SCIPvarGetUbLocal(var);
        // make sure the bound is appropriate
        if(SCIPisInfinity(scip, ub)|| lb < 0 || SCIPisFeasEQ(scip, lb, ub)){
            return FALSE;
        } 
        // translate valule in [0,1]
        w[i] = (val - lb)/(ub-lb);
    }
        
    constant = 0;


    // we assume the valid inequality a x + constant >= 0

    // linearized the right term is
    // s invpi (v) + lb^\gamma, where w = invpi(v)
    constant = 0; // - lb^\gamma
    SCIP_Real max_activity = -SCIPinfinity(scip);


    // the cardinality of rightvaluepowerterms
    int card = rightconcavepowterms.size();
    // the number of subsets, 2^card
    int numsubsets = 1 << card;
    // the indicator for a subset
    vector<bool> indicator(rightconcavepowterms.size(), false);
    for(int i = 0; i < numsubsets; i++){
        // carry bits
        for(int j = 0; j  < card; j++){
            if(indicator[j] == false){
                indicator[j] = true;
                break;
            }
            else{
                indicator[j] = false;
            } 
        }

        // temp coefficients
        map<SCIP_VAR *, SCIP_Real> coefficient_;
        SCIP_Real g0 = 1; // zero
        SCIP_Real gS = 1; // S associated to indicator
        SCIP_Real gN = 1; // full
        for(int j = 0; j < card; j++){
            auto var = rightconcavepowterms[j].var;
            SCIP_Real val = SCIPvarGetLPSol(var);
            SCIP_Real exponant = rightconcavepowterms[j].exponent;
            SCIP_Real lb = SCIPvarGetLbLocal(var);
            SCIP_Real ub = SCIPvarGetUbLocal(var);
            if(indicator[j]){
                gS *= pow(ub,exponant);
            }
            else{
                gS *= pow(lb,exponant);
            }
            gN *= pow(ub,exponant);
            g0 *= pow(lb,exponant);
        }


        // g(\chi_{S}) + \sum_{j \in H \smallsetminus S} \rho(j,S) w_j -  \sum_{j \in S} \rho(j,N \smallsetminus \{j\}) (1-w_j) & \le t
        SCIP_Real activity1 = gS;
        for(int j = 0; j < card; j++){
            auto var = rightconcavepowterms[j].var;
            //SCIP_Real val = SCIPvarGetLPSol(var);
            SCIP_Real exponant = rightconcavepowterms[j].exponent;
            SCIP_Real lb = SCIPvarGetLbLocal(var);
            SCIP_Real ub = SCIPvarGetUbLocal(var);
            if(!indicator[j]){
                coefficient_[var]= gS * (pow(ub/lb,exponant) -1 );
                activity1 += coefficient_[var] * w[j];
            }
            else{
                coefficient_[var]= gN * (1-pow(lb/ub,exponant));
                activity1 += -coefficient_[var] * (1 -w[j]);
            }
        }
        if(activity1 > max_activity){
            max_activity = activity1;
            constant = -gS;
            //SCIP_Real activity1_ = 0;
            for(int j = 0; j < card; j++){
                auto var = rightconcavepowterms[j].var;
                SCIP_Real val = SCIPvarGetLPSol(var);
                SCIP_Real exponant = rightconcavepowterms[j].exponent;
                SCIP_Real lb = SCIPvarGetLbLocal(var);
                SCIP_Real ub = SCIPvarGetUbLocal(var);
                if(!indicator[j]){
                    coefficient[var]= -coefficient_[var]/(ub-lb);
                    constant += -coefficient_[var] * (-lb)/(ub-lb);
                }
                else{
                    //printf(" %d ", j);
                    coefficient[var]= -coefficient_[var]/(ub-lb);
                    constant += coefficient_[var] * ub / (ub-lb);
                }
            }
        }

        //  g(\chi_{S}) + \sum_{j \in H \smallsetminus S} \rho(j,\varnothing) w_j -  \sum_{j \in S} \rho(j,S \smallsetminus \{j\}) (1-w_j) &\le t
        SCIP_Real activity2 = gS;
        for(int j = 0; j < card; j++){
            auto var = rightconcavepowterms[j].var;
            SCIP_Real val = SCIPvarGetLPSol(var);
            SCIP_Real exponant = rightconcavepowterms[j].exponent;
            SCIP_Real lb = SCIPvarGetLbLocal(var);
            SCIP_Real ub = SCIPvarGetUbLocal(var);
            if(!indicator[j]){
                coefficient_[var]= g0 * (pow(ub/lb,exponant) -1 );
                activity2 += coefficient_[var] * w[j];
            }
            else{
                coefficient_[var]= gS * (1-pow(lb/ub,exponant));
                activity2 += -coefficient_[var] * (1 -w[j]);
            }
        }
        if(activity2 > max_activity){
            max_activity = activity2;
            constant = -gS;
            for(int j = 0; j < card; j++){
                auto var = rightconcavepowterms[j].var;
                SCIP_Real val = SCIPvarGetLPSol(var);
                SCIP_Real exponant = rightconcavepowterms[j].exponent;
                SCIP_Real lb = SCIPvarGetLbLocal(var);
                SCIP_Real ub = SCIPvarGetUbLocal(var);
                if(!indicator[j]){
                    coefficient[var]= -coefficient_[var]/(ub-lb);
                    constant += -coefficient_[var] * (-lb)/(ub-lb);
                }
                else{
                    //printf(" %d ", j);
                    coefficient[var]= -coefficient_[var]/(ub-lb);
                    constant += coefficient_[var] * ub / (ub-lb);
                }
            }
        }
    }
    SCIP_Real rightval = max_activity;


    // linearize the left part
    SCIP_Real leftval = 1; // x_1^{p_1} ... x_n^{p_n}
    SCIP_Real sumeexponant = 0;
    for(auto & sidepowterm: leftconcavepowterms){
        auto var = sidepowterm.var;
        SCIP_Real val = SCIPvarGetLPSol(var);
        //printf("%s %f\n",  SCIPvarGetName(var), val);
        leftval *= pow(val, sidepowterm.exponent);
        sumeexponant += sidepowterm.exponent;
    }   

    // left constant part = leftval * (1-sumeexponant)
    constant += leftval * (1-sumeexponant);
    
    //SCIP_Real leftactivity = leftval * (1-sumeexponant);
    // gradient_i = p_i x_1^{p_1} ..x_i^{p_i-1}.. x_n^{p_n}=  p_i x_1^{p_1} ..x_i^{p_i}.. x_n^{p_n} /x_i
    // to do: how to improve the numerical accurarcy of gradient cuts? For example, x^a, when x is close to zero, the gradient cut
    // may suffer from numerical problems, test gasnet_al3
    for(int i = 0; i < leftconcavepowterms.size(); i++){
        auto var = leftconcavepowterms[i].var;
        SCIP_Real val = SCIPvarGetLPSol(var);
        //SCIPdebugMessage("%f\n", SCIPvarGetLbLocal(var));
        if(SCIPisFeasLE(scip, val, 1e-4)){ // if the lowerbound is too small, some numerical errors may occur, quit
            return FALSE;
        }
        coefficient[var] = leftconcavepowterms[i].exponent * leftval / val; // sidepowterms[i].exponent * pow(vars_val[sidepowterms[i].var], sidepowterms[i].exponent - 1);

    }

    //SCIPdebugMessage("super\n");
    
    if(SCIPisFeasLT(scip, leftval, rightval)){
        return TRUE;
    }
    else{
        return FALSE;
    }

}



// separate outer approximation cut using lift-convexify-project (lcp)
SCIP_Bool SIGNOM_TERM::sepouter_lcp(SCIP * scip, map<SCIP_VAR *, SCIP_Real> & coefficient, SCIP_Real & constant){
    // normalized again
    SCIP_Real sumleftexponant = 0;
    for(int i = 0; i < leftnormexponents.size(); i++){
        sumleftexponant += leftpowterms[i].exponent;
    }
    SCIP_Real leftsum = 1 - sumleftexponant;
    for(int i = 0; i < leftnormexponents.size(); i++){
        leftsum += leftpowterms[i].exponent;
        leftnormexponents[i] = leftpowterms[i].exponent / leftsum;
    }   
    SCIP_Real sumrightexponent = 0;
    for(int i = 0; i < rightnormexponents.size(); i++){
        sumrightexponent += rightpowterms[i].exponent;
    }   
    SCIP_Real rightsum = 1 - sumrightexponent;
    for(int i = 0; i < rightnormexponents.size(); i++){
        rightsum += rightpowterms[i].exponent;
        rightnormexponents[i] = rightpowterms[i].exponent / rightsum;
    }      

    // we have concave term* <= concave term*, we want concave term* >= concave term*, and the outer approximation of
    // concave term >= concave term is linearized concave term >= linear concave term. It is violated if we still have
    // linearized concave term* <= linear concave term*
    vector<POWER_TERM> & leftconcavepowterms = innerrelation == LE? leftpowterms: rightpowterms;
    //vector<SCIP_Real> & leftconcaveexponent = innerrelation == LE? leftnormexponents: rightnormexponents;
    vector<POWER_TERM> & rightconcavepowterms = innerrelation == GE? leftpowterms: rightpowterms;
    // zeta  
    vector<SCIP_Real> & rightconcaveexponent = innerrelation == GE? leftnormexponents: rightnormexponents;
    // we assume the valid inequality a x + constant >= 0

    SCIP_Bool debug_envelope  = TRUE;

    SCIP_Real rightval = 1;
    SCIP_Real rightrealval = 1;
    SCIP_Real rightlb = 1;
    SCIP_Real rightub = 1;
    constant = 1;


    for(int i = 0; i < rightconcavepowterms.size(); i++){
        auto var = rightconcavepowterms[i].var;
        SCIP_Real val = SCIPvarGetLPSol(var);
        SCIP_Real exponant = rightconcaveexponent[i];
        SCIP_Real lb = SCIPvarGetLbLocal(var);
        SCIP_Real ub = SCIPvarGetUbLocal(var);
        //SCIPdebugMessage("%f,%f,%f\n", val, lb, ub);
        if(SCIPisInfinity(scip, ub)|| lb < 0|| SCIPisFeasEQ(scip, lb, ub)){
            return FALSE;
        } 
        if(i == 0){ // construct under estimator of u^{\zeta}:  slope * u + intercept
            // compute linearization
            SCIP_Real slope = (pow(ub, exponant) - pow(lb, exponant)) / (ub - lb); 
            SCIP_Real intercept =  - slope *  lb +  pow(lb, exponant);
            // update linearization
            constant = intercept;
            coefficient[var] = slope;
            // evaluate F(u)
            rightval = slope * val + intercept;
            // compute next s bound
            rightlb =  pow(lb, exponant);
            rightub =  pow(ub, exponant);
            // evluate u^(\zeta)
            rightrealval = pow(val, exponant);
        }
        else{
            // construct under estimator of s^{1-\zeta} u^{\zeta}:  slope_s * s + slope_u * u + intercept
            // extreme points
            SCIP_Real bu[2] = {lb, ub};
            SCIP_Real bs[2] = {rightlb, rightub};
            SCIP_Real fv00 =  pow(bu[0], exponant) * pow(bs[0], 1- exponant);
            SCIP_Real fv01 =  pow(bu[0], exponant) * pow(bs[1], 1- exponant);
            SCIP_Real fv10 =  pow(bu[1], exponant) * pow(bs[0], 1- exponant);
            SCIP_Real fv11 =  pow(bu[1], exponant) * pow(bs[1], 1- exponant);
            SCIP_Real d1 = ub - lb;
            SCIP_Real d2 = rightub - rightlb;

            // compute linearization
            SCIP_Real intercept = 0;
            SCIP_Real slope_s = 0, slope_u = 0;

            // 00: lb, rightlb
            SCIP_Real intercept00 = 0;
            SCIP_Real slope00_s = 0, slope00_u = 0;   
            slope00_u = (fv10 - fv00) / d1;
            slope00_s = (fv01 - fv00) / d2;
            intercept00 = fv00 + slope00_u * (-bu[0]) +  slope00_s * (-bs[0]);           
            // F00(us)
            SCIP_Real rightval00 = intercept00 + slope00_u * val + slope00_s * rightval;
            if(debug_envelope){
                //if(fabs(intercept00 + slope00_u * bu[0] + slope00_s * bs[0] - fv00 ) > 1e-9){
                //    SCIPdebugMessage("%f %f %f\n", intercept00 + slope00_u * bu[0] + slope00_s * bs[0], fv00 , intercept00 + slope00_u * bu[0] + slope00_s * bs[0] - fv00);
                //    SCIPdebugMessage("%f %f %f %f\n", intercept00 + slope00_u * bu[0] + slope00_s * bs[0], fv00 , slope00_u * bu[0] , slope00_s * bs[0]);
                //}
                assert(fabs(intercept00 + slope00_u * bu[0] + slope00_s * bs[0] - fv00 ) <= 1e-6);
                assert(fabs(intercept00 + slope00_u * bu[1] + slope00_s * bs[0] - fv10 ) <= 1e-6);
                assert(fabs(intercept00 + slope00_u * bu[0] + slope00_s * bs[1] - fv01 ) <= 1e-6);
                assert(intercept00 + slope00_u * bu[1] + slope00_s * bs[1] - fv11  <= 1e-6);
                assert(rightval00 - pow(rightval, 1- exponant) * pow(val, exponant)  <= 1e-6);
            }

            // 11: ub, rightub
            SCIP_Real intercept11 = 0;
            SCIP_Real slope11_s = 0, slope11_u = 0;     
            slope11_u = -(fv01 - fv11) / d1;
            slope11_s = -(fv10 - fv11) / d2;
            intercept11 = fv11 + slope11_u * (-bu[1]) +  slope11_s * (-bs[1]);
            // F00(us)
            SCIP_Real rightval11 = intercept11 + slope11_u * val + slope11_s * rightval;
            if(debug_envelope){
                assert(intercept11 + slope11_u * bu[0] + slope11_s * bs[0] - fv00  <= 1e-6);
                assert(fabs(intercept11 + slope11_u * bu[1] + slope11_s * bs[0] - fv10 ) <= 1e-6);
                assert(fabs(intercept11 + slope11_u * bu[0] + slope11_s * bs[1] - fv01 ) <= 1e-6);
                assert(fabs(intercept11 + slope11_u * bu[1] + slope11_s * bs[1] - fv11 ) <= 1e-6);
                assert(rightval00 - pow(rightval, 1- exponant) * pow(val, exponant)  <= 1e-6);
            }

            // find argmax
            if(rightval00 < rightval11){
                intercept = intercept11;
                slope_s =  slope11_s;
                slope_u =  slope11_u;
                rightval = rightval11;
            }
            else{
                intercept = intercept00;
                slope_s =  slope00_s;
                slope_u =  slope00_u;
                rightval = rightval00;
            }

            // update previous linearization
            constant *= slope_s;
            constant += intercept;
            for(auto & coeff:  coefficient){
                coeff.second *= slope_s;
            }            
            coefficient[var] = slope_u;
            // evaluate new lower bound on next s
            rightlb = pow(rightlb, 1- exponant) * pow(lb, exponant);
            rightub = pow(rightub, 1- exponant) * pow(ub, exponant);
            // evluate s^{1-\zeta} u^{\zeta}
            rightrealval = pow(rightrealval, 1- exponant) * pow(val, exponant);
        }
        // in linear part, s \ubderline{g}(x/s) = s (slope*(x/s) + intercept) = slope * x + intercept*s;
        //SCIP_Real slope = (pow(ub, exponant) - pow(lb, exponant)) / (ub - lb); // linearize x^p
        //SCIP_Real slope = ((pow(1, exponant) - pow(lb/ub, exponant))) * () / (ub - lb);
        // construct a under estimator of s^(1-p) x^p
    } 

    for(auto &coeff: coefficient){
        coeff.second = -coeff.second;
        //SCIPdebugMessage("%f\n", coeff.second);
    }
    //SCIPdebugMessage("%f\n", constant * (count >= 10 ? 1: 1));
    constant = -constant; 

    SCIP_Real leftval = 1; // x_1^{p_1} ... x_n^{p_n}
    SCIP_Real sumeexponant = 0;
    for(auto & sidepowterm: leftconcavepowterms){
        auto var = sidepowterm.var;
        SCIP_Real val = SCIPvarGetLPSol(var);
        leftval *= pow(val, sidepowterm.exponent);
        sumeexponant += sidepowterm.exponent;
    }   

    constant += leftval * (1-sumeexponant);
    // gradient_i = p_i x_1^{p_1} ..x_i^{p_i-1}.. x_n^{p_n}=  p_i x_1^{p_1} ..x_i^{p_i}.. x_n^{p_n} /x_i
    for(int i = 0; i < leftconcavepowterms.size(); i++){
        auto var = leftconcavepowterms[i].var;
        SCIP_Real val = SCIPvarGetLPSol(var);
        coefficient[var] = leftconcavepowterms[i].exponent * leftval / val; // sidepowterms[i].exponent * pow(vars_val[sidepowterms[i].var], sidepowterms[i].exponent - 1);
    }

    //SCIPdebugMessage("%s %f %f %f\n", SCIPisFeasLT(scip, leftval, rightval) ? "cut" : "non",rightval, rightrealval, leftval - rightval);
    if(SCIPisFeasLT(scip, leftval, rightval)){
        return TRUE;
    }
    else{
        return FALSE;
    }

}

