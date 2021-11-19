clear all,close all,clc

%% IDENTIFICACIÓN DEL SISTEMA
%% SOLO ES PARA IDENTIFICAR EL SISTEMA
%Cargar data
load('y1.dat')
%PERIODO DE MUESTREO
Ts=20e-3;
%OBTENER INFORMACIÓN DE LAS PRIMERAS M muestras
%TIEMPO DE INTERES
tM=1;
M=tM/Ts;
M=round(M);
y1=y1(1:M);
y1=filter(ones(1,4),1,y1)/4;
%-----SEÑAL DE CONTROL ESCALÓN (PRUEBAS HECHAS)
U=15.25;
ut=U*ones(M,1);
%-------RESPUESTA DEL SISTEMA
yt=y1;
%VECTOR TIEMPO DISCRETO
 n=0:M-1;
%VECTOR TIEMPO CONTINUO
 t=n*Ts;
 %---STEP
 plot(t,y1)
 grid on
 title('DATOS MEDIDOS')
 xlabel('t[seg]')
 ylabel('Amplitud')
 %---
data = iddata(yt,ut,Ts);
%Función Transfer  Estimation
%np=2
np=2;%Número de polos
%nz=2
nz=0;%Número de zeros
%FUNCIÓN DE TRANSFERENCIA DEL MOTOR DC 
TF1= tfest(data,np,nz);
b=TF1.Numerator;
 
a=TF1.Denominator;
figure
yb=1*step(TF1,t);
sistema=tf(b,a)
plot(t,yb)
title('DATOS MEDIDOS FILTRADOS')
xlabel('t[seg]')
ylabel('Amplitud')
grid on
%obtener el periodo de muestreo
%método del diagrama de bode
[aux wgc]=margin(sistema);
%Periodo de muestreo minimo en terminos
%del margen de ganancia del diagrama de bode
Tss_min=1/(20*wgc);
