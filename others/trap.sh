##计算按键盘的速度
##

trap 'increment' 2
increment()
{
  #echo "Caught SIGINT ..."
  now=`date +%s%N`
  echo $now
  X=`expr ${X} + 5`
  if [ "${X}" -gt "200" ]
  then
    echo "Okay, I'll quit ..."
    exit 1
  fi
}

### main script
X=0
while :
do
  :
  #echo "X=$X"
  #X=`expr ${X} + 1`
  #echo `date`
done
