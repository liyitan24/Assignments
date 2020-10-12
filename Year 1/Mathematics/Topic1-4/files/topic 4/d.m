R_infty = 1
R_0 = 10
tau = 1

omega=0.001:0.001:10^3
theta = omega*tau
figure, hold on;
for alpha = [0.25, 0.5, 0.75, 1]
    c=cos(alpha*pi/2)
    modZ = sqrt( ((R_infty)^2.*theta.^(2*alpha) + 2*c*R_0*R_infty.*theta.^alpha + (R_0)^2)./ (1+2*c*theta.^alpha + theta.^(2.*alpha)) )
    plot(log10(omega), modZ); 
end
xlabel('log_{10}(\omega) (Hz)'); ylabel('|Z| (\Omega)')
legend('\alpha = 0.25','\alpha = 0.5','\alpha = 0.75','\alpha = 1', 'Location','best')
print('eps/topic4_d.eps','-depsc')