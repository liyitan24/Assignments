h=@height;
tau=@maxTime;
a=0.01; h0=0.30; theta=pi/4; g = 9.8;
tMax = tau(a,h0,theta, g)
heights = h(a,h0,theta, g, 0:tMax)
plot(0:tMax, heights);
xlabel('Time (s)'); ylabel('Height (m)');
print('eps/topic5_b.eps','-depsc')
%%
function tau = maxTime(a, h0, theta, g)
    tau = h0^(5/2)*( 2*tan(pi/2-theta)^2 )/( 5*a^2*sqrt(2*g) );
end
function h = height(a, h0, theta, g, t)
    h = ( h0^(5/2) - t*( 5*a^2*sqrt(2*g) )/( 2*tan(pi/2-theta)^2 ) ).^(2/5);
end