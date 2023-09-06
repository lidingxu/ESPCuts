# Install script for directory: /home/lxu/experiments/scip/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lpi" TYPE FILE FILES
    "/home/lxu/experiments/scip/src/lpi/lpi.h"
    "/home/lxu/experiments/scip/src/lpi/type_lpi.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dijkstra" TYPE FILE FILES "/home/lxu/experiments/scip/src/dijkstra/dijkstra.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/objscip" TYPE FILE FILES
    "/home/lxu/experiments/scip/src/objscip/objbenders.h"
    "/home/lxu/experiments/scip/src/objscip/objbenderscut.h"
    "/home/lxu/experiments/scip/src/objscip/objbranchrule.h"
    "/home/lxu/experiments/scip/src/objscip/objcloneable.h"
    "/home/lxu/experiments/scip/src/objscip/objconshdlr.h"
    "/home/lxu/experiments/scip/src/objscip/objcutsel.h"
    "/home/lxu/experiments/scip/src/objscip/objdialog.h"
    "/home/lxu/experiments/scip/src/objscip/objdisp.h"
    "/home/lxu/experiments/scip/src/objscip/objeventhdlr.h"
    "/home/lxu/experiments/scip/src/objscip/objheur.h"
    "/home/lxu/experiments/scip/src/objscip/objmessagehdlr.h"
    "/home/lxu/experiments/scip/src/objscip/objnodesel.h"
    "/home/lxu/experiments/scip/src/objscip/objpresol.h"
    "/home/lxu/experiments/scip/src/objscip/objpricer.h"
    "/home/lxu/experiments/scip/src/objscip/objprobcloneable.h"
    "/home/lxu/experiments/scip/src/objscip/objprobdata.h"
    "/home/lxu/experiments/scip/src/objscip/objprop.h"
    "/home/lxu/experiments/scip/src/objscip/objreader.h"
    "/home/lxu/experiments/scip/src/objscip/objrelax.h"
    "/home/lxu/experiments/scip/src/objscip/objscipdefplugins.h"
    "/home/lxu/experiments/scip/src/objscip/objscip.h"
    "/home/lxu/experiments/scip/src/objscip/objsepa.h"
    "/home/lxu/experiments/scip/src/objscip/objtable.h"
    "/home/lxu/experiments/scip/src/objscip/objvardata.h"
    "/home/lxu/experiments/scip/src/objscip/type_objcloneable.h"
    "/home/lxu/experiments/scip/src/objscip/type_objprobcloneable.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/scip" TYPE FILE FILES
    "/home/lxu/experiments/scip/src/scip/bandit.h"
    "/home/lxu/experiments/scip/src/scip/bandit_epsgreedy.h"
    "/home/lxu/experiments/scip/src/scip/bandit_exp3.h"
    "/home/lxu/experiments/scip/src/scip/bandit_exp3ix.h"
    "/home/lxu/experiments/scip/src/scip/bandit_ucb.h"
    "/home/lxu/experiments/scip/src/scip/benders.h"
    "/home/lxu/experiments/scip/src/scip/benders_default.h"
    "/home/lxu/experiments/scip/src/scip/benderscut.h"
    "/home/lxu/experiments/scip/src/scip/benderscut_feas.h"
    "/home/lxu/experiments/scip/src/scip/benderscut_feasalt.h"
    "/home/lxu/experiments/scip/src/scip/benderscut_int.h"
    "/home/lxu/experiments/scip/src/scip/benderscut_nogood.h"
    "/home/lxu/experiments/scip/src/scip/benderscut_opt.h"
    "/home/lxu/experiments/scip/src/scip/bendersdefcuts.h"
    "/home/lxu/experiments/scip/src/scip/bitencode.h"
    "/home/lxu/experiments/scip/src/scip/boundstore.h"
    "/home/lxu/experiments/scip/src/scip/branch_allfullstrong.h"
    "/home/lxu/experiments/scip/src/scip/branch_cloud.h"
    "/home/lxu/experiments/scip/src/scip/branch_distribution.h"
    "/home/lxu/experiments/scip/src/scip/branch_fullstrong.h"
    "/home/lxu/experiments/scip/src/scip/branch.h"
    "/home/lxu/experiments/scip/src/scip/branch_inference.h"
    "/home/lxu/experiments/scip/src/scip/branch_leastinf.h"
    "/home/lxu/experiments/scip/src/scip/branch_lookahead.h"
    "/home/lxu/experiments/scip/src/scip/branch_mostinf.h"
    "/home/lxu/experiments/scip/src/scip/branch_multaggr.h"
    "/home/lxu/experiments/scip/src/scip/branch_nodereopt.h"
    "/home/lxu/experiments/scip/src/scip/branch_pscost.h"
    "/home/lxu/experiments/scip/src/scip/branch_random.h"
    "/home/lxu/experiments/scip/src/scip/branch_relpscost.h"
    "/home/lxu/experiments/scip/src/scip/branch_vanillafullstrong.h"
    "/home/lxu/experiments/scip/src/scip/clock.h"
    "/home/lxu/experiments/scip/src/scip/compr.h"
    "/home/lxu/experiments/scip/src/scip/compr_largestrepr.h"
    "/home/lxu/experiments/scip/src/scip/compr_weakcompr.h"
    "/home/lxu/experiments/scip/src/scip/concsolver.h"
    "/home/lxu/experiments/scip/src/scip/concsolver_scip.h"
    "/home/lxu/experiments/scip/src/scip/concurrent.h"
    "/home/lxu/experiments/scip/src/scip/conflict.h"
    "/home/lxu/experiments/scip/src/scip/conflict_graphanalysis.h"
    "/home/lxu/experiments/scip/src/scip/conflict_dualproofanalysis.h"
    "/home/lxu/experiments/scip/src/scip/conflict_general.h"
    "/home/lxu/experiments/scip/src/scip/conflictstore.h"
    "/home/lxu/experiments/scip/src/scip/cons_abspower.h"
    "/home/lxu/experiments/scip/src/scip/cons_and.h"
    "/home/lxu/experiments/scip/src/scip/cons_benders.h"
    "/home/lxu/experiments/scip/src/scip/cons_benderslp.h"
    "/home/lxu/experiments/scip/src/scip/cons_bounddisjunction.h"
    "/home/lxu/experiments/scip/src/scip/cons_cardinality.h"
    "/home/lxu/experiments/scip/src/scip/cons_components.h"
    "/home/lxu/experiments/scip/src/scip/cons_conjunction.h"
    "/home/lxu/experiments/scip/src/scip/cons_countsols.h"
    "/home/lxu/experiments/scip/src/scip/cons_cumulative.h"
    "/home/lxu/experiments/scip/src/scip/cons_disjunction.h"
    "/home/lxu/experiments/scip/src/scip/cons.h"
    "/home/lxu/experiments/scip/src/scip/cons_indicator.h"
    "/home/lxu/experiments/scip/src/scip/cons_integral.h"
    "/home/lxu/experiments/scip/src/scip/cons_knapsack.h"
    "/home/lxu/experiments/scip/src/scip/cons_linear.h"
    "/home/lxu/experiments/scip/src/scip/cons_linking.h"
    "/home/lxu/experiments/scip/src/scip/cons_logicor.h"
    "/home/lxu/experiments/scip/src/scip/cons_nonlinear.h"
    "/home/lxu/experiments/scip/src/scip/cons_orbisack.h"
    "/home/lxu/experiments/scip/src/scip/cons_orbitope.h"
    "/home/lxu/experiments/scip/src/scip/cons_or.h"
    "/home/lxu/experiments/scip/src/scip/cons_pseudoboolean.h"
    "/home/lxu/experiments/scip/src/scip/cons_quadratic.h"
    "/home/lxu/experiments/scip/src/scip/cons_setppc.h"
    "/home/lxu/experiments/scip/src/scip/cons_soc.h"
    "/home/lxu/experiments/scip/src/scip/cons_sos1.h"
    "/home/lxu/experiments/scip/src/scip/cons_sos2.h"
    "/home/lxu/experiments/scip/src/scip/cons_superindicator.h"
    "/home/lxu/experiments/scip/src/scip/cons_symresack.h"
    "/home/lxu/experiments/scip/src/scip/cons_varbound.h"
    "/home/lxu/experiments/scip/src/scip/cons_xor.h"
    "/home/lxu/experiments/scip/src/scip/cutpool.h"
    "/home/lxu/experiments/scip/src/scip/cuts.h"
    "/home/lxu/experiments/scip/src/scip/cutsel.h"
    "/home/lxu/experiments/scip/src/scip/cutsel_hybrid.h"
    "/home/lxu/experiments/scip/src/scip/dbldblarith.h"
    "/home/lxu/experiments/scip/src/scip/debug.h"
    "/home/lxu/experiments/scip/src/scip/dcmp.h"
    "/home/lxu/experiments/scip/src/scip/def.h"
    "/home/lxu/experiments/scip/src/scip/dialog_default.h"
    "/home/lxu/experiments/scip/src/scip/dialog.h"
    "/home/lxu/experiments/scip/src/scip/disp_default.h"
    "/home/lxu/experiments/scip/src/scip/disp.h"
    "/home/lxu/experiments/scip/src/scip/event_globalbnd.h"
    "/home/lxu/experiments/scip/src/scip/event.h"
    "/home/lxu/experiments/scip/src/scip/event_estim.h"
    "/home/lxu/experiments/scip/src/scip/event_softtimelimit.h"
    "/home/lxu/experiments/scip/src/scip/event_solvingphase.h"
    "/home/lxu/experiments/scip/src/scip/expr.h"
    "/home/lxu/experiments/scip/src/scip/expr_abs.h"
    "/home/lxu/experiments/scip/src/scip/expr_entropy.h"
    "/home/lxu/experiments/scip/src/scip/expr_erf.h"
    "/home/lxu/experiments/scip/src/scip/expr_exp.h"
    "/home/lxu/experiments/scip/src/scip/expr_log.h"
    "/home/lxu/experiments/scip/src/scip/expr_pow.h"
    "/home/lxu/experiments/scip/src/scip/expr_product.h"
    "/home/lxu/experiments/scip/src/scip/expr_sum.h"
    "/home/lxu/experiments/scip/src/scip/expr_trig.h"
    "/home/lxu/experiments/scip/src/scip/expr_value.h"
    "/home/lxu/experiments/scip/src/scip/expr_var.h"
    "/home/lxu/experiments/scip/src/scip/expr_varidx.h"
    "/home/lxu/experiments/scip/src/scip/exprinterpret.h"
    "/home/lxu/experiments/scip/src/scip/heur_actconsdiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_adaptivediving.h"
    "/home/lxu/experiments/scip/src/scip/heur_bound.h"
    "/home/lxu/experiments/scip/src/scip/heur_clique.h"
    "/home/lxu/experiments/scip/src/scip/heur_coefdiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_completesol.h"
    "/home/lxu/experiments/scip/src/scip/heur_conflictdiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_crossover.h"
    "/home/lxu/experiments/scip/src/scip/heur_dins.h"
    "/home/lxu/experiments/scip/src/scip/heur_distributiondiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_dps.h"
    "/home/lxu/experiments/scip/src/scip/heur_dualval.h"
    "/home/lxu/experiments/scip/src/scip/heur_farkasdiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_feaspump.h"
    "/home/lxu/experiments/scip/src/scip/heur_fixandinfer.h"
    "/home/lxu/experiments/scip/src/scip/heur_fracdiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_gins.h"
    "/home/lxu/experiments/scip/src/scip/heur_guideddiving.h"
    "/home/lxu/experiments/scip/src/scip/heur.h"
    "/home/lxu/experiments/scip/src/scip/heur_indicator.h"
    "/home/lxu/experiments/scip/src/scip/heur_indicatordiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_intdiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_intshifting.h"
    "/home/lxu/experiments/scip/src/scip/heuristics.h"
    "/home/lxu/experiments/scip/src/scip/heur_linesearchdiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_localbranching.h"
    "/home/lxu/experiments/scip/src/scip/heur_locks.h"
    "/home/lxu/experiments/scip/src/scip/heur_alns.h"
    "/home/lxu/experiments/scip/src/scip/heur_lpface.h"
    "/home/lxu/experiments/scip/src/scip/heur_multistart.h"
    "/home/lxu/experiments/scip/src/scip/heur_mutation.h"
    "/home/lxu/experiments/scip/src/scip/heur_mpec.h"
    "/home/lxu/experiments/scip/src/scip/heur_nlpdiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_objpscostdiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_octane.h"
    "/home/lxu/experiments/scip/src/scip/heur_ofins.h"
    "/home/lxu/experiments/scip/src/scip/heur_oneopt.h"
    "/home/lxu/experiments/scip/src/scip/heur_padm.h"
    "/home/lxu/experiments/scip/src/scip/heur_proximity.h"
    "/home/lxu/experiments/scip/src/scip/heur_pscostdiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_randrounding.h"
    "/home/lxu/experiments/scip/src/scip/heur_rens.h"
    "/home/lxu/experiments/scip/src/scip/heur_reoptsols.h"
    "/home/lxu/experiments/scip/src/scip/heur_repair.h"
    "/home/lxu/experiments/scip/src/scip/heur_rins.h"
    "/home/lxu/experiments/scip/src/scip/heur_rootsoldiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_rounding.h"
    "/home/lxu/experiments/scip/src/scip/heur_shiftandpropagate.h"
    "/home/lxu/experiments/scip/src/scip/heur_shifting.h"
    "/home/lxu/experiments/scip/src/scip/heur_simplerounding.h"
    "/home/lxu/experiments/scip/src/scip/heur_subnlp.h"
    "/home/lxu/experiments/scip/src/scip/heur_sync.h"
    "/home/lxu/experiments/scip/src/scip/heur_trivial.h"
    "/home/lxu/experiments/scip/src/scip/heur_trivialnegation.h"
    "/home/lxu/experiments/scip/src/scip/heur_trustregion.h"
    "/home/lxu/experiments/scip/src/scip/heur_trysol.h"
    "/home/lxu/experiments/scip/src/scip/heur_twoopt.h"
    "/home/lxu/experiments/scip/src/scip/heur_undercover.h"
    "/home/lxu/experiments/scip/src/scip/heur_vbounds.h"
    "/home/lxu/experiments/scip/src/scip/heur_veclendiving.h"
    "/home/lxu/experiments/scip/src/scip/heur_zeroobj.h"
    "/home/lxu/experiments/scip/src/scip/heur_zirounding.h"
    "/home/lxu/experiments/scip/src/scip/history.h"
    "/home/lxu/experiments/scip/src/scip/implics.h"
    "/home/lxu/experiments/scip/src/scip/interrupt.h"
    "/home/lxu/experiments/scip/src/scip/intervalarith.h"
    "/home/lxu/experiments/scip/src/scip/lapack_calls.h"
    "/home/lxu/experiments/scip/src/scip/lp.h"
    "/home/lxu/experiments/scip/src/scip/mem.h"
    "/home/lxu/experiments/scip/src/scip/message_default.h"
    "/home/lxu/experiments/scip/src/scip/message.h"
    "/home/lxu/experiments/scip/src/scip/misc.h"
    "/home/lxu/experiments/scip/src/scip/nlhdlr_bilinear.h"
    "/home/lxu/experiments/scip/src/scip/nlhdlr_convex.h"
    "/home/lxu/experiments/scip/src/scip/nlhdlr_default.h"
    "/home/lxu/experiments/scip/src/scip/nlhdlr_perspective.h"
    "/home/lxu/experiments/scip/src/scip/nlhdlr_quadratic.h"
    "/home/lxu/experiments/scip/src/scip/nlhdlr_quotient.h"
    "/home/lxu/experiments/scip/src/scip/nlhdlr_soc.h"
    "/home/lxu/experiments/scip/src/scip/nlhdlr.h"
    "/home/lxu/experiments/scip/src/scip/nlp.h"
    "/home/lxu/experiments/scip/src/scip/nlpi.h"
    "/home/lxu/experiments/scip/src/scip/nlpioracle.h"
    "/home/lxu/experiments/scip/src/scip/nlpi_all.h"
    "/home/lxu/experiments/scip/src/scip/nlpi_filtersqp.h"
    "/home/lxu/experiments/scip/src/scip/nlpi_ipopt.h"
    "/home/lxu/experiments/scip/src/scip/nlpi_worhp.h"
    "/home/lxu/experiments/scip/src/scip/nodesel_bfs.h"
    "/home/lxu/experiments/scip/src/scip/nodesel_breadthfirst.h"
    "/home/lxu/experiments/scip/src/scip/nodesel_dfs.h"
    "/home/lxu/experiments/scip/src/scip/nodesel_estimate.h"
    "/home/lxu/experiments/scip/src/scip/nodesel.h"
    "/home/lxu/experiments/scip/src/scip/nodesel_hybridestim.h"
    "/home/lxu/experiments/scip/src/scip/nodesel_restartdfs.h"
    "/home/lxu/experiments/scip/src/scip/nodesel_uct.h"
    "/home/lxu/experiments/scip/src/scip/paramset.h"
    "/home/lxu/experiments/scip/src/scip/presol_boundshift.h"
    "/home/lxu/experiments/scip/src/scip/presol_milp.h"
    "/home/lxu/experiments/scip/src/scip/presol_convertinttobin.h"
    "/home/lxu/experiments/scip/src/scip/presol_domcol.h"
    "/home/lxu/experiments/scip/src/scip/presol_dualagg.h"
    "/home/lxu/experiments/scip/src/scip/presol_dualcomp.h"
    "/home/lxu/experiments/scip/src/scip/presol_dualinfer.h"
    "/home/lxu/experiments/scip/src/scip/presol_gateextraction.h"
    "/home/lxu/experiments/scip/src/scip/presol.h"
    "/home/lxu/experiments/scip/src/scip/presol_implics.h"
    "/home/lxu/experiments/scip/src/scip/presol_inttobinary.h"
    "/home/lxu/experiments/scip/src/scip/presol_qpkktref.h"
    "/home/lxu/experiments/scip/src/scip/presol_redvub.h"
    "/home/lxu/experiments/scip/src/scip/presol_sparsify.h"
    "/home/lxu/experiments/scip/src/scip/presol_dualsparsify.h"
    "/home/lxu/experiments/scip/src/scip/presol_stuffing.h"
    "/home/lxu/experiments/scip/src/scip/presol_trivial.h"
    "/home/lxu/experiments/scip/src/scip/presol_tworowbnd.h"
    "/home/lxu/experiments/scip/src/scip/presolve.h"
    "/home/lxu/experiments/scip/src/scip/pricer.h"
    "/home/lxu/experiments/scip/src/scip/pricestore.h"
    "/home/lxu/experiments/scip/src/scip/primal.h"
    "/home/lxu/experiments/scip/src/scip/prob.h"
    "/home/lxu/experiments/scip/src/scip/prop_dualfix.h"
    "/home/lxu/experiments/scip/src/scip/prop_genvbounds.h"
    "/home/lxu/experiments/scip/src/scip/prop.h"
    "/home/lxu/experiments/scip/src/scip/prop_nlobbt.h"
    "/home/lxu/experiments/scip/src/scip/prop_obbt.h"
    "/home/lxu/experiments/scip/src/scip/prop_probing.h"
    "/home/lxu/experiments/scip/src/scip/prop_pseudoobj.h"
    "/home/lxu/experiments/scip/src/scip/prop_redcost.h"
    "/home/lxu/experiments/scip/src/scip/prop_rootredcost.h"
    "/home/lxu/experiments/scip/src/scip/prop_symmetry.h"
    "/home/lxu/experiments/scip/src/scip/prop_sync.h"
    "/home/lxu/experiments/scip/src/scip/prop_vbounds.h"
    "/home/lxu/experiments/scip/src/scip/pub_branch.h"
    "/home/lxu/experiments/scip/src/scip/pub_bandit.h"
    "/home/lxu/experiments/scip/src/scip/pub_bandit_epsgreedy.h"
    "/home/lxu/experiments/scip/src/scip/pub_bandit_exp3.h"
    "/home/lxu/experiments/scip/src/scip/pub_bandit_exp3ix.h"
    "/home/lxu/experiments/scip/src/scip/pub_bandit_ucb.h"
    "/home/lxu/experiments/scip/src/scip/pub_benders.h"
    "/home/lxu/experiments/scip/src/scip/pub_benderscut.h"
    "/home/lxu/experiments/scip/src/scip/pub_compr.h"
    "/home/lxu/experiments/scip/src/scip/pub_conflict.h"
    "/home/lxu/experiments/scip/src/scip/pub_cons.h"
    "/home/lxu/experiments/scip/src/scip/pub_cutpool.h"
    "/home/lxu/experiments/scip/src/scip/pub_cutsel.h"
    "/home/lxu/experiments/scip/src/scip/pub_dcmp.h"
    "/home/lxu/experiments/scip/src/scip/pub_dialog.h"
    "/home/lxu/experiments/scip/src/scip/pub_disp.h"
    "/home/lxu/experiments/scip/src/scip/pub_event.h"
    "/home/lxu/experiments/scip/src/scip/pub_expr.h"
    "/home/lxu/experiments/scip/src/scip/pub_fileio.h"
    "/home/lxu/experiments/scip/src/scip/pub_heur.h"
    "/home/lxu/experiments/scip/src/scip/pub_history.h"
    "/home/lxu/experiments/scip/src/scip/pub_implics.h"
    "/home/lxu/experiments/scip/src/scip/pub_lp.h"
    "/home/lxu/experiments/scip/src/scip/pub_matrix.h"
    "/home/lxu/experiments/scip/src/scip/pub_message.h"
    "/home/lxu/experiments/scip/src/scip/pub_misc.h"
    "/home/lxu/experiments/scip/src/scip/pub_misc_linear.h"
    "/home/lxu/experiments/scip/src/scip/pub_misc_rowprep.h"
    "/home/lxu/experiments/scip/src/scip/pub_misc_select.h"
    "/home/lxu/experiments/scip/src/scip/pub_misc_sort.h"
    "/home/lxu/experiments/scip/src/scip/pub_nlhdlr.h"
    "/home/lxu/experiments/scip/src/scip/pub_nlp.h"
    "/home/lxu/experiments/scip/src/scip/pub_nlpi.h"
    "/home/lxu/experiments/scip/src/scip/pub_nodesel.h"
    "/home/lxu/experiments/scip/src/scip/pub_paramset.h"
    "/home/lxu/experiments/scip/src/scip/pub_presol.h"
    "/home/lxu/experiments/scip/src/scip/pub_pricer.h"
    "/home/lxu/experiments/scip/src/scip/pub_prop.h"
    "/home/lxu/experiments/scip/src/scip/pub_reader.h"
    "/home/lxu/experiments/scip/src/scip/pub_relax.h"
    "/home/lxu/experiments/scip/src/scip/pub_reopt.h"
    "/home/lxu/experiments/scip/src/scip/pub_sepa.h"
    "/home/lxu/experiments/scip/src/scip/pub_sol.h"
    "/home/lxu/experiments/scip/src/scip/pub_table.h"
    "/home/lxu/experiments/scip/src/scip/pub_tree.h"
    "/home/lxu/experiments/scip/src/scip/pub_var.h"
    "/home/lxu/experiments/scip/src/scip/rbtree.h"
    "/home/lxu/experiments/scip/src/scip/reader_bnd.h"
    "/home/lxu/experiments/scip/src/scip/reader_ccg.h"
    "/home/lxu/experiments/scip/src/scip/reader_cip.h"
    "/home/lxu/experiments/scip/src/scip/reader_cnf.h"
    "/home/lxu/experiments/scip/src/scip/reader_cor.h"
    "/home/lxu/experiments/scip/src/scip/reader_dec.h"
    "/home/lxu/experiments/scip/src/scip/reader_diff.h"
    "/home/lxu/experiments/scip/src/scip/reader_fix.h"
    "/home/lxu/experiments/scip/src/scip/reader_fzn.h"
    "/home/lxu/experiments/scip/src/scip/reader_gms.h"
    "/home/lxu/experiments/scip/src/scip/reader.h"
    "/home/lxu/experiments/scip/src/scip/reader_lp.h"
    "/home/lxu/experiments/scip/src/scip/reader_mps.h"
    "/home/lxu/experiments/scip/src/scip/reader_mst.h"
    "/home/lxu/experiments/scip/src/scip/reader_nl.h"
    "/home/lxu/experiments/scip/src/scip/reader_opb.h"
    "/home/lxu/experiments/scip/src/scip/reader_osil.h"
    "/home/lxu/experiments/scip/src/scip/reader_pbm.h"
    "/home/lxu/experiments/scip/src/scip/reader_pip.h"
    "/home/lxu/experiments/scip/src/scip/reader_ppm.h"
    "/home/lxu/experiments/scip/src/scip/reader_rlp.h"
    "/home/lxu/experiments/scip/src/scip/reader_sol.h"
    "/home/lxu/experiments/scip/src/scip/reader_smps.h"
    "/home/lxu/experiments/scip/src/scip/reader_sto.h"
    "/home/lxu/experiments/scip/src/scip/reader_tim.h"
    "/home/lxu/experiments/scip/src/scip/reader_wbo.h"
    "/home/lxu/experiments/scip/src/scip/reader_zpl.h"
    "/home/lxu/experiments/scip/src/scip/relax.h"
    "/home/lxu/experiments/scip/src/scip/reopt.h"
    "/home/lxu/experiments/scip/src/scip/retcode.h"
    "/home/lxu/experiments/scip/src/scip/scipbuildflags.h"
    "/home/lxu/experiments/scip/src/scip/scipcoreplugins.h"
    "/home/lxu/experiments/scip/src/scip/scipdefplugins.h"
    "/home/lxu/experiments/scip/src/scip/scipgithash.h"
    "/home/lxu/experiments/scip/src/scip/scip.h"
    "/home/lxu/experiments/scip/src/scip/scip_bandit.h"
    "/home/lxu/experiments/scip/src/scip/scip_benders.h"
    "/home/lxu/experiments/scip/src/scip/scip_branch.h"
    "/home/lxu/experiments/scip/src/scip/scip_compr.h"
    "/home/lxu/experiments/scip/src/scip/scip_concurrent.h"
    "/home/lxu/experiments/scip/src/scip/scip_conflict.h"
    "/home/lxu/experiments/scip/src/scip/scip_cons.h"
    "/home/lxu/experiments/scip/src/scip/scip_copy.h"
    "/home/lxu/experiments/scip/src/scip/scip_cut.h"
    "/home/lxu/experiments/scip/src/scip/scip_cutsel.h"
    "/home/lxu/experiments/scip/src/scip/scip_datastructures.h"
    "/home/lxu/experiments/scip/src/scip/scip_debug.h"
    "/home/lxu/experiments/scip/src/scip/scip_dcmp.h"
    "/home/lxu/experiments/scip/src/scip/scip_dialog.h"
    "/home/lxu/experiments/scip/src/scip/scip_disp.h"
    "/home/lxu/experiments/scip/src/scip/scip_event.h"
    "/home/lxu/experiments/scip/src/scip/scip_expr.h"
    "/home/lxu/experiments/scip/src/scip/scip_general.h"
    "/home/lxu/experiments/scip/src/scip/scip_heur.h"
    "/home/lxu/experiments/scip/src/scip/scip_lp.h"
    "/home/lxu/experiments/scip/src/scip/scip_mem.h"
    "/home/lxu/experiments/scip/src/scip/scip_message.h"
    "/home/lxu/experiments/scip/src/scip/scip_nlp.h"
    "/home/lxu/experiments/scip/src/scip/scip_nlpi.h"
    "/home/lxu/experiments/scip/src/scip/scip_nodesel.h"
    "/home/lxu/experiments/scip/src/scip/scip_numerics.h"
    "/home/lxu/experiments/scip/src/scip/scip_param.h"
    "/home/lxu/experiments/scip/src/scip/scip_presol.h"
    "/home/lxu/experiments/scip/src/scip/scip_pricer.h"
    "/home/lxu/experiments/scip/src/scip/scip_prob.h"
    "/home/lxu/experiments/scip/src/scip/scip_probing.h"
    "/home/lxu/experiments/scip/src/scip/scip_prop.h"
    "/home/lxu/experiments/scip/src/scip/scip_randnumgen.h"
    "/home/lxu/experiments/scip/src/scip/scip_reader.h"
    "/home/lxu/experiments/scip/src/scip/scip_relax.h"
    "/home/lxu/experiments/scip/src/scip/scip_reopt.h"
    "/home/lxu/experiments/scip/src/scip/scip_sepa.h"
    "/home/lxu/experiments/scip/src/scip/scip_sol.h"
    "/home/lxu/experiments/scip/src/scip/scip_solve.h"
    "/home/lxu/experiments/scip/src/scip/scip_solvingstats.h"
    "/home/lxu/experiments/scip/src/scip/scip_table.h"
    "/home/lxu/experiments/scip/src/scip/scip_timing.h"
    "/home/lxu/experiments/scip/src/scip/scip_tree.h"
    "/home/lxu/experiments/scip/src/scip/scip_validation.h"
    "/home/lxu/experiments/scip/src/scip/scip_var.h"
    "/home/lxu/experiments/scip/src/scip/scipshell.h"
    "/home/lxu/experiments/scip/src/scip/sepa_cgmip.h"
    "/home/lxu/experiments/scip/src/scip/sepa_clique.h"
    "/home/lxu/experiments/scip/src/scip/sepa_closecuts.h"
    "/home/lxu/experiments/scip/src/scip/sepa_aggregation.h"
    "/home/lxu/experiments/scip/src/scip/sepa_convexproj.h"
    "/home/lxu/experiments/scip/src/scip/sepa_disjunctive.h"
    "/home/lxu/experiments/scip/src/scip/sepa_eccuts.h"
    "/home/lxu/experiments/scip/src/scip/sepa_gauge.h"
    "/home/lxu/experiments/scip/src/scip/sepa_gomory.h"
    "/home/lxu/experiments/scip/src/scip/sepa.h"
    "/home/lxu/experiments/scip/src/scip/sepa_impliedbounds.h"
    "/home/lxu/experiments/scip/src/scip/sepa_interminor.h"
    "/home/lxu/experiments/scip/src/scip/sepa_intobj.h"
    "/home/lxu/experiments/scip/src/scip/sepa_mcf.h"
    "/home/lxu/experiments/scip/src/scip/sepa_minor.h"
    "/home/lxu/experiments/scip/src/scip/sepa_mixing.h"
    "/home/lxu/experiments/scip/src/scip/sepa_oddcycle.h"
    "/home/lxu/experiments/scip/src/scip/sepa_rapidlearning.h"
    "/home/lxu/experiments/scip/src/scip/sepa_rlt.h"
    "/home/lxu/experiments/scip/src/scip/sepastore.h"
    "/home/lxu/experiments/scip/src/scip/sepa_zerohalf.h"
    "/home/lxu/experiments/scip/src/scip/set.h"
    "/home/lxu/experiments/scip/src/scip/sol.h"
    "/home/lxu/experiments/scip/src/scip/solve.h"
    "/home/lxu/experiments/scip/src/scip/stat.h"
    "/home/lxu/experiments/scip/src/scip/struct_bandit.h"
    "/home/lxu/experiments/scip/src/scip/struct_benders.h"
    "/home/lxu/experiments/scip/src/scip/struct_benderscut.h"
    "/home/lxu/experiments/scip/src/scip/struct_branch.h"
    "/home/lxu/experiments/scip/src/scip/struct_clock.h"
    "/home/lxu/experiments/scip/src/scip/struct_compr.h"
    "/home/lxu/experiments/scip/src/scip/struct_concsolver.h"
    "/home/lxu/experiments/scip/src/scip/struct_concurrent.h"
    "/home/lxu/experiments/scip/src/scip/struct_conflict.h"
    "/home/lxu/experiments/scip/src/scip/struct_conflictstore.h"
    "/home/lxu/experiments/scip/src/scip/struct_cons.h"
    "/home/lxu/experiments/scip/src/scip/struct_cutpool.h"
    "/home/lxu/experiments/scip/src/scip/struct_cuts.h"
    "/home/lxu/experiments/scip/src/scip/struct_cutsel.h"
    "/home/lxu/experiments/scip/src/scip/struct_dcmp.h"
    "/home/lxu/experiments/scip/src/scip/struct_dialog.h"
    "/home/lxu/experiments/scip/src/scip/struct_disp.h"
    "/home/lxu/experiments/scip/src/scip/struct_event.h"
    "/home/lxu/experiments/scip/src/scip/struct_expr.h"
    "/home/lxu/experiments/scip/src/scip/struct_heur.h"
    "/home/lxu/experiments/scip/src/scip/struct_history.h"
    "/home/lxu/experiments/scip/src/scip/struct_implics.h"
    "/home/lxu/experiments/scip/src/scip/struct_lp.h"
    "/home/lxu/experiments/scip/src/scip/struct_matrix.h"
    "/home/lxu/experiments/scip/src/scip/struct_mem.h"
    "/home/lxu/experiments/scip/src/scip/struct_message.h"
    "/home/lxu/experiments/scip/src/scip/struct_misc.h"
    "/home/lxu/experiments/scip/src/scip/struct_nlhdlr.h"
    "/home/lxu/experiments/scip/src/scip/struct_nlp.h"
    "/home/lxu/experiments/scip/src/scip/struct_nlpi.h"
    "/home/lxu/experiments/scip/src/scip/struct_nodesel.h"
    "/home/lxu/experiments/scip/src/scip/struct_paramset.h"
    "/home/lxu/experiments/scip/src/scip/struct_presol.h"
    "/home/lxu/experiments/scip/src/scip/struct_pricer.h"
    "/home/lxu/experiments/scip/src/scip/struct_pricestore.h"
    "/home/lxu/experiments/scip/src/scip/struct_primal.h"
    "/home/lxu/experiments/scip/src/scip/struct_prob.h"
    "/home/lxu/experiments/scip/src/scip/struct_prop.h"
    "/home/lxu/experiments/scip/src/scip/struct_reader.h"
    "/home/lxu/experiments/scip/src/scip/struct_relax.h"
    "/home/lxu/experiments/scip/src/scip/struct_reopt.h"
    "/home/lxu/experiments/scip/src/scip/struct_scip.h"
    "/home/lxu/experiments/scip/src/scip/struct_sepa.h"
    "/home/lxu/experiments/scip/src/scip/struct_sepastore.h"
    "/home/lxu/experiments/scip/src/scip/struct_set.h"
    "/home/lxu/experiments/scip/src/scip/struct_sol.h"
    "/home/lxu/experiments/scip/src/scip/struct_stat.h"
    "/home/lxu/experiments/scip/src/scip/struct_syncstore.h"
    "/home/lxu/experiments/scip/src/scip/struct_table.h"
    "/home/lxu/experiments/scip/src/scip/struct_tree.h"
    "/home/lxu/experiments/scip/src/scip/struct_var.h"
    "/home/lxu/experiments/scip/src/scip/struct_visual.h"
    "/home/lxu/experiments/scip/src/scip/symmetry.h"
    "/home/lxu/experiments/scip/src/scip/syncstore.h"
    "/home/lxu/experiments/scip/src/scip/table_default.h"
    "/home/lxu/experiments/scip/src/scip/table.h"
    "/home/lxu/experiments/scip/src/scip/tree.h"
    "/home/lxu/experiments/scip/src/scip/treemodel.h"
    "/home/lxu/experiments/scip/src/scip/type_bandit.h"
    "/home/lxu/experiments/scip/src/scip/type_benders.h"
    "/home/lxu/experiments/scip/src/scip/type_benderscut.h"
    "/home/lxu/experiments/scip/src/scip/type_branch.h"
    "/home/lxu/experiments/scip/src/scip/type_clock.h"
    "/home/lxu/experiments/scip/src/scip/type_compr.h"
    "/home/lxu/experiments/scip/src/scip/type_concsolver.h"
    "/home/lxu/experiments/scip/src/scip/type_concurrent.h"
    "/home/lxu/experiments/scip/src/scip/type_conflict.h"
    "/home/lxu/experiments/scip/src/scip/type_conflictstore.h"
    "/home/lxu/experiments/scip/src/scip/type_cons.h"
    "/home/lxu/experiments/scip/src/scip/type_cutpool.h"
    "/home/lxu/experiments/scip/src/scip/type_cuts.h"
    "/home/lxu/experiments/scip/src/scip/type_cutsel.h"
    "/home/lxu/experiments/scip/src/scip/type_dcmp.h"
    "/home/lxu/experiments/scip/src/scip/type_dialog.h"
    "/home/lxu/experiments/scip/src/scip/type_disp.h"
    "/home/lxu/experiments/scip/src/scip/type_event.h"
    "/home/lxu/experiments/scip/src/scip/type_expr.h"
    "/home/lxu/experiments/scip/src/scip/type_exprinterpret.h"
    "/home/lxu/experiments/scip/src/scip/type_heur.h"
    "/home/lxu/experiments/scip/src/scip/type_history.h"
    "/home/lxu/experiments/scip/src/scip/type_implics.h"
    "/home/lxu/experiments/scip/src/scip/type_interrupt.h"
    "/home/lxu/experiments/scip/src/scip/type_lp.h"
    "/home/lxu/experiments/scip/src/scip/type_matrix.h"
    "/home/lxu/experiments/scip/src/scip/type_mem.h"
    "/home/lxu/experiments/scip/src/scip/type_message.h"
    "/home/lxu/experiments/scip/src/scip/type_misc.h"
    "/home/lxu/experiments/scip/src/scip/type_nlhdlr.h"
    "/home/lxu/experiments/scip/src/scip/type_nlp.h"
    "/home/lxu/experiments/scip/src/scip/type_nlpi.h"
    "/home/lxu/experiments/scip/src/scip/type_nodesel.h"
    "/home/lxu/experiments/scip/src/scip/type_paramset.h"
    "/home/lxu/experiments/scip/src/scip/type_presol.h"
    "/home/lxu/experiments/scip/src/scip/type_pricer.h"
    "/home/lxu/experiments/scip/src/scip/type_pricestore.h"
    "/home/lxu/experiments/scip/src/scip/type_primal.h"
    "/home/lxu/experiments/scip/src/scip/type_prob.h"
    "/home/lxu/experiments/scip/src/scip/type_prop.h"
    "/home/lxu/experiments/scip/src/scip/type_reader.h"
    "/home/lxu/experiments/scip/src/scip/type_relax.h"
    "/home/lxu/experiments/scip/src/scip/type_reopt.h"
    "/home/lxu/experiments/scip/src/scip/type_result.h"
    "/home/lxu/experiments/scip/src/scip/type_retcode.h"
    "/home/lxu/experiments/scip/src/scip/type_scip.h"
    "/home/lxu/experiments/scip/src/scip/type_sepa.h"
    "/home/lxu/experiments/scip/src/scip/type_sepastore.h"
    "/home/lxu/experiments/scip/src/scip/type_set.h"
    "/home/lxu/experiments/scip/src/scip/type_sol.h"
    "/home/lxu/experiments/scip/src/scip/type_stat.h"
    "/home/lxu/experiments/scip/src/scip/type_syncstore.h"
    "/home/lxu/experiments/scip/src/scip/type_table.h"
    "/home/lxu/experiments/scip/src/scip/type_timing.h"
    "/home/lxu/experiments/scip/src/scip/type_tree.h"
    "/home/lxu/experiments/scip/src/scip/type_var.h"
    "/home/lxu/experiments/scip/src/scip/type_visual.h"
    "/home/lxu/experiments/scip/src/scip/var.h"
    "/home/lxu/experiments/scip/src/scip/visual.h"
    "/home/lxu/experiments/scip/build/scip/config.h"
    "/home/lxu/experiments/scip/build/scip/scip_export.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/tclique" TYPE FILE FILES
    "/home/lxu/experiments/scip/src/tclique/tclique_coloring.h"
    "/home/lxu/experiments/scip/src/tclique/tclique_def.h"
    "/home/lxu/experiments/scip/src/tclique/tclique.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/tinycthread" TYPE FILE FILES "/home/lxu/experiments/scip/src/tinycthread/tinycthread.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/tpi" TYPE FILE FILES
    "/home/lxu/experiments/scip/src/tpi/def_openmp.h"
    "/home/lxu/experiments/scip/src/tpi/tpi.h"
    "/home/lxu/experiments/scip/src/tpi/type_tpi.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/xml" TYPE FILE FILES
    "/home/lxu/experiments/scip/src/xml/xmldef.h"
    "/home/lxu/experiments/scip/src/xml/xml.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/symmetry" TYPE FILE FILES
    "/home/lxu/experiments/scip/src/symmetry/compute_symmetry.h"
    "/home/lxu/experiments/scip/src/symmetry/type_symmetry.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/blockmemshell" TYPE FILE FILES "/home/lxu/experiments/scip/src/blockmemshell/memory.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/scip" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/scip")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/scip"
         RPATH "/usr/local/lib:/home/lxu/software/coinor/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/lxu/experiments/scip/build/bin/scip")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/scip" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/scip")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/scip"
         OLD_RPATH "/home/lxu/software/coinor/lib:::::::::::::::"
         NEW_RPATH "/usr/local/lib:/home/lxu/software/coinor/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/scip")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libscip.so.8.0.3.5"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libscip.so.8.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libscip.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/home/lxu/software/coinor/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/lxu/experiments/scip/build/lib/libscip.so.8.0.3.5"
    "/home/lxu/experiments/scip/build/lib/libscip.so.8.0"
    "/home/lxu/experiments/scip/build/lib/libscip.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libscip.so.8.0.3.5"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libscip.so.8.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libscip.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/lxu/software/coinor/lib:"
           NEW_RPATH "/home/lxu/software/coinor/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/scip/scip-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/scip/scip-targets.cmake"
         "/home/lxu/experiments/scip/build/src/CMakeFiles/Export/lib/cmake/scip/scip-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/scip/scip-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/scip/scip-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/scip" TYPE FILE FILES "/home/lxu/experiments/scip/build/src/CMakeFiles/Export/lib/cmake/scip/scip-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/scip" TYPE FILE FILES "/home/lxu/experiments/scip/build/src/CMakeFiles/Export/lib/cmake/scip/scip-targets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/scip" TYPE FILE FILES
    "/home/lxu/experiments/scip/build/CMakeFiles/scip-config.cmake"
    "/home/lxu/experiments/scip/build/scip-config-version.cmake"
    )
endif()

