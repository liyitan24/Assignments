syms t
a=0.01; h0=0.3; theta=pi/4; g=9.8;
tau= h0.^(5/2).*( 2.*tan(pi/2-theta).^2 )./( 5*a^2*sqrt(2*g) )
dhdt=@(t) 2/5*( h0.^(5/2)-t.*(h0^(5/2))./(tau) ).^(-3/5)*( (-h0.^(5/2))./(tau) );
dVdt=@(t) pi.*dhdt(t).*(h(t).*tan(pi/2-theta)).^2;
format long;
V=integral(dVdt,0,tau/2)
rsums(dVdt, [0,tau/2])