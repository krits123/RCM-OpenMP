%% function A = loadArray(name)
% This function is used to read a sparse matrix file downloaded from a
% collection.The file is in '.mat' form.
function A = loadArray(name)

    load(name);
    
    
    A = Problem.A;
    
    % Make sure matrix is symmetric
    A = A + A'; 
    
    A = spones(A);
    
    
end