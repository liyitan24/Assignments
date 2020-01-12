w=[0:1:100]'; t=0:0.1:2
plot(w, abs(eval(vectorize(Particular))));
xlabel('Angular displacement \omega'), ylabel('Height')
title('Each line is a distinct moment in time, t=0 to 3')