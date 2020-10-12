clc;clear;
load('gold.mat', 'gold');
data=[0 1 1 1 1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0];
results=zeros(2);
for i = 1:30
    if(data(i) == 1 && gold(i) == 1)
        results(1,1) = results(1,1)+1;
    elseif(data(i) == 1 && gold(i)==0)
        results(1,2) = results(1,2)+1;
    elseif(data(i) == 0 && gold(i)==1)
        results(2,1) = results(2,1)+1;
    elseif(data(i) == 0 && gold(i)==0)
        results(2,2) = results(2,2)+1;
    end
end

sickPeople = numel(gold(gold==1));
healthyPeople = numel(gold(gold==0));