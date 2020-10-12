syms t
a=0.01; h0=0.30; theta=pi/4; g = 9.8;
tau = h0.^(5/2).*( 2.*tan(pi/2-theta).^2 )./( 5*a^2*sqrt(2*g) )
h=@(t) ( h0.^(5/2) - t.*( 5*a^2*sqrt(2*g) )./( 2.*tan(pi/2-theta).^2 ) ).^(2/5);
t = 0:0.1:tau;
plot(t, h(t));
xlabel('Time (s)'); ylabel('Height (m)');
print('eps/topic5_b.eps','-depsc')