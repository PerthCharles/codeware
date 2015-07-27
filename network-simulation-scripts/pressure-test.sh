#!/bin/bash

server="221.168.20.22"
time="60"

function netperf-cases()
{
    echo -e "\t\t\t\tSocket Size   Request Resp.  Elapsed Trans.   CPU    CPU    S.dem   S.dem"    >> netperf.log
    echo -e "\t\t\t\tSend   Recv   Size    Size   Time    Rate     local  remote local   remote"   >> netperf.log
    echo -e "\t\t\t\tbytes  bytes  bytes   bytes  secs.   per sec  %      %      us/Tr   us/Tr\n"  >> netperf.log

    for class in TCP_RR TCP_CRR UDP_RR; do
        for req in 32, 1024, 10240; do
            for rsp in 32, 1024, 10240; do
                for i in 1; do
                    echo -n -e  "$class\t $req\t $rsp\t [$i]\t" >> netperf.log
                    netperf -H $server -l $time -t $class -c -C -- -r $req $rsp |tail -n 2 | head -n 1 >> netperf.log
                done
            done
        done
    done
}

function http_load-cases()
{
    echo -e "\n\n##### Test random small files" >> http_load.log
    for usr in 50 100 500 1000; do
        for i in 1 2 3; do
            echo -e "#usr=$usr [$i]" >> http_load.log
            http_load -p $usr -s $time taobao.url >> http_load.log
            sleep 3
        done
    done

    echo -e "\n\n##### Test large file" >> http_load.log
    for qps in 50 100 200; do
        for i in 1 2 3; do
            echo -e "#qps=$qps [$i]" >> http_load.log
            http_load -r $qps -s $time 1MB.url >> http_load.log
            sleep 3
        done
    done
}

netperf-cases
http_load-cases
