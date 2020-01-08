theta = linspace(pi/16, 7*pi/16,200);
h0=[0.30; 0.40];
tMax=tau(a,h0, theta, g)
plot(theta, tMax(1,:)); hold on;
plot(theta, tMax(2,:));
xlabel('Angle \theta (Rad)'); ylabel('Max. time \tau (s)');
legend('h_0 = 0.30', 'h_0 = 0.40')
print('eps/topic5_c.eps','-depsc')