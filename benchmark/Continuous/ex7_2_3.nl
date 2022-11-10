g3 0 1 0	# problem ex7_2_3
 8 6 1 0 0	# vars, constraints, objectives, ranges, eqns
 3 0	# nonlinear constraints, objectives
 0 0	# network constraints: nonlinear, linear
 8 0 0	# nonlinear vars in constraints, objectives, both
 0 0 0 1	# linear network variables; functions; arith, flags
 0 0 0 0 0	# discrete variables: binary, integer, nonlinear (b,c,o)
 17 3	# nonzeros in Jacobian, gradients
 3 2	# max name lengths: constraints, variables
 0 0 0 0 0	# common exprs: b,c,o,c1,o1
b
0 100 1e4
0 1e3 1e4
0 1e3 1e4
0 10 1e3
0 10 1e3
0 10 1e3
0 10 1e3
0 10 1e3
x8
0 100
1 1e3
2 1e3
3 10
4 10
5 10
6 10
7 10
r
1 1
1 1
1 1
1 1
1 1
1 1
C0
o54
3
o3
o3
o2
n833.33252
v3
v0
v5
o3
n100
v5
o16
o3
n83333.333
o2
v0
v5
C1
o54
3
o3
o3
o2
n1.25e3
v4
v1
v6
o3
v3
v6
o16
o3
o3
o2
n1.25e3
v3
v1
v6
C2
o54
3
o3
n1.25e6
o2
v2
v7
o3
v4
v7
o16
o3
o3
o2
n2.5e3
v4
v2
v7
C3
n0
C4
n0
C5
n0
O0 0
n0
k7
1
2
3
7
11
13
15
J0 3
0 0
3 0
5 0
J1 4
1 0
3 0
4 0
6 0
J2 3
2 0
4 0
7 0
J3 2
3 2.5e-3
5 2.5e-3
J4 3
3 -2.5e-3
4 2.5e-3
6 2.5e-3
J5 2
4 -1e-2
7 1e-2
G0 3
0 1
1 1
2 1
