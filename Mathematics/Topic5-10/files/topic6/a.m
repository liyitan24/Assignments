syms h(t)
Dh = diff(h);
ode = diff(h,t,2) + 6*diff(h,t) + 25*h == 0;
conds = [Dh(0)==-0.05, h(0)==0.15];
hSol(t) = dsolve(ode,conds);
hSol=simplify(hSol)