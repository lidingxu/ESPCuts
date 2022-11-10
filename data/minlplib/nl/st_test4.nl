g3 0 1 0	# problem st_test4
 6 5 1 0 0	# vars, constraints, objectives, ranges, eqns
 0 1	# nonlinear constraints, objectives
 0 0	# network constraints: nonlinear, linear
 0 2 0	# nonlinear vars in constraints, objectives, both
 0 0 0 1	# linear network variables; functions; arith, flags
 2 2 0 0 2	# discrete variables: binary, integer, nonlinear (b,c,o)
 30 6	# nonzeros in Jacobian, gradients
 3 2	# max name lengths: constraints, variables
 0 0 0 0 0	# common exprs: b,c,o,c1,o1
b
0 0 1e15
0 0 2
0 0 1
0 0 1
0 0 1e15
0 0 1e15
r
1 16
1 -1
1 24
1 12
1 3
C0
n0
C1
n0
C2
n0
C3
n0
C4
n0
O0 0
o54
4
o2
o2
n.5
v0
v0
o2
n6.5
v0
o2
o2
n7
v1
v1
o16
v1
k5
5
10
15
20
25
J0 6
0 1
1 5
2 1
3 3
4 2
5 8
J1 6
0 -8
1 -1
2 2
3 4
4 -4
5 -2
J2 6
0 2
1 -4
2 -3
3 -1
4 .5
5 .2
J3 6
0 .2
1 2
2 -4
3 2
4 2
5 .1
J4 6
0 -.1
1 3
2 5
3 -5
4 -.5
5 2
G0 6
0 0
1 0
2 3
3 -2
4 -1
5 -2
