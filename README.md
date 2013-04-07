##codeware  
========
convert.c:  
    This program is the tool for dealing with data
    which is geted from topmc-finegrained-trace-v3.
    The main effect is obvious by read the define.
========
choose_points.c  
    This program is a tool for choosing important points from simpoints3.2 output
=========
normalize.c  
    this program works for normalize the vectors which output by convert.c
==========
toolfortest.m  
    this matlab function file is a plot function for files outputed by convert.c
============
2013-03-23-scomplement.c  
test  
test.c  
test.debug  
test-O2.debug  
    char型求补码在32位系统里按照32位求补
    和两个objdump反汇编文件
============
check_tag_count.c  
    验证通过topmc-finegranted-trace-3.5在trace里面每隔2ms打的tag数量是否正确  
============
GetCfgContent.h  
    trace分割程序的头文件
============
trace_analyze_zhongbin-split-v3.c  
    最终的trace切割程序
============
run_simpoint.sh  
    一个运行simpoint的脚本
============
hello.c  
hello  
    学习Gnu AS
============
test_time.c  
	测试time.h头文件下的函数time()
============
alarm_test.c  
	测试alarm函数，用于后台计时

