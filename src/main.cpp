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
/*  along with SCIP; see the file COPYING. If not visit scipopt.org.         */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file   main.c
 * @brief  Main file for branch-and-cut mixed integer signomial solver
 * @author Liding Xu
 */

#include "scip/scip.h"
#include "scip/scipshell.h"
#include "scip/scipdefplugins.h"

#include "sepa_signomial.h"

/** creates a SCIP instance with default plugins, evaluates command line parameters, runs SCIP appropriately,
 *  and frees the SCIP instance
 */
static
SCIP_RETCODE runShell(
   int                   argc,               /**< number of shell parameters */
   char**                argv,               /**< array with shell parameters */
   const char*           defaultsetname      /**< name of default settings file */
   )
{
   SCIP* scip = NULL;

   /*********
    * Setup *
    *********/

   /* initialize SCIP */
   SCIP_CALL( SCIPcreate(&scip) );
   
   /* we explicitly enable the use of a debug solution for this main SCIP instance */
   SCIPenableDebugSol(scip);

   /* include default SCIP plugins */
   SCIP_CALL( SCIPincludeDefaultPlugins(scip) );

   /* include intersection cut separator for mixed intefer signomial term */
   SCIP_CALL( SCIPincludeObjSepa(scip, new SepaSignomial(scip), TRUE) );


   /* parameter setting */
   //SCIP_CALL(SCIPsetRealParam(scip, "limits/gap", 1e-4));
   //SCIP_CALL(SCIPsetRealParam(scip, "limits/absgap", 1e-6));
   //SCIP_CALL(SCIPsetLongintParam(scip, "limits/nodes", 1));
   //SCIP_CALL(SCIPsetIntParam(scip, "timing/clocktype", 1));
   
   SCIP_CALL( SCIPaddBoolParam(scip,
         "separating/sepa_signomial/inter_cut",
         "intersection cut mode, FALSE: not use, TRUE: use",
          NULL, FALSE, FALSE, NULL,  NULL) );
   
   SCIP_CALL( SCIPaddIntParam(scip,
         "separating/sepa_signomial/outer_cut",
         "outer approximation cut mode, 0: not use, 1: supermodular cut, 2: lift-convexify-project (lcp) cut",
         NULL, FALSE, 0, 0, 2, NULL, NULL) );

   SCIP_CALL( SCIPaddRealParam(scip,
         "separating/sepa_signomial/mincutviol",
         "minimum required violation of a cut",
         NULL, FALSE, 1e-4, 0.0, SCIP_REAL_MAX, NULL, NULL) );

   SCIP_CALL( SCIPaddIntParam(scip,
         "separating/sepa_signomial/maxrounds",
         "maximal number of separation rounds per node (-1: unlimited)",
         NULL, FALSE, 10, -1, INT_MAX, NULL, NULL) );

   SCIP_CALL( SCIPaddIntParam(scip,
         "separating/sepa_signomial/maxroundsroot",
         "maximal number of separation rounds in the root node (-1: unlimited)",
         NULL, FALSE, 500, -1, INT_MAX, NULL, NULL) );


   /**********************************
    * Process command line arguments *
    **********************************/
   SCIP_CALL( SCIPprocessShellArguments(scip, argc, argv, defaultsetname) );

   /********************
    * Deinitialization *
    ********************/

   SCIP_CALL( SCIPfree(&scip) );

   BMScheckEmptyMemory();

   return SCIP_OKAY;
}

int
main(
   int                        argc,
   char**                     argv
   )
{
   SCIP_RETCODE retcode;

   retcode = runShell(argc, argv, "scip.set");
   if( retcode != SCIP_OKAY )
   {
      SCIPprintError(retcode);
      return -1;
   }

   return 0;
}

