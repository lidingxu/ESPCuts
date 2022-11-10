g3 0 1 0	# problem st_e33
 9 6 1 0 4	# vars, constraints, objectives, ranges, eqns
 3 0	# nonlinear constraints, objectives
 0 0	# network constraints: nonlinear, linear
 3 0 0	# nonlinear vars in constraints, objectives, both
 0 0 0 1	# linear network variables; functions; arith, flags
 0 0 0 0 0	# discrete variables: binary, integer, nonlinear (b,c,o)
 23 6	# nonzeros in Jacobian, gradients
 3 2	# max name lengths: constraints, variables
 0 0 0 0 0	# common exprs: b,c,o,c1,o1
b
0 0 100
0 0 200
0 1e-2 3e-2
0 0 300
0 0 300
0 0 100
0 0 300
0 0 100
0 0 200
x1
2 1e-2
r
4 0
1 0
1 0
4 0
4 0
4 0
C0
o16
o2
v2
o0
v0
v1
C1
o2
v2
v0
C2
o2
v2
v1
C3
n0
C4
n0
C5
n0
O0 0
n0
k8
4
8
11
13
15
17
19
21
J0 5
0 0
1 0
2 0
3 3e-2
4 1e-2
J1 4
0 0
2 0
5 -2.5e-2
6 2e-2
J2 4
1 0
2 0
7 2e-2
8 -1.5e-2
J3 4
0 -1
1 -1
3 1
4 1
J4 3
0 1
5 -1
6 1
J5 3
1 1
7 1
8 -1
G0 6
3 6
4 16
5 -9
6 10
7 10
8 -15
