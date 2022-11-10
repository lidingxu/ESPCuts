g3 0 1 0	# problem ex3_1_1
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
0 579.19
1 1360.13
2 5109.92
3 182.01
4 295.6
5 217.99
6 286.4
7 395.6
r
1 83333.333
1 0
1 -1.25e6
1 1
1 1
1 1
C0
o1
o2
n100
v0
o2
v0
v5
C1
o54
3
o2
v1
v3
o16
o2
v1
v6
o2
n-1.25e3
v3
C2
o54
3
o2
v2
v4
o16
o2
v2
v7
o2
n-2.5e3
v4
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
3 833.33252
5 0
J1 4
1 0
3 0
4 1.25e3
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
