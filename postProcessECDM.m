clc
clear 
close
for cycle = 0:1:0
filename = sprintf('output/cycle%03d.dat', cycle);
cellsize = getDomainSize(filename);
nNodeR = cellsize(1);
nNodeZ = cellsize(2);
[r,z,phi] = dataIn(filename);
end