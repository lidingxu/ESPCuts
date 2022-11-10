g3 0 1 0	# problem ex7_2_4
 8 4 1 0 0	# vars, constraints, objectives, ranges, eqns
 4 1	# nonlinear constraints, objectives
 0 0	# network constraints: nonlinear, linear
 6 8 2	# nonlinear vars in constraints, objectives, both
 0 0 0 1	# linear network variables; functions; arith, flags
 0 0 0 0 0	# discrete variables: binary, integer, nonlinear (b,c,o)
 13 4	# nonzeros in Jacobian, gradients
 3 2	# max name lengths: constraints, variables
 0 0 0 0 0	# common exprs: b,c,o,c1,o1
b
0 .1 10
0 .1 10
0 .1 10
0 .1 10
0 .1 10
0 .1 10
0 .1 10
0 .1 10
x8
0 .1
1 .1
2 .1
3 .1
4 .1
5 .1
6 .1
7 .1
r
1 1
1 1
1 1
1 1
C0
o2
o2
n5.88e-2
v4
v0
C1
o2
o2
n5.88e-2
v5
v1
C2
o54
3
o3
o2
n4
v2
v4
o3
n2
o2
o5
v2
n.71
v4
o3
o2
n5.88e-2
v0
o5
v2
n1.3
C3
o54
3
o3
o2
n4
v3
v5
o3
n2
o2
o5
v3
n.71
v5
o2
o2
n5.88e-2
o5
v3
n1.3
v1
O0 0
o54
5
o3
o2
n.4
o5
v6
n.67
o5
v0
n.67
o3
o2
n.4
o5
v7
n.67
o5
v1
n.67
o16
v6
o16
v7
n10
k7
2
4
5
6
8
10
12
J0 3
0 0
4 0
6 .1
J1 4
1 0
5 0
6 .1
7 .1
J2 3
0 0
2 0
4 0
J3 3
1 0
3 0
5 0
G0 4
0 0
1 0
6 0
7 0
