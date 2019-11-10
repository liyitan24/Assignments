figure,plot(examMarks,courseworkMarks, '*');
xlabel('Exam Marks'); ylabel('Coursework Marks')
axis square; axis ([0 100 0 100])
hold on; plot(0:100,0:100, '--'); hold off;
legend('', 'y=x', 'Location', 'best');
print('eps/topic1_a.eps','-depsc')