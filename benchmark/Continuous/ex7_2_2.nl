g3 0 1 0	# problem ex7_2_2
 6 5 1 0 4	# vars, constraints, objectives, ranges, eqns
 5 0	# nonlinear constraints, objectives
 0 0	# network constraints: nonlinear, linear
 6 0 0	# nonlinear vars in constraints, objectives, both
 0 0 0 1	# linear network variables; functions; arith, flags
 0 0 0 0 0	# discrete variables: binary, integer, nonlinear (b,c,o)
 15 1	# nonzeros in Jacobian, gradients
 3 2	# max name lengths: constraints, variables
 0 0 0 0 0	# common exprs: b,c,o,c1,o1
b
0 0 1
0 0 1
0 0 1
0 0 1
0 1e-5 16
0 1e-5 16
x2
4 1e-5
5 1e-5
r
4 1
4 0
4 1
4 0
1 4
C0
o0
o2
o2
n9.755988e-2
v0
v4
v0
C1
o0
o2
o2
n9.65842812e-2
v1
v5
v1
C2
o0
o2
o2
n3.91908e-2
v2
v4
v2
C3
o0
o2
o2
n3.527172e-2
v3
v5
v3
C4
o0
o5
v4
n.5
o5
v5
n.5
O0 0
n0
k5
4
6
8
9
12
J0 2
0 0
4 0
J1 3
0 -1
1 0
5 0
J2 3
0 1
2 0
4 0
J3 5
0 -1
1 1
2 -1
3 0
5 0
J4 2
4 0
5 0
G0 1
3 -1
