clear;clc;
data=zeros(30,1); time=zeros(30,1);
for i = 1:30
    [data{i}, time{i}] = ECG_prac(i);
    plot(time{i}, data{i}(:,1));
    print(['./plots/patient_' num2str(i) '.eps'], '-depsc');
end