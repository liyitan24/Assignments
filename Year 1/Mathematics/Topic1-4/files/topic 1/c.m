figure,plot(examMarks,courseworkMarks, '*');
xlabel('Exam Marks'); ylabel('Coursework Marks')
hold on;
axis square; axis ([0 100 0 100]);
p=polyfit(examMarks, courseworkMarks, 1); %Generate polynomial of best fit
xfit=0:100; yfit=polyval(p,xfit); %Line of best fit
plot(xfit,yfit)
plot(i,10+i.*1.08, '--'); %max slope
plot(i,13+i.*0.80, '--'); %min slope
legend('', 'matlab-calculated', 'y=1.08x+10', 'y=0.80x+13', 'Location', 'best')
hold off;