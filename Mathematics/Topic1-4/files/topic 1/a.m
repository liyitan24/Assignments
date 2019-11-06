data = readmatrix('MMA I CW I Dataset.xlsx');
courseworkMarks = data(:,1);
examMarks = data(:,2);
figure,plot(examMarks,courseworkMarks, '*');
xlabel('Exam Marks'); ylabel('Coursework Marks')
axis square; axis ([0 100 0 100])
hold on; plot(0:100,0:100, '--');