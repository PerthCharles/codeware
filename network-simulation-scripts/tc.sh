#!/bin/bash

BUFSIZE=204800 # the default buffer size in router is 200KB
PKTSIZE=1540   # the default packet size

function usage()
{
    echo "usage:   $0 add|del rate delay loss burst"
    echo "example: $0 add 4mbit 20 0.1 10"
}

function tcdel()
{
    tc qdisc del dev eth0 root
    tc qdisc del dev eth1 root
}

function tcadd()
{
    delay=$(($2 / 2))
    burst=$(($4 * $PKTSIZE))  # burst(bytes) = burst-pkts * pkt-size"
    tc qdisc add dev eth0 root handle 1:0 tbf rate $1 burst $burst limit $BUFSIZE
    tc qdisc add dev eth0 parent 1:0 handle 10:0 netem delay ${delay}ms loss $3 limit $BUFSIZE
    tc qdisc add dev eth1 root netem delay ${delay}ms loss 0 limit $BUFSIZE
}

if [ "$1" = "add" ]
then
    if [ $# != 5 ]
    then
    usage; exit
    fi
    echo "adding rate=$2, delay=$3, loss=$4, burst=$5"
    tcadd $2 $3 $4 $5
elif [ "$1" = "del" ]
then
    echo "deleting..."
    tcdel
else
    usage
    exit
fi
