function [len, dots] = plant_a_array(file, n_sheet, range, step, x_cood, y_cood, name)
%plant_a_array Summary of this function goes here
%   Detailed explanation goes here
%   功能：从EXCEL文件中读取某一行/列数据，并将其画出二维图
%   输入：
%       file:EXCEL文件名
%       n_sheet:读取EXCEL文件的n_sheet号标签页内的数据
%       range:读取EXCEL文件指定范围内的数据
%           读取特定区域, 如:'A3:G20'，表示读取以A3和G20为两个顶角的矩形区域内的数据
%           读取特定行/列,如:'C:C',表示读取第C列的数据
%       step：步长
%       x_cood:x坐标名称
%       y_cood:y坐标名称
%       name:图的标题
%   输出：
%       length:数组a的长度
%       dots:图中共用到了多少个点
%   举例：
%       [length, dots] = plant_a_array('test.xls', 1, 'C:C', 1, 'x', 'y', 'test');

    %读取指定数据到数组A
    A = xlsread(file, n_sheet, range);
    %得到输出
    len = length(A);
    x = 1:step:len;
    y = A(1:step:len);
    dots = length(y);
    %画普通图
%     plot(x, y, 'b');
    %画散点图
    scatter(x, y, 'b.');
    %设置图片属性
%     set(gcf, 'visible', 'off');%不显示图片直接保存
%     set(gcf, 'visible', 'off', 'Position', [100 100 1000 500]);%将图片设置为从100*100开始，大小为1000*500
    set(gcf, 'visible', 'on', 'Position', [100 100 1000 500]);%将图片设置为从100*100开始，大小为1000*500
    %设置标题和坐标名称
    xlabel(x_cood);
    ylabel(y_cood);
    title(name);
    %保存图片
%     suffix = '.jpg';
%     pic_name = [file '-' name];
%     pic_name = strcat(pic_name, suffix);
%     print(gcf, '-djpeg', pic_name);
end

