%(i)

flow=[1460 1240 1230 1270 861 1355 612 822 1370 1380 ...
    810 735 259 1290 1125 528 622 468 664 717]
pd01_10=fitdist(flow(1:10)', 'Normal')
pd11_20=fitdist(flow(11:20)', 'Normal')
%%
%(ii)
paramci(pd01_10)
paramci(pd11_20)