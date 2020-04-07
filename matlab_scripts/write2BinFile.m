function checkOut = write2BinFile(name,arr)

    arr = full(arr);
    fileID = fopen(name,'w');
    
    fwrite(fileID,arr,'int');
    
    checkOut = fclose(fileID);
end

