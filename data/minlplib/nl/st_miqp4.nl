g3 0 1 0	# problem st_miqp4
 6 4 1 0 0	# vars, constraints, objectives, ranges, eqns
 0 1	# nonlinear constraints, objectives
 0 0	# network constraints: nonlinear, linear
 0 3 0	# nonlinear vars in constraints, objectives, both
 0 0 0 1	# linear network variables; functions; arith, flags
 3 0 0 0 0	# discrete variables: binary, integer, nonlinear (b,c,o)
 9 6	# nonzeros in Jacobian, gradients
 3 2	# max name lengths: constraints, variables
 0 0 0 0 0	# common exprs: b,c,o,c1,o1
b
0 0 1e15
0 0 1e15
0 0 1e15
0 0 1
0 0 1
0 0 1
r
2 0
1 0
1 0
1 0
C0
n0
C1
n0
C2
n0
C3
n0
O0 0
o54
6
o2
o2
n5
v0
v0
o2
n2
v0
o2
o2
n5
v1
v1
o2
n3
v1
o2
o2
n10
v2
v2
o2
n-500
v2
k5
2
4
6
7
8
J0 3
0 1
1 1
2 -1
J1 2
0 1
3 -5
J2 2
1 1
4 -10
J3 2
2 1
5 -30
G0 6
0 0
1 0
2 0
3 10
4 -4
5 5
