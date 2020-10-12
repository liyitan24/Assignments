v=[20*cos(t); -20*sin(t); -2.*t./16]
speed=sqrt(sum(v.^2))
plot(t,speed)
xlabel('time (s)'),ylabel('speed (cms^{-1})')