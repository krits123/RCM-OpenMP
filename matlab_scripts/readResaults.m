%% function p = readResaults(name,n)
% This function is used to read a premutation vector produced by our
% implementation of rcm algorithm.
function p = readResaults(name,n)

    fid = fopen(name);
    % Increment each entrie by one since matlab is not 0-based indexed
    p = fread(fid,n,'int') + 1;
    
    
    fclose(fid);
    
    
end