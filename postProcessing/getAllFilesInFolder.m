%GETALLFILESINFOLDER - Returns all non-hidden files in a given folder
%
% fname = getAllFilesInFolder(folderName) looks in the folder 'folderName'
% in the current directory and extracts all files in it. All files starting
% with a '.' are ignored. These are hidden files that are typicaly not of
% interest.
%
% fname is a cell array of the different file names in the folder. By
% default, the file names are returned in alphabetical order.
%
% Todd Karin
% 10/11/2013


function fname = getAllFilesInFolder(folderName)

finfo = dir(folderName);
j=1;

if length(finfo)>2

    for i=1:length(finfo)
        fnameCurr = finfo(i).name;
        if fnameCurr(1)~='.'
            % Extract the filename
            fname{j} = fnameCurr;
            j=j+1;
        end
    end

end