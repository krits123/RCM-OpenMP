%% This script is used to test the resaults

clc
clear all
close all

A = loadArray('extraLarge3.mat');
p = readResaults('res_extraLarge3.bin',nnz(A));
getBandwith(A)
printArray(A)
printArray(A,p)
getBandwith(A,p)
tic; p = symrcm(A); toc
printArray(A,p)
getBandwith(A,p)