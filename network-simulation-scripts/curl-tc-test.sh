#!/bin/bash

# Note
# The most time comsuming case, which rtt=250, loss=10, size=200MB, burst=5,
# will take about 4 hours to finish.
# Therefore, the cases for file size larger than 10MB will be separated.

emulator="221.168.10.12"
server="221.168.20.22"
path="" # the location of tc.sh in emulator
curl_fmt="%{time_connect}\t %{time_starttransfer}\t %{time_total}\t %{speed_download}\n"
speed="4mbit"

# Configuration for each case
# Case 1: Different RTTs only
function cfg-case1()
{
    size="50KB 100KB 250KB 1MB 10MB"
    rtt="20 50 100 200"
    burst="10"
    loss="0"
    repeat="1 2 3 4 5"
}

# Case 2: Different RTTs + loss rate
function cfg-case2()
{
    size="50KB 100KB 250KB 1MB 10MB"
    rtt="20 50 100 200"
    burst="10"
    loss="0.1 1 5"
    repeat="1 2 3 4 5 6 7 8"
}

# Case 3: Different RTTs + burst
function cfg-case3()
{
    size="50KB 100KB 250KB 1MB 10MB"
    rtt="20 50 100 200"
    burst="5 25 50 100"
    loss="0"
    repeat="1 2"
}

# Case 4: Different RTTs + burst + loss
function cfg-case4()
{
    size="50KB 100KB 250KB 1MB 10MB"
    rtt="20 50 100 200"
    burst="5 25 50"
    loss="0.1 1"
    repeat="1 2 3 4 5"
}

# Case 5: Large file: Different RTTs + burst + loss
function cfg-case5()
{
    size="50MB 200MB"
    rtt="20 50"
    burst="10 50"
    loss="0.1 1"
    repeat="1 2"
}


# You must reLoad the cfg before running cases
# Usage: run-cases CASE-NAME
function run-cases()
{
    echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" >> ${1}.log
    echo "++++++++ BEGIN $1  @ `date`  ++++++++" >> ${1}.log
    for data in $size; do
        for latency in $rtt; do
            for bst in $burst; do
                for drop in $loss; do
                    for i in $repeat; do
                        fmt="${1}\t $data\t $latency\t $bst\t $drop\t [$i]\t $curl_fmt"
                        ssh root@$emulator "cd $path; ./tc.sh add $speed $latency $drop $bst"
                        curl -s -w "$fmt" http://${server}/$data -o tmp >> ${1}.log
                        ssh root@$emulator "cd $path; ./tc.sh del"
                        sleep 3
                    done
                done
            done
        done
    done
}

echo "=====> start case 1"   |tee -a test.report
cfg-case1
(time run-cases case1) 2>&1  |tee -a test.report

echo "=====> start case 2"   |tee -a test.report
cfg-case2
(time run-cases case2) 2>&1  |tee -a test.report

echo "=====> start case 3"   |tee -a test.report
cfg-case3
(time run-cases case3) 2>&1  |tee -a test.report

echo "=====> start case 4"   |tee -a test.report
cfg-case4
(time run-cases case4) 2>&1  |tee -a test.report

echo "=====> start case 5"   |tee -a test.report
cfg-case5
(time run-cases case5) 2>&1  |tee -a test.report
