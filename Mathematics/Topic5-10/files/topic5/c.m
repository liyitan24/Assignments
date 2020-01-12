theta = linspace(pi/16, 7*pi/16,200);
h0=[0.30; 0.40];
tau= h0.^(5/2).*( 2.*tan(pi/2-theta).^2 )./( 5*a^2*sqrt(2*g) )
plot(theta, tau(1,:)); hold on;
plot(theta, tau(2,:));
xlabel('Angle \theta (Rad)'); ylabel('Max. time \tau (s)');
legend('h_0 = 0.30', 'h_0 = 0.40')
print('eps/topic5_c.eps','-depsc')