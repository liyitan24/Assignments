t=0:0.1:3
hVector = eval(vectorize(hSol))
plot(t, hVector)
xlabel('Time (s)'); ylabel('Height (m)')
print('eps/topic6_b.eps','-depsc')