g3 0 1 0	# problem nvs07
 3 2 1 0 0	# vars, constraints, objectives, ranges, eqns
 1 1	# nonlinear constraints, objectives
 0 0	# network constraints: nonlinear, linear
 2 1 1	# nonlinear vars in constraints, objectives, both
 0 0 0 1	# linear network variables; functions; arith, flags
 0 1 1 1 0	# discrete variables: binary, integer, nonlinear (b,c,o)
 5 3	# nonzeros in Jacobian, gradients
 3 2	# max name lengths: constraints, variables
 0 0 0 0 0	# common exprs: b,c,o,c1,o1
b
0 0 200
0 0 200
0 0 200
x3
0 1
1 1
2 1
r
2 10
2 2.66
C0
o0
o2
o5
v1
n2
v0
o2
n5
v1
C1
n0
O0 0
o2
n2
o5
v0
n2
k2
1
3
J0 3
0 0
1 0
2 3
J1 2
1 -1
2 1
G0 3
0 0
1 5
2 1
