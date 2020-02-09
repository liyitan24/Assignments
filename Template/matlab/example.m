figure,plot(x,y);
xlabel(''); ylabel(''); axis square
legend('', 'y=x', 'Location', 'best');
print('eps/example.eps','-depsc')