h=0.05; N=40; y=zeros(1,41); y(1)=-0.25;
t=0:h:2;
dy=@(t)sin(4*t);
for n=1:N
    y(n+1)=y(n)+h*dy(t(n));
end
y(end);