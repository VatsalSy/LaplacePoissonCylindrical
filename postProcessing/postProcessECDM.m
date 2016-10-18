clc
clear 
close all;
cycleIn = 1;
cycleEnd = 500;

for cycle = cycleIn:1:cycleEnd
tic;
filename = sprintf('outputRobin/cycle%03d.dat', cycle);
cellsize = getDomainSize(filename);
nNodeR = cellsize(1);
nNodeZ = cellsize(2);
[r,z,phi] = dataIn(filename);
phi = phi*273.15 + 273.15;
R = reshape(r,[nNodeR,nNodeZ]);
Z = reshape(z,[nNodeR,nNodeZ]);
PHI = reshape(phi,[nNodeR,nNodeZ]);

%% visualization
figure1 = figure('Visible','off','InvertHardcopy','off','Color',[1 1 1]);
colormap('jet');
axes1 = axes('Parent',figure1,'LineWidth',3,'BoxStyle','full','Layer','top',...
    'FontWeight','bold',...
    'FontSize',16,...
    'FontName','times');
box(axes1,'on');
hold(axes1,'on');
contourf(R,Z,PHI,'LineWidth',3)
contourf(-R,Z,PHI,'LineWidth',3)
xlabel('R (in m)','FontWeight','bold','FontSize',16,'FontName','times');
ylabel('Z (in m)','FontWeight','bold','FontSize',16,'FontName','times');
text = sprintf('Cycle = %03d', cycle);
title([text ': Contour of \Phi (K)'],'FontWeight','bold','FontSize',16,'FontName','times');
colorbar('peer',axes1);
axis square
destinationImage = sprintf('images/figure%03d.png', cycle);
saveas(gcf,destinationImage);
toc;
projection = ['Completed step ' num2str(cycle) ' of ' num2str(cycleEnd)];
display(projection)
end
fprintf('\n You job is finished.\n');