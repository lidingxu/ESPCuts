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

/**@file   sepa_intermis.c
 * @brief  signomial term separator for y_k = x^{\alpha_k}
 * @author Liding Xu
 *
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __SCIP_SEPA_SIGNOMIAL_H__
#define __SCIP_SEPA_SIGNOMIAL_H__


#include "objscip/objscip.h"
#include <unordered_map>
#include "term_signomial.h"
using namespace scip;

struct SCIP_SepaData {
   vector<SIGNOM_TERM>   signomterms;           /**< variables of signomial terms; each signomial term is stored in a SIGNOM_TERM data strcuture*/
   int                   maxrounds;             /**< maximal number of separation rounds per node (-1: unlimited) */
   int                   maxroundsroot;         /**< maximal number of separation rounds in the root node (-1: unlimited) */
   SCIP_Bool             detectedsignomterms;   /**< has signomial terms detection be called? */
   SCIP_Real             mincutviol;            /**< minimum required violation of a cut */
	int                   BINSEARCH_MAXITERS= 500; /**< default iteration limit for binary search */
   SCIP_Bool             inter_cut;             /*<  intersection cut mode, 0: not use, 1: use */
   int                   outer_cut;             /**< outer approximation cut mode, 0: not use, 1: supermodular cut, 2: lift-convexify-project (lcp) cut */
};

/** C++ constraint handler for  constraints */
class SepaSignomial : public ObjSepa
{
public:
	/** default constructor */
	SepaSignomial(
		SCIP* scip /**< SCIP data structure */
	)
		: ObjSepa(scip, /**< SCIP data structure */
			"sepa_signomial", /**< 	name of cut separator  */
			"separator for a signomial term", /**< desc	description of cut separator */
			100000,	/**< priority	priority of the cut separator */
   		1,	/** freq	frequency for calling separator  */
			1.0,	/**< maxbounddist	maximal relative distance from current node's dual bound to primal bound compared to best node's dual bound for applying separation */
			FALSE,	/**< usessubscip	does the separator use a secondary SCIP instance? */
			FALSE	/**< delay	should separator be delayed, if other separators found cuts? */)
	{
	}

	SCIP_SepaData sepadata;


	virtual SCIP_DECL_SEPAEXECLP(scip_execlp);

	virtual SCIP_DECL_SEPAEXITSOL(scip_exitsol);

	virtual SCIP_DECL_SEPAINITSOL(scip_initsol);

	virtual SCIP_DECL_SEPAINIT(scip_init);

	virtual SCIP_DECL_SEPAEXIT(scip_exit);

	virtual SCIP_DECL_SEPACOPY(scip_copy);

	virtual SCIP_DECL_SEPAFREE(scip_free);



}; /*lint !e1712*/



#endif