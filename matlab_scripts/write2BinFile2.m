%% function checkOut = write2BinFile2(name,arr)
% This function is used to write a sparse matrix to bainary file.
% Since all the non-zero entries are equal to 1 the matrix is represented
% by pairs (i,j) such that arr(i,j) = 1
function checkOut = write2BinFile2(name,arr)
    
    % Find indexes of non zero elements
    [rows ,cols ,~] = find(arr);
    
    rows = rows -1;
    cols = cols -1;
    fileID = fopen(name,'w');
    
    %First write rows then collumns
    fwrite(fileID,rows,'int');
    fwrite(fileID,cols,'int');
    checkOut = fclose(fileID);
end