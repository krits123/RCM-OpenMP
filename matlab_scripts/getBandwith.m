%% function bw = getBandwith(A,prem)
% This function is used to calculate the bandwith of sparse matrix.If a premutation 
% vector is given in the input the function returns the bandwith of the
% reorded array,
function bw = getBandwith(A,prem)

    if nargin > 1
        [i,j] = find(A(prem,prem));
        bw = max(i-j) +1;
    else
        [i,j] = find(A);
        bw = max(i-j) +1;
    end

end