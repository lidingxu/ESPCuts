g3 0 1 0	# problem fuel
 15 15 1 0 6	# vars, constraints, objectives, ranges, eqns
 3 1	# nonlinear constraints, objectives
 0 0	# network constraints: nonlinear, linear
 3 6 0	# nonlinear vars in constraints, objectives, both
 0 0 0 1	# linear network variables; functions; arith, flags
 3 0 0 0 0	# discrete variables: binary, integer, nonlinear (b,c,o)
 35 3	# nonzeros in Jacobian, gradients
 3 3	# max name lengths: constraints, variables
 0 0 0 0 0	# common exprs: b,c,o,c1,o1
b
3
3
3
0 50 700
0 50 700
0 50 700
2 0
2 0
2 0
0 0 4e3
0 0 4e3
0 2e3 4e3
0 0 1
0 0 1
0 0 1
x7
0 100
1 100
2 100
3 50
4 50
5 50
11 2e3
r
4 0
4 0
4 0
2 0
2 0
2 0
1 0
1 0
1 0
4 3.5e3
4 500
4 500
2 400
2 900
2 700
C0
o16
o0
o2
n5e-3
o5
v0
n2
v0
C1
o16
o0
o2
n5e-3
o5
v1
n2
v1
C2
o16
o0
o2
n5e-3
o5
v2
n2
v2
C3
n0
C4
n0
C5
n0
C6
n0
C7
n0
C8
n0
C9
n0
C10
n0
C11
n0
C12
n0
C13
n0
C14
n0
O0 0
o54
7
o2
n2.5e-3
o5
v3
n2
o2
n6
v3
o2
n2.5e-3
o5
v4
n2
o2
n6
v4
o2
n2.5e-3
o5
v5
n2
o2
n6
v5
n900
k14
4
8
12
13
14
15
17
19
21
23
25
26
29
32
J0 3
0 0
6 1
12 -50
J1 3
1 0
7 1
13 -50
J2 3
2 0
8 1
14 -50
J3 2
0 1
12 -100
J4 2
1 1
13 -100
J5 2
2 1
14 -100
J6 2
0 1
12 -500
J7 2
1 1
13 -500
J8 2
2 1
14 -500
J9 2
6 1
9 1
J10 3
7 1
9 -1
10 1
J11 3
8 1
10 -1
11 1
J12 2
0 1
3 1
J13 2
1 1
4 1
J14 2
2 1
5 1
G0 3
3 0
4 0
5 0
