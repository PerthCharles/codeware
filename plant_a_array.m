function [len, dots] = plant_a_array(file, n_sheet, range, step, x_cood, y_cood, name)
%plant_a_array Summary of this function goes here
%   Detailed explanation goes here
%   ���ܣ���EXCEL�ļ��ж�ȡĳһ��/�����ݣ������仭����άͼ
%   ���룺
%       file:EXCEL�ļ���
%       n_sheet:��ȡEXCEL�ļ���n_sheet�ű�ǩҳ�ڵ�����
%       range:��ȡEXCEL�ļ�ָ����Χ�ڵ�����
%           ��ȡ�ض�����, ��:'A3:G20'����ʾ��ȡ��A3��G20Ϊ�������ǵľ��������ڵ�����
%           ��ȡ�ض���/��,��:'C:C',��ʾ��ȡ��C�е�����
%       step������
%       x_cood:x��������
%       y_cood:y��������
%       name:ͼ�ı���
%   �����
%       length:����a�ĳ���
%       dots:ͼ�й��õ��˶��ٸ���
%   ������
%       [length, dots] = plant_a_array('test.xls', 1, 'C:C', 1, 'x', 'y', 'test');

    %��ȡָ�����ݵ�����A
    A = xlsread(file, n_sheet, range);
    %�õ����
    len = length(A);
    x = 1:step:len;
    y = A(1:step:len);
    dots = length(y);
    %����ͨͼ
%     plot(x, y, 'b');
    %��ɢ��ͼ
    scatter(x, y, 'b.');
    %����ͼƬ����
%     set(gcf, 'visible', 'off');%����ʾͼƬֱ�ӱ���
%     set(gcf, 'visible', 'off', 'Position', [100 100 1000 500]);%��ͼƬ����Ϊ��100*100��ʼ����СΪ1000*500
    set(gcf, 'visible', 'on', 'Position', [100 100 1000 500]);%��ͼƬ����Ϊ��100*100��ʼ����СΪ1000*500
    %���ñ������������
    xlabel(x_cood);
    ylabel(y_cood);
    title(name);
    %����ͼƬ
%     suffix = '.jpg';
%     pic_name = [file '-' name];
%     pic_name = strcat(pic_name, suffix);
%     print(gcf, '-djpeg', pic_name);
end

