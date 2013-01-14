function maxcol = toolfortest(filename,column)
%TOOLFORTEST is a tool function
%   usage:toolfortest(length,filename,column)
%       length: the length of x-axis
%       filename:the data is reading from this file
%       column:choose a column to be the y-axis

%data=importdata(filename);
load(filename);
length=size(data,1);
maxcol=max(data);
%maxresult=maxcol(column);
tmp=length-1;
x=0:1:tmp;
scatter(x,data(1:length,column),'.');
switch column
    case 1
        ylabel('Memory BandWidth(MB/s)');
    case 2
        ylabel('Read/Write');
    case 3
        ylabel('ROW Buffer Miss');
    case 4
        ylabel('L3 Miss Rate');
    case 5
        ylabel('Read Channel times');
    case 6
        ylabel('Write Channel times');
end
xlabel('Time(s)');
end

