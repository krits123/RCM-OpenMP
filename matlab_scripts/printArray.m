%% function printArray
%This function produces a spy plot for a Sparse matrix.If a premutation
%vector is given it plots the reorded array.
function printArray(arr,prem)


    if nargin > 1
    
        figure
        spy(arr(prem,prem));
        
    else
        
        figure 
        spy(arr);
    end




end