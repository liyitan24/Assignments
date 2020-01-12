syms t
y=@(t)-1/4*cos(4*t); %Define function
T=vectorize(taylor(y(t),t,2)); %Create taylor polynomial as a matlab expression
t=[0:0.1:2];
p=eval(T);
p(end)