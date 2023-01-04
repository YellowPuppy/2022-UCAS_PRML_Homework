H = [18, 10.5, -3; 10.5, 25, -3.5; -3, -3.5, 2];
f = [-1; -1; -1];
A = [-1, 0, 0; 0, -1, 0; 0, 0, -1];
b = [0; 0; 0];
A_eq = [1, 1, -1];
b_eq = [0];
[x, fval, exitflag, output, lambda] = quadprog(H, f, A, b, A_eq, b_eq)