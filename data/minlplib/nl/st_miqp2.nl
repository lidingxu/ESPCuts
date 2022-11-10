g3 0 1 0	# problem st_miqp2
 4 3 1 0 0	# vars, constraints, objectives, ranges, eqns
 0 1	# nonlinear constraints, objectives
 0 0	# network constraints: nonlinear, linear
 0 2 0	# nonlinear vars in constraints, objectives, both
 0 0 0 1	# linear network variables; functions; arith, flags
 2 0 0 0 2	# discrete variables: binary, integer, nonlinear (b,c,o)
 6 4	# nonzeros in Jacobian, gradients
 3 2	# max name lengths: constraints, variables
 0 0 0 0 0	# common exprs: b,c,o,c1,o1
b
0 0 1e10
0 0 1e10
0 0 1
0 0 1
r
1 0
1 0
2 5
C0
n0
C1
n0
C2
n0
O0 0
o54
4
o2
o2
n4
v0
v0
o2
n-3
v0
o2
o2
n2
v1
v1
o2
n-10
v1
k3
2
4
5
J0 2
0 1
2 -10
J1 2
1 1
3 -20
J2 2
0 1
1 1
G0 4
0 0
1 0
2 4
3 5
