H = [1, 0, 0; 0, 1, 0; 0, 0, 0];
f = [0; 0; 0];
A = [-3, -3, -1; -4, -3, -1; 1, 1, 1];
b = [-1; -1; -1];
[x, fval, exitflag, output, lambda] = quadprog(H, f, A, b)