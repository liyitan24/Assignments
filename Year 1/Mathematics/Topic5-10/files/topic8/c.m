syms t
y=@(t)-1/4*cos(4*t);
T=vectorize(taylor(y(t),t,2, 'order', 100));
t=0:0.1:2;
p=eval(T);
plot(t, p)
xlabel('Time'); ylabel('Position')
print('eps/topic8_c.eps','-depsc')