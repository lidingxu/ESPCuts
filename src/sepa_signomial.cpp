/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the program and library             */
/*         SCIP --- Solving Constraint Integer Programs                      */
/*                                                                           */
/*    Copyright (C) 2002-2020 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SCIP is distributed under the terms of the ZIB Academic License.         */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SCIP; see the file COPYING. If not visit scip.zib.de.         */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file   sepa_signomial.c
 * @brief  signomial term separator for y_k = x^{\alpha_k}
 * @author Liding Xu
 *
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/
#define SCIP_DEBUG
#include <assert.h>
#include <string.h>

#include "sepa_signomial.h"
#include "scip/expr.h"
#include "scip/expr_var.h"
#include "scip/expr_pow.h"
#include "scip/expr_product.h"
#include "scip/expr_log.h"
#include "scip/expr_exp.h"
#include "scip/expr_abs.h"
#include "scip/expr_entropy.h"
#include "scip/expr_trig.h"
#include "scip/pub_misc_rowprep.h"

#include "scip/cons_nonlinear.h"
#include <map>







/**
 * helper method to add an signomial term into global signomial terms
 * 
 */
static 
SCIP_RETCODE addSignomGlobal(
   SCIP* scip,
   SCIP_VAR* var,
   SCIP_Real & expandcoefficient,
   list<POWER_TERM> & expandpowterms,
   list<tuple<SCIP_VAR *, SCIP_Real, list<POWER_TERM>>> & globalsignomterms
){
   //SCIPdebugMessage("try to record signomial term");
   //for(auto & powterm: expandpowterms){
   //   SCIPdebugMessage("%s^%f ",  SCIPvarGetName(powterm.var), powterm.exponent);
   //}
   //SCIPdebugMessage(" %s, %f \n", SCIPvarGetName(var), expandcoefficient);
   SCIP_Bool isfind = FALSE;
   for(auto & signomterm:globalsignomterms){
      auto & powterms = get<2>(signomterm);
      if(powterms.size() == expandpowterms.size()){
         auto iter = powterms.begin();
         auto iterexpand = expandpowterms.begin();
         SCIP_Bool stillsame = TRUE;
         while(stillsame){
            if (iterexpand->var !=  iter->var || !SCIPisEQ(scip, iterexpand->exponent,  iter->exponent)){
               stillsame = false;
               break;
            }
            iter++;
            iterexpand++;
         }
         if(stillsame){
            assert(SCIPisEQ(scip, expandcoefficient, get<1>(signomterm)));
            assert(var == get<0>(signomterm));
            isfind = TRUE;
            break;
         }
      }
   }
   if(! isfind){
      globalsignomterms.push_back(make_tuple(var, expandcoefficient, expandpowterms));
   }
   else{
      SCIPdebugMessage(" repeated \n");
   }
   return SCIP_OKAY;
}

/**
 * helper method to add an signomial term into global signomial terms
 * 
 */
static 
SCIP_RETCODE expandExpr(
   SCIP* scip,
   SCIP_EXPR* expr,
   SCIP_Bool insignomial,
   SCIP_Real & expandcoefficient,
   list<POWER_TERM> & expandpowterms,
   list<tuple<SCIP_VAR *, SCIP_Real, list<POWER_TERM>>> & globalsignomterms
);

/**
 * helper method to expand power expr
 */
static
SCIP_RETCODE expandPowExpr(
   SCIP* scip,
   SCIP_EXPR* expr,
   SCIP_Bool insignomial,
   SCIP_Real & expandcoefficient,
   list<POWER_TERM> & expandpowterms,
   list<tuple<SCIP_VAR *, SCIP_Real, list<POWER_TERM>>> & globalsignomterms
){
   SCIP_EXPR** children = SCIPexprGetChildren(expr);
   SCIP_Real exponentExprPow = SCIPgetExponentExprPow(expr);
   SCIP_EXPR* childexpr = children[0]; 
   SCIP_CALL(expandExpr(scip, childexpr, insignomial, expandcoefficient, expandpowterms, globalsignomterms));
   expandcoefficient = pow(expandcoefficient, exponentExprPow);
   for(auto & powterm: expandpowterms){
         powterm.exponent = powterm.exponent * exponentExprPow;
   }
   return SCIP_OKAY;
}

/**
 * helper method to expand product expr
 */
static
SCIP_RETCODE expandProdExpr(
   SCIP* scip,
   SCIP_EXPR* expr,
   SCIP_Bool insignomial,
   SCIP_Real & expandcoefficient,
   list<POWER_TERM> & expandpowterms,
   list<tuple<SCIP_VAR *, SCIP_Real, list<POWER_TERM>>> & globalsignomterms
){
   SCIP_EXPR** children = SCIPexprGetChildren(expr);
   int nchildren = SCIPexprGetNChildren(expr);
   for(int child_id = 0; child_id < nchildren; child_id++){
      /* count iter once and get the child expr */
      SCIP_EXPR* childexpr = children[child_id]; 
      SCIP_Real expandcoefficient_ = 1;
      list<POWER_TERM> expandpowterms_;
      SCIP_CALL(expandExpr(scip, childexpr, insignomial, expandcoefficient_, expandpowterms_, globalsignomterms));
      //SCIPdebugMessage("\n");
      //SCIPprintExpr(scip, childexpr, NULL);
      //SCIPdebugMessage("\n");
      if(expandpowterms_.size()==0){
         continue;
      }
      expandcoefficient *= expandcoefficient_;
      //assert(expandpowterms_.size() > 0);
      // match or add to keep the expandpowterms in increasing order
      for(auto & powterm_: expandpowterms_){
         auto var_ = powterm_.var;
         auto exponent_ = powterm_.exponent;
         // add when empty
         if(expandpowterms.empty()){
            expandpowterms.push_back(powterm_);
            continue;
         }
         // add to head
         if(var_ < expandpowterms.begin()->var){
            expandpowterms.insert(expandpowterms.begin(), powterm_);
            continue;
         }
         for(auto iter = expandpowterms.begin(); iter != expandpowterms.end(); iter++){
            // matched
            if(var_ == iter->var){
               iter->exponent += exponent_;
               break;
            }
            // add
            auto nextiter = next(iter);
            if(var_ > iter->var && ( nextiter == expandpowterms.end() || var_ < nextiter->var)){
               expandpowterms.insert(nextiter, powterm_);
               break;
            }
         }
      }
   }
   //assert(expandpowterms.size() > 0);
   return SCIP_OKAY;
}

/** helper method to expand an expression of a signomial term recursively, the expression to expand is expr.
 *  If the return value is true, then after expanded, the expression will be stored in expandcoefficients and expandpowterms as: expandcoefficient * \prod_{j \in J} x_j^{p_j}
 */
static 
SCIP_RETCODE expandExpr(
   SCIP* scip,
   SCIP_EXPR* expr,
   SCIP_Bool insignomial,
   SCIP_Real & expandcoefficient,
   list<POWER_TERM> & expandpowterms,
   list<tuple<SCIP_VAR *, SCIP_Real, list<POWER_TERM>>> & globalsignomterms
){

   SCIP_EXPR** children = SCIPexprGetChildren(expr);
   int nchildren = SCIPexprGetNChildren(expr);
   SCIP_Bool is_power =  SCIPisExprPower(scip, expr);
   SCIP_Bool is_product = SCIPisExprProduct(scip, expr);
   SCIP_Bool is_value = SCIPisExprValue(scip, expr);
   SCIP_Bool is_var = SCIPisExprVar(scip, expr);
   SCIP_Bool is_sum = SCIPisExprSum(scip, expr);
   SCIP_Bool is_uninonlinear = SCIPisExprSignpower(scip, expr) ||  SCIPisExprLog(scip, expr) || SCIPisExprExp(scip, expr) || SCIPisExprSin(scip, expr) || SCIPisExprCos(scip, expr) || SCIPisExprEntropy(scip, expr); 
   //SCIPdebugMessage("%d %s\n", nchildren, SCIPvarGetName(SCIPgetExprAuxVarNonlinear(expr)));
   //SCIPprintExpr(scip, expr, NULL);
   //for(int i = 0; i < nchildren; i++){
   //   SCIPprintExpr(scip, children[i], NULL);
   //}
   //SCIPdebugMessage("\n");
   /* expr = x^{p}*/

   if(is_value){
      //SCIPdebugMessage("1\n");
      if(insignomial){  // finish current expansion
         expandcoefficient *= SCIPgetValueExprValue(expr);
      }
   }
   else if(is_var){
      //SCIPdebugMessage("2\n");
      if(insignomial){ // finish current expansion
         POWER_TERM powterm= {.var = SCIPgetVarExprVar(expr), .exponent = 1};
         expandpowterms.push_back(powterm);
      }
   }
   else if(is_sum){
      //SCIPdebugMessage("3\n");
      auto auxvar =  SCIPgetExprAuxVarNonlinear(expr);
      if(insignomial){ // finish current expansion with aurxiliary variable
         //assert(auxvar != NULL);
         if(auxvar != NULL){
            assert(auxvar != NULL);
            POWER_TERM powterm= {.var = auxvar, .exponent = 1};
            expandpowterms.push_back(powterm);
         }
      }
      else{ // maybe need an expansion, go into the childexpr
         for(int child_id = 0; child_id < nchildren; child_id++){
            SCIP_CALL(expandExpr(scip, children[child_id], FALSE, expandcoefficient, expandpowterms, globalsignomterms));
         }
      }
   }
   else if(is_power){
      auto auxvar = SCIPgetExprAuxVarNonlinear(expr);
      if(insignomial){
         SCIP_CALL(expandPowExpr(scip, expr, insignomial, expandcoefficient, expandpowterms, globalsignomterms));
      }
      else if(auxvar != NULL){
         // start a new signomial term
         //SCIPdebugMessage("%d \n", nchildren);
         //SCIPprintExpr(scip, expr, NULL);
         //SCIPdebugMessage("%d \n", nchildren);
         assert(auxvar != NULL);
         SCIP_Real expandcoefficient_new = 1;
         list<POWER_TERM> expandpowterms_new; 
         SCIP_CALL(expandPowExpr(scip, expr, TRUE, expandcoefficient_new, expandpowterms_new, globalsignomterms));
         SCIP_CALL(addSignomGlobal(scip, auxvar, expandcoefficient_new, expandpowterms_new, globalsignomterms));
      }     
   }
   /* expr = \prod_{j in J} x_j  */
   else if(is_product){
      auto auxvar =  SCIPgetExprAuxVarNonlinear(expr);
      if(insignomial){
         SCIP_CALL(expandProdExpr(scip, expr, insignomial, expandcoefficient, expandpowterms, globalsignomterms));
         //SCIPdebugMessage("\n %d %s \n", int(expandpowterms.size()), SCIPvarGetName(auxvar));
         //SCIPprintExpr(scip, expr, NULL);
         //SCIPdebugMessage("\n %d \n", int(expandpowterms.size()));
         assert(expandpowterms.size() > 0);
      }
      else if(auxvar != NULL){
         // start a new signomial term
         assert(auxvar != NULL);
         SCIP_Real expandcoefficient_new = 1;
         list<POWER_TERM> expandpowterms_new;    
         SCIP_CALL(expandProdExpr(scip, expr, TRUE, expandcoefficient_new, expandpowterms_new, globalsignomterms));
         SCIP_CALL(addSignomGlobal(scip, auxvar, expandcoefficient_new, expandpowterms_new, globalsignomterms));
      }
   }
   else{
      //SCIPdebugMessage("3\n");
      auto auxvar =  SCIPgetExprAuxVarNonlinear(expr);
      if(insignomial){ // finish current expansion with aurxiliary variable
         if(auxvar != NULL){
            POWER_TERM powterm= {.var = auxvar, .exponent = 1};
            expandpowterms.push_back(powterm);
         }
      }
      else{ // maybe need an expansion, go into the childexpr
         for(int child_id = 0; child_id < nchildren; child_id++){
            SCIP_CALL(expandExpr(scip, children[child_id], FALSE, expandcoefficient, expandpowterms, globalsignomterms));
         }         
      }
   }
   return SCIP_OKAY;
}

/** method to detect and store signomial terms */
static
SCIP_RETCODE detectSignomterms(
   SCIP*                 scip,               /**< SCIP data structure */
   SCIP_SEPADATA*        sepadata            /**< separator data */
   )
{
   SCIP_CONSHDLR* conshdlr;
   SCIP_EXPRITER* it;
   int c;
   int i;
   int nterms;

#ifdef SCIP_STATISTIC
   SCIP_Real totaltime = -SCIPgetTotalTime(scip);
#endif

   assert(sepadata != NULL);

   /* check whether signomial detection has been called already */
   if( sepadata->detectedsignomterms )
      return SCIP_OKAY;

   assert(sepadata->signomterms.size() == 0);

   /* we assume that the auxiliary variables in the nonlinear constraint handler have been already generated */
   sepadata->detectedsignomterms = TRUE;

   /* check whether there are nonlinear constraints available */
   conshdlr = SCIPfindConshdlr(scip, "nonlinear");
   if( conshdlr == NULL || SCIPconshdlrGetNConss(conshdlr) == 0 )
      return SCIP_OKAY;

   //SCIPdebugMsg(scip, "call detectSignomterms()\n");


   nterms = 0;

   list<tuple<SCIP_VAR *, SCIP_Real, list<POWER_TERM>>> globalsignomterms; 

   //SCIPdebugMessage("%d\n", SCIPconshdlrGetNConss(conshdlr));
   for( c = 0; c < SCIPconshdlrGetNConss(conshdlr); ++c )
   {
      SCIP_CONS* cons;
      SCIP_EXPR* root;


      cons = SCIPconshdlrGetConss(conshdlr)[c];
      assert(cons != NULL);
      root = SCIPgetExprNonlinear(cons);
      assert(root != NULL);


      //SCIPdebugMsg(scip,"\n");
      //SCIPprintExpr(scip, root, NULL);
      //SCIPdebugMsg(scip,"\n");
      SCIP_Real expandcoefficient = 1;
      list<POWER_TERM> expandpowterms; 
      SCIP_CALL(expandExpr(scip, root, FALSE, expandcoefficient, expandpowterms, globalsignomterms));
   }

   /* store signomial terms */
   for(auto & signomterm: globalsignomterms)
   {
      auto liftvar = get<0>(signomterm);
      auto powterms = get<2>(signomterm);
      assert(liftvar != NULL);
      // x^1 is typed as a power term
      if(int(powterms.size()) == 0){
         continue;
      }
      // x^1 is typed as a product term
      else if(int(powterms.size()) == 1 && SCIPisFeasEQ(scip, powterms.begin()->exponent,1)) {
         continue;
      }
      // to do: bilinear term y_12 = x^1 x^2, does y_12 exists?
      //printf("%d\n", int(powterms.size()));
      sepadata->signomterms.push_back(SIGNOM_TERM(scip, liftvar, powterms));
      //printf("%d\n", int(powterms.size()));
      //sepadata->signomterms.back().printSignomTerm(scip);
   }

   //SCIPdebugMessage("%d\n", int(globalsignomterms.size()));
   //SCIPABORT();

#ifdef SCIP_STATISTIC
   totaltime += SCIPgetTotalTime(scip);
   SCIPstatisticMessage("MINOR DETECT %s %f %d %d\n", SCIPgetProbName(scip), totaltime, sepadata->nminors, maxminors);
#endif

   return SCIP_OKAY;
}


/** constructs map between lp position of a basic variable and its row in the tableau,
 * A x + I s = 0, and A_b x_b + I_b s_b + A_n x_n + I_n s_n = 0.
*/
static
SCIP_RETCODE constructBasicVars2TableauRowMap(
   SCIP*                 scip,               /**< SCIP data structure */
   int*                  map                 /**< buffer to store the map */
   )
{
   int* basisind;
   int nrows;
   int i;

   nrows = SCIPgetNLPRows(scip);
   SCIP_CALL( SCIPallocBufferArray(scip, &basisind, nrows) );

   SCIP_CALL( SCIPgetLPBasisInd(scip, basisind) );
   for( i = 0; i < nrows; ++i )
   {
      if( basisind[i] >= 0 )
         map[basisind[i]] = i;
   }

   SCIPfreeBufferArray(scip, &basisind);

   return SCIP_OKAY;
}


/** get the tableau rows of the variables in vars,
 * A x + I s = 0, and A_b x_b + I_b s_b + A_n x_n + I_n s_n = 0. B = [A_b, I_b]
 * B^{-1} (Ax + Is) = 0,  x_b +  B^{-1}A_n x_n + s_b + B^{-1} I_n s_n = 0.
 */
static
SCIP_RETCODE getTableauRows(
   SCIP*       scip,               /**< SCIP data structure */
   list<SCIP_VAR *>  &    vars,       /**< signomial term */
   int * basicvarpos2tableaurow,  /**< map between basic var and its tableau row */
   map<SCIP_VAR*, SCIP_Real*> & tableau,     /**< map between all var and its tableau row */
   map<SCIP_VAR*, SCIP_Real*> & tableaurows,    /**< buffer to store tableau row associated with signomial vars */
   SCIP_Bool*     success             /**< set to TRUE if no variable had basisstat = ZERO */
   )
{

   *success = TRUE;

   int nrows = SCIPgetNLPRows(scip);
   int ncols = SCIPgetNLPCols(scip);

   /* check if we have the tableau row of the variable and if not compute it */
   for(auto var: vars)
   {
      if( tableau.find(var) == tableau.end())
      {
         /* get column of variable */
         SCIP_COL* col = SCIPvarGetCol(var);

         /* if variable is basic, then get its tableau row and insert it in the hashmap */
         if( SCIPcolGetBasisStatus(col) == SCIP_BASESTAT_BASIC )
         {
            int lppos = SCIPcolGetLPPos(col);
            SCIP_Real* densetableaurow;
            SCIP_CALL( SCIPallocBufferArray(scip, &densetableaurow, ncols + nrows));

            SCIP_CALL( SCIPgetLPBInvRow(scip, basicvarpos2tableaurow[lppos], &densetableaurow[ncols], NULL, NULL) );
            SCIP_CALL( SCIPgetLPBInvARow(scip, basicvarpos2tableaurow[lppos], &densetableaurow[ncols], densetableaurow, NULL, NULL) );

            /* insert tableau row in hashmap*/
            tableau[var] = densetableaurow;
         }
         else if( SCIPcolGetBasisStatus(col) == SCIP_BASESTAT_ZERO)
         {
            *success = FALSE;
            return SCIP_OKAY; /* don't even bother */
         }
         else
         {
            tableau[var] = (SCIP_Real *)NULL;
         }
      }
      /* get tableau row of var */
      tableaurows[var] = tableau[var];
   }
   return SCIP_OKAY;
}

/** adds cutcoef * (col - col*) to rowprep */
static
SCIP_RETCODE addColToCut(
   SCIP*                 scip,               /**< SCIP data structure */
   SCIP_ROWPREP*         rowprep,            /**< rowprep to store intersection cut */
   SCIP_Real             cutcoef,            /**< cut coefficient */
   SCIP_COL*             col                 /**< column to add to rowprep */
   )
{
   assert(col != NULL);

#ifdef DEBUG_INTERCUTS_NUMERICS
   SCIPinfoMessage(scip, NULL, "adding col %s to cut. %g <= col <= %g\n", SCIPvarGetName(SCIPcolGetVar(col)),
      SCIPvarGetLbLocal(SCIPcolGetVar(col)), SCIPvarGetUbLocal(SCIPcolGetVar(col)));
   SCIPinfoMessage(scip, NULL, "col is active at %s. Value %.15f\n", SCIPcolGetBasisStatus(col) == SCIP_BASESTAT_LOWER ? "lower bound" :
      "upper bound" , SCIPcolGetPrimsol(col));
#endif

   SCIP_CALL( SCIPaddRowprepTerm(scip, rowprep, SCIPcolGetVar(col), cutcoef) );
   SCIProwprepAddConstant(rowprep, -cutcoef * SCIPcolGetPrimsol(col) );

   return SCIP_OKAY;
}

/** The maximal S-free set is gamma(z) <= 0; we find the intersection point of the ray `ray` starting from zlp with the
 * boundary of the S-free set.
 * That is, we find t >= 0 such that gamma(zlp + t * ray) = 0 and zlp+t*ray >= 0.
 */
static
SCIP_Real computeIntersectionPoint(
   SCIP*                 scip,               /**< SCIP data structure */
   SCIP_SEPADATA*        sepadata,           /**< separator data */
   map<SCIP_VAR*, SCIP_Real> & ray,    /**< iterator of ray */
   SIGNOM_TERM  &        signom,             /**< signomial term */
   SCIP_Bool*            success             /**< pointer to store whether the generation of cutcoefs was successful */
   )
{
   // to do binary search;
   //SCIPdebugMessage("bin search\n");
   SCIP_Real lb = 0.0;
   SCIP_Real ub = signom.uppert(scip, ray);
   SCIP_Real curr;

   //SCIPdebugMessage("bin search %f %f\n", ub, signom.evalRay(scip, ray, 0));
   for(int i = 0; i < sepadata->BINSEARCH_MAXITERS; ++i )
   {

      SCIP_Real t = (lb + ub) / 2.0;
      SCIP_Real gamma_t =  signom.evalRay(scip, ray, t); // we assume signom.evalRay(scip, ray, 0) > 0
      //SCIPdebugMessage("bin search_ %d %f %f in %f %f\n", i, t, gamma_t, lb, ub);
#ifdef INTERCUT_MOREDEBUG
      printf("%d: lb,ub %.10f, %.10f. curr = %g -> phi at curr %g -> phi at lb %g \n", i, lb, ub, curr, phival, evalPhiAtRay(scip, lb, a, b, c, d, e));
#endif

      if( gamma_t >= 0.0 )
      {
         lb = t;
         if( SCIPisFeasZero(scip, gamma_t) || SCIPisFeasEQ(scip, ub, lb) )
            {  
               *success = TRUE;
               //SCIPdebugMessage("%d\n", i);
               break;
            }
      }
      else
         ub = t;
   }

   return lb;
}

/** computes the cut coefs of the  non-basic (non-slack) variables (correspond to cols) and adds them to the
 * A x + I s = 0, and A_b x_b + I_b s_b + A_n x_n + I_n s_n = 0. B = [A_b, I_b]
 * B^{-1} (Ax + Is) = 0,  x_b +  B^{-1}A_n x_n + s_b + B^{-1} I_n s_n = 0.
 */
static
SCIP_RETCODE addCols(
   SCIP*                 scip,               /**< SCIP data structure */
   SCIP_SEPADATA*        sepadata,           /**< separator data */
   SIGNOM_TERM  &        signom,               /**< signomial term */
   map<SCIP_VAR*, SCIP_Real*> & tableaurows, /**< tableau rows corresponding to the variables in vars */
   SCIP_ROWPREP*         rowprep,            /**< store cut */
   SCIP_Bool*            success             /**< pointer to store whether the generation of cutcoefs was successful */
   )
{
   //SCIPdebugMessage("add col %d\n", int(tableaurows.size()));
   *success = TRUE;

   int nrays = 0;

   /* loop over non-basic (non-slack) variables */
   SCIP_COL** cols = SCIPgetLPCols(scip);
   int ncols = SCIPgetNLPCols(scip);
   int sigdim = signom.getSize();
   for(int i = 0; i < ncols; ++i )
   {

      SCIP_COL* col = cols[i];

      SCIP_Real factor;
      /* set factor to store entries of ray as = [-BinvL, BinvU] */
      if( SCIPcolGetBasisStatus(col) == SCIP_BASESTAT_LOWER )
         factor = -1.0;
      else if( SCIPcolGetBasisStatus(col) == SCIP_BASESTAT_UPPER )
         factor = 1.0;
      else if( SCIPcolGetBasisStatus(col) == SCIP_BASESTAT_ZERO )
      {
         *success = FALSE;
         return SCIP_OKAY;
      }
      else
         continue;

      /* build the ray */
      SCIP_Bool israynonzero = FALSE;
      map<SCIP_VAR*,SCIP_Real> raysbycol;
      for(auto var: signom.getVars())
      {
         //SCIPdebugMessage("add col 2.1 %d %d\n",  int(tableaurows.find(var) != tableaurows.end()), int(tableaurows[var] != NULL));
         if( tableaurows.find(var) != tableaurows.end() && tableaurows[var] != NULL )
         {
            //SCIPdebugMessage("add col 2.11\n");
            raysbycol[var] = factor * ( SCIPisZero(scip, tableaurows[var][i]) ? 0.0 : tableaurows[var][i] );
            //SCIPdebugMessage("add col 2.12\n");
         }
         else
         {
            //SCIPdebugMessage("add col 2.2\n");
            if( col == SCIPvarGetCol(var) )
               raysbycol[var]= (-factor);
            else
               raysbycol[var]=(0.0);
         }
         //SCIPdebugMessage("%f\n", raysbycol[var]);
         israynonzero = israynonzero || (raysbycol[var] != 0.0);
      }

      //SCIPdebugMessage("add col 3 %d\n", int(israynonzero));
      /* do nothing if ray is 0 */
      if( ! israynonzero )
         continue;

      //SCIPdebugMessage("add col 3\n");
      

      /* compute intersection point */
      SCIP_Real interpoint = computeIntersectionPoint(scip, sepadata, raysbycol, signom, success);


      if(SCIPisZero(scip, interpoint)){
         *success = FALSE;
         break;
      }

      //SCIPdebugMessage("add col 4\n");

      if( *success == FALSE )
         return SCIP_OKAY;

      /* count nonzero rays */
      nrays += 1;

      /* compute cut coef */
      SCIP_Real cutcoef = SCIPisInfinity(scip, interpoint) ? 0.0 : 1.0 / interpoint;

      /* add var to cut: if variable is nonbasic at upper we have to flip sign of cutcoef */
      assert(SCIPcolGetBasisStatus(col) == SCIP_BASESTAT_UPPER || SCIPcolGetBasisStatus(col) == SCIP_BASESTAT_LOWER);
      SCIP_CALL( addColToCut(scip, rowprep, SCIPcolGetBasisStatus(col) == SCIP_BASESTAT_UPPER ? -cutcoef :
            cutcoef, col) );
   }
   //SCIPdebugMessage("add col__ nray:%d\n", nrays);
   //abort();
   return SCIP_OKAY;
}



/** adds cutcoef * (slack - slack*) to rowprep
  *
  * row is lhs <= <coefs, vars> + constant <= rhs, thus slack is defined by
  * slack + <coefs, vars> + constant = side
  * If row (slack) is at upper, it means that <coefs,vars*> + constant = rhs, and so
  * slack* = side - rhs --> slack - slack* = rhs - <coefs, vars> - constant.
  * If row (slack) is at lower, then <coefs,vars*> + constant = lhs, and so
  * slack* = side - lhs --> slack - slack* = lhs - <coefs, vars> - constant.
  */
static
SCIP_RETCODE addRowToCut(
   SCIP*                 scip,               /**< SCIP data structure */
   SCIP_ROWPREP*         rowprep,            /**< rowprep to store intersection cut */
   SCIP_Real             cutcoef,            /**< cut coefficient */
   SCIP_ROW*             row,                /**< row, whose slack we are adding to rowprep */
   SCIP_Bool*            success             /**< buffer to store whether the row is nonbasic enough */
   )
{
   int i;
   SCIP_COL** rowcols;
   SCIP_Real* rowcoefs;
   int nnonz;

   assert(row != NULL);

   rowcols = SCIProwGetCols(row);
   rowcoefs = SCIProwGetVals(row);
   nnonz = SCIProwGetNLPNonz(row);

#ifdef DEBUG_INTERCUTS_NUMERICS
   SCIPinfoMessage(scip, NULL, "adding slack var row_%d to cut. %g <= row <= %g\n", SCIProwGetLPPos(row), SCIProwGetLhs(row), SCIProwGetRhs(row));
   SCIPinfoMessage(scip, NULL, "row is active at %s = %.15f Activity %.15f\n", SCIProwGetBasisStatus(row) == SCIP_BASESTAT_LOWER ? "lhs" :
   "rhs" , SCIProwGetBasisStatus(row) == SCIP_BASESTAT_LOWER ? SCIProwGetLhs(row) : SCIProwGetRhs(row),
   SCIPgetRowActivity(scip, row));
#endif

   if( SCIProwGetBasisStatus(row) == SCIP_BASESTAT_LOWER )
   {
      assert(!SCIPisInfinity(scip, -SCIProwGetLhs(row)));
      if( ! SCIPisFeasEQ(scip, SCIProwGetLhs(row), SCIPgetRowActivity(scip, row)) )
      {
         *success = FALSE;
         return SCIP_OKAY;
      }

      SCIProwprepAddConstant(rowprep, SCIProwGetLhs(row) * cutcoef);
   }
   else
   {
      assert(!SCIPisInfinity(scip, SCIProwGetRhs(row)));
      if( ! SCIPisFeasEQ(scip, SCIProwGetRhs(row), SCIPgetRowActivity(scip, row)) )
      {
         *success = FALSE;
         return SCIP_OKAY;
      }

      SCIProwprepAddConstant(rowprep, SCIProwGetRhs(row) * cutcoef);
   }

   for( i = 0; i < nnonz; i++ )
   {
      SCIP_CALL( SCIPaddRowprepTerm(scip, rowprep, SCIPcolGetVar(rowcols[i]), -rowcoefs[i] * cutcoef) );
   }

   SCIProwprepAddConstant(rowprep, -SCIProwGetConstant(row) * cutcoef);

   return SCIP_OKAY;
}

/** computes the cut coefs of the non-basic slack variables (correspond to rows) and adds them to the
 * A x + I s = 0, and A_b x_b + I_b s_b + A_n x_n + I_n s_n = 0. B = [A_b, I_b]
 * B^{-1} (Ax + Is) = 0,  x_b +  B^{-1}A_n x_n + s_b + B^{-1} I_n s_n = 0. 
 */
static
SCIP_RETCODE addRows(
   SCIP*                 scip,               /**< SCIP data structure */
   SCIP_SEPADATA*        sepadata,           /**< separator data */
   SIGNOM_TERM  &        signom,             /**< signomial term */
   map<SCIP_VAR*, SCIP_Real*> & tableaurows, /**< tableau rows corresponding to the variables in vars */
   SCIP_ROWPREP*         rowprep,            /**< store cut */
   SCIP_Bool*            success             /**< pointer to store whether the generation of cutcoefs was successful */
   )
{
   //SCIPdebugMessage("add row\n");
   *success = TRUE;

   int nrays = 0;

   /* loop over non-basic (slack) variables */
   SCIP_ROW** rows = SCIPgetLPRows(scip);
   int nrows = SCIPgetNLPRows(scip);
   int ncols = SCIPgetNLPCols(scip);
   int sigdim = signom.getSize();
   for(int i = 0; i < nrows; ++i )
   {

      //SCIPdebugMessage("add row 1\n");
      SCIP_ROW* row = rows[i];

      SCIP_Real factor;
      /* set factor to store entries of ray as = [-BinvL, BinvU] */
      if( SCIProwGetBasisStatus(row) == SCIP_BASESTAT_LOWER )
         factor = 1.0;
      else if( SCIProwGetBasisStatus(row) == SCIP_BASESTAT_UPPER )
         factor = -1.0;
      else if( SCIProwGetBasisStatus(row) == SCIP_BASESTAT_ZERO )
      {
         *success = FALSE;
         return SCIP_OKAY;
      }
      else
         continue;

      //SCIPdebugMessage("add row 2\n");
      /* build the ray */
      SCIP_Bool israynonzero = FALSE;
      map<SCIP_VAR*,SCIP_Real> raysbyrow;
      for(auto var: signom.getVars())
      {
         if( tableaurows.find(var) != tableaurows.end() && tableaurows[var] != NULL )
            raysbyrow[var] = factor * ( SCIPisZero(scip, tableaurows[var][ncols + i]) ? 0.0 : tableaurows[var][ncols + i] );
         else
         {
            raysbyrow[var]= 0.0;
         }
         israynonzero = israynonzero || (raysbyrow[var] != 0.0);
      }

      //SCIPdebugMessage("add row 3\n");
      /* do nothing if ray is 0 */
      if( ! israynonzero )
         continue;


      /* compute intersection point */
      
      SCIP_Real interpoint = computeIntersectionPoint(scip, sepadata, raysbyrow, signom, success);


      if(SCIPisZero(scip, interpoint)){
         *success = FALSE;
         break;
      }

  
      if( *success == FALSE )
         return SCIP_OKAY;
         

      //SCIPdebugMessage("add row 4\n");

      /* count nonzero rays */
      nrays += 1;

      /* compute cut coef */
      SCIP_Real cutcoef = SCIPisInfinity(scip, interpoint) ? 0.0 : 1.0 / interpoint;



      /* add var to cut: if variable is nonbasic at upper we have to flip sign of cutcoef */
      assert(SCIProwGetBasisStatus(row) == SCIP_BASESTAT_UPPER || SCIProwGetBasisStatus(row) == SCIP_BASESTAT_LOWER);
      SCIP_CALL( addRowToCut(scip, rowprep, SCIProwGetBasisStatus(row) == SCIP_BASESTAT_UPPER ? cutcoef :
            -cutcoef, row, success) ); /* rows have flipper base status! */
   }

   //SCIPdebugMessage("add row__ nay:%d\n", nrays);
   return SCIP_OKAY;
}

/** separates cuts for stored signomial terms */
static
SCIP_RETCODE separateSignomInter(
   SCIP*                 scip,               /**< SCIP data structure */
   SCIP_SEPA*            sepa,               /**< separator */
   SCIP_SEPADATA*        sepadata,           /**< separator data */
   SIGNOM_TERM &         signomterm,         /**< signomial term */
   int *                 basicvarpos2tableaurow,/**< map from basic var to its tableau row */
   map<SCIP_VAR *, SCIP_Real*> &  tableau,            /**< map from var to its tableau row */
   SCIP_RESULT*          result              /**< pointer to store the result of the separation call */
   )
{
   //SCIPdebugMessage("start sep!\n");
   SCIP_ROWPREP* rowprep;

   int ncols = SCIPgetNLPCols(scip);
   int nrows = SCIPgetNLPRows(scip);

   SCIP_Bool success = TRUE;

   /* cut (in the nonbasic space) is of the form alpha^T x >= 1 */
   SCIP_CALL( SCIPcreateRowprep(scip, &rowprep, SCIP_SIDETYPE_LEFT, TRUE) );
   SCIProwprepAddSide(rowprep, 1.0);

   map<SCIP_VAR *, SCIP_Real*> tableaurows;
   /* check if we have the tableau row of the variable and if not compute it */
   //SCIPdebugMessage("get tableau!\n");
   SCIP_CALL( getTableauRows(scip, signomterm.getVars(), basicvarpos2tableaurow, tableau, tableaurows, &success) );
   //SCIPdebugMessage("get tableau finish!\n");

   SCIP_Bool is_constructed = signomterm.constructSfree(scip);

   if(! success )
      goto CLEANUP;

   //SCIPdebugMessage("S-free construct!\n")
   if(!is_constructed)
      goto CLEANUP;
   //SCIPdebugMessage("S-free construced!\n");


   //SCIPdebugMessage("col to add!\n");

   /* loop over each non-basic var; get the ray; compute cut coefficient */
   SCIP_CALL( addCols(scip, sepadata, signomterm,  tableaurows,rowprep, &success) );

   if( ! success )
      goto CLEANUP;

   /* loop over non-basic slack variables */
   SCIP_CALL( addRows(scip, sepadata, signomterm, tableaurows, rowprep, &success) );

   //SCIPdebugMessage("row added!\n");
   if( ! success )
      goto CLEANUP;

   //SCIPdebugMessage("row added!\n");

   /* merge coefficients that belong to same variable */

   //SCIPprintRowprep( scip,   rowprep,  NULL);
   
   //SCIPdebugMessage("row added0.5!\n");

   SCIPmergeRowprepTerms(scip, rowprep);

   SCIP_CALL( SCIPcleanupRowprep(scip, rowprep, NULL, sepadata->mincutviol, NULL, &success) );


   //SCIPdebugMessage("row added1!\n");
   /* if cleanup was successfull, create row out of rowprep and add it */
   if( success )
   {
      SCIP_ROW* row;
      SCIP_Bool infeasible;

      /* create row */
      SCIP_CALL( SCIPgetRowprepRowSepa(scip, &row, rowprep, sepa) );

      assert(SCIPgetCutEfficacy(scip, NULL, row) > 0.0);

      /* add row */
      SCIP_CALL( SCIPaddRow(scip, row, FALSE, &infeasible) );

      //SCIPdebugMessage("inter\n");
      //SCIPprintRow ( scip,row, NULL ) ;
      //SCIPdebugMessage("inter\n");

      //SCIPdebugMessage("%f %d \n", SCIPgetCutEfficacy(scip, NULL, row), infeasible);
      if( infeasible )
         *result = SCIP_CUTOFF;
      else
         *result = SCIP_SEPARATED;

      SCIP_CALL( SCIPreleaseRow(scip, &row) );
   }

   //SCIPdebugMessage("row added2!\n");
CLEANUP:
   SCIPfreeRowprep(scip, &rowprep);
   //SCIPfreeBuffer(scip, &rayslppos);
   //SCIPfreeBuffer(scip, &rays);
   //SCIPfreeBuffer(scip, &interpoints);

   return SCIP_OKAY;
}


/** separates cuts for stored signomial terms */
static
SCIP_RETCODE separateSignomOuter(
   SCIP*                 scip,               /**< SCIP data structure */
   SCIP_SEPA*            sepa,               /**< separator */
   SCIP_SEPADATA*        sepadata,           /**< separator data */
   SIGNOM_TERM &         signomterm,         /**< signomial term */
   SCIP_RESULT*          result,              /**< pointer to store the result of the separation call */
   SCIP_Bool &           success 
   )
{
   //SCIPdebugMessage("start sep!\n");
   SCIP_ROWPREP* rowprep;
   success = TRUE;

   /* cut (in the nonbasic space) is of the form alpha^T x >= -constant */
   SCIP_CALL( SCIPcreateRowprep(scip, &rowprep, SCIP_SIDETYPE_LEFT, TRUE));

   map<SCIP_VAR *, SCIP_Real> coefficients;
   /* check if we have the tableau row of the variable and if not compute it */
   //SCIPdebugMessage("get tableau!\n");

   SCIP_Real constant = 0;
   success = signomterm.sepouter(scip, coefficients, constant, sepadata->outer_cut);

   SCIP_Real cut = 0;

   if(! success )
      goto CLEANUP;

   //SCIPdebugMessage("S-free construct!\n");
   for(auto & coeff: coefficients){
      SCIP_CALL(SCIPaddRowprepTerm(scip, rowprep, coeff.first, coeff.second));
      cut += SCIPvarGetLPSol(coeff.first) * coeff.second;
      //SCIPdebugMessage("%f\n", coeff.second);
   }
   //SCIPdebugMessage("%f\n", cut + constant);


   SCIProwprepAddSide(rowprep, -constant);



   /* merge coefficients that belong to same variable */
   SCIPmergeRowprepTerms(scip, rowprep);

   SCIP_CALL( SCIPcleanupRowprep(scip, rowprep, NULL, sepadata->mincutviol, NULL, &success) );

   /* if cleanup was successfull, create row out of rowprep and add it */
   if( success )
   {
      SCIP_ROW* row;
      SCIP_Bool infeasible;

      /* create row */
      SCIP_CALL( SCIPgetRowprepRowSepa(scip, &row, rowprep, sepa) );

      assert(SCIPgetCutEfficacy(scip, NULL, row) > 0.0);

      /* add row */
      SCIP_CALL( SCIPaddRow(scip, row, FALSE, &infeasible) );

      //SCIPdebugMessage("mis\n");
      SCIPprintRow ( scip,row, NULL ) ;
      //SCIPdebugMessage("mis\n");

      //SCIPdebugMessage("%f %d \n", SCIPgetCutEfficacy(scip, NULL, row), infeasible);
      if( infeasible )
         *result = SCIP_CUTOFF;
      else
         *result = SCIP_SEPARATED;

      SCIP_CALL( SCIPreleaseRow(scip, &row) );
   }

CLEANUP:
   SCIPfreeRowprep(scip, &rowprep);
   //SCIPfreeBuffer(scip, &rayslppos);
   //SCIPfreeBuffer(scip, &rays);
   //SCIPfreeBuffer(scip, &interpoints);

   return SCIP_OKAY;
}

/** separate cuts for stored signomial */
static
SCIP_RETCODE separatePoint(
   SCIP*                 scip,               /**< SCIP data structure */
   SCIP_SEPA*            sepa,               /**< separator */
   SCIP_SEPADATA*        sepadata,           /**< separator data */
   SCIP_RESULT*          result              /**< pointer to store the result of the separation call */
   )
{
   assert(sepa != NULL);
   assert(result != NULL);
   *result = SCIP_DIDNOTRUN;
   assert(sepadata != NULL);

   /* check whether there are some minors available */
   if( sepadata->signomterms.size() == 0 )
      return SCIP_OKAY;

   *result = SCIP_DIDNOTFIND;

   /* loop over the signomial terms and if they are violated build cut */
   map<SCIP_VAR *, SCIP_Real *> tableau;
   int *  basicvarpos2tableaurow = NULL; /* map between basic var and its tableau row */
   int nviolated = 0;
   //SCIPdebugMessage("good\n");
   for(int i = 0; i < sepadata->signomterms.size() && (*result != SCIP_CUTOFF); ++i )
   {
      //SCIPdebugMessage("good0.5\n");
      auto & signomterm = sepadata->signomterms[i];
      //signomterm.printSignomTerm(scip);
      signomterm.initSep();
      //SCIPdebugMessage("good0.7\n");
      SCIP_Bool isnonnega = signomterm.isNonNeg(scip);
      if(!isnonnega){
         continue;
      }
      //SCIPdebugMessage("good0.8\n");
      SCIP_Bool isviolatedOriginal = signomterm.isviolatedOriginal(scip);
      SCIP_Bool isviolatedTransform = signomterm.isviolatedTransfrom(scip);

      //SCIPdebugMessage("good1\n");

      // separate if both forms are violated
      if( !isviolatedOriginal || !isviolatedTransform )
         continue;

      nviolated++;

      if(sepadata->outer_cut != 0){
         SCIP_Bool success = FALSE;
         //SCIPdebugMessage("1\n");
         SCIP_CALL(separateSignomOuter(scip, sepa, sepadata, signomterm, result, success));
         //SCIPdebugMessage("2\n");
         if(*result == SCIP_CUTOFF){
            SCIPdebugMessage("cut off\n");
         }
         if(success){
            continue;
         }
      }

      //SCIPdebugMessage("good3\n");
      if(sepadata->inter_cut == TRUE){
         if( basicvarpos2tableaurow == NULL )
         {
            /* allocate memory */
            SCIP_CALL( SCIPallocBufferArray(scip, &basicvarpos2tableaurow, SCIPgetNLPCols(scip)) );

            /* construct basicvar to tableau row map */
            SCIP_CALL( constructBasicVars2TableauRowMap(scip, basicvarpos2tableaurow) );
         }
         SCIP_CALL(separateSignomInter(scip, sepa, sepadata, signomterm, basicvarpos2tableaurow, tableau, result));
      }
   }

   for(auto & table: tableau){
      SCIPfreeBufferArrayNull(scip, &table.second);
   }

   /* all minors were feasible, so no memory to free */
   if( basicvarpos2tableaurow == NULL )
      return SCIP_OKAY;
   SCIPfreeBufferArray(scip, &basicvarpos2tableaurow);

   //SCIPdebugMessage("viol/total: %d/%d\n", nviolated, int(sepadata->signomterms.size()));
   //abort();

   return SCIP_OKAY;
}






/*
 * Callback methods of separator
 */

/** copy method for separator plugins (called when SCIP copies plugins) */
SCIP_DECL_SEPACOPY(SepaSignomial::scip_copy)
{  /*lint --e{715}*/
   //SCIPdebugMessage("copy %p\n", scip);
   return SCIP_OKAY;
}


/** destructor of separator to free user data (called when SCIP is exiting) */
SCIP_DECL_SEPAFREE(SepaSignomial::scip_free)
{  /*lint --e{715}*/
   return SCIP_OKAY;
}


/** initialization method of separator (called after problem was transformed) */
SCIP_DECL_SEPAINIT(SepaSignomial::scip_init)
{  /*lint --e{715}*/
   //SCIPdebugMessage("init %p\n", scip);
   /* get separator data */

	SCIP_CALL(SCIPgetRealParam(scip,  "separating/sepa_signomial/mincutviol", &sepadata.mincutviol ));
	SCIP_CALL(SCIPgetIntParam(scip,  "separating/sepa_signomial/maxroundsroot", &sepadata.maxroundsroot ));
   SCIP_CALL(SCIPgetIntParam(scip,  "separating/sepa_signomial/maxrounds", &sepadata.maxrounds ));
   SCIP_CALL(SCIPgetBoolParam(scip,  "separating/sepa_signomial/inter_cut", &sepadata.inter_cut));
   SCIP_CALL(SCIPgetIntParam(scip,  "separating/sepa_signomial/outer_cut", &sepadata.outer_cut));
   sepadata.detectedsignomterms = FALSE;
   return SCIP_OKAY;
}


/** deinitialization method of separator (called before transformed problem is freed) */
SCIP_DECL_SEPAEXIT(SepaSignomial::scip_exit)
{  /*lint --e{715}*/
   return SCIP_OKAY;
}


/** solving process initialization method of separator (called when branch and bound process is about to begin) */
SCIP_DECL_SEPAINITSOL(SepaSignomial::scip_initsol)
{  /*lint --e{715}*/
   return SCIP_OKAY;
}


/** solving process deinitialization method of separator (called before branch and bound process data is freed) */
SCIP_DECL_SEPAEXITSOL(SepaSignomial::scip_exitsol)
{  /*lint --e{715}*/
   return SCIP_OKAY;
}


/** LP solution separation method of separator */
SCIP_DECL_SEPAEXECLP(SepaSignomial::scip_execlp)
{  /*lint --e{715}*/
   int ncalls;
   int currentdepth;

   //SCIPdebugMessage("execl sep\n");
   currentdepth = SCIPgetDepth(scip);
   ncalls = SCIPsepaGetNCallsAtNode(sepa);

   *result = SCIP_DIDNOTRUN;
   /* only call the separator a given number of times at each node */
   if( (currentdepth == 0 && sepadata.maxroundsroot >= 0 && ncalls >= sepadata.maxroundsroot)
      || (currentdepth > 0 && sepadata.maxrounds >= 0 && ncalls >= sepadata.maxrounds) )
   {
      SCIPdebugMsg(scip, "reached round limit for node\n");
      return SCIP_OKAY;
   }
   /* detec signomial */
   SCIP_CALL( detectSignomterms(scip, &sepadata) );

   /* call separation method */
   SCIP_CALL( separatePoint(scip, sepa, &sepadata, result) );

   return SCIP_OKAY;
}