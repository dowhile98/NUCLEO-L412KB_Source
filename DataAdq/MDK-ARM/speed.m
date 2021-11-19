%clear
close all
iptsetpref('ImshowBorder', 'tight')

FontSize=11;
FontName='Arial';

load('y1.dat')
%n = 0:3:length(y2)-1;
n = 0:50-1;
figure(1);
%stem(n*0.02,y1(n+1),'filled','k.');
plot(n*0.02,y(n+1))
hold on
plot(n*0.02,y(n+1),'*')
%axis([0 511 -1.1 1.1]);
lab=xlabel('tiempo');
title("VELOCIDAD ANGULAR rad/s")
set(lab,'FontName',FontName,'FontSize',FontSize);
lab=ylabel('w[n]');
set(lab,'FontName',FontName,'FontSize',FontSize);

