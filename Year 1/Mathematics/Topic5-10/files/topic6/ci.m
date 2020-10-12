syms h(t) w
Dh = diff(h);
ode = diff(h,t,2) + 6*diff(h,t) + 25*h == 2.5*exp(i*w*t);
conds = [Dh(0)==-0.05 h(0)==0.15];
General=simplify(dsolve(ode))
Particular=simplify(dsolve(ode,conds))