###This shell is try to help myself to add explanation into readme for a new file 

FILE_LIST=`ls -1`
EXCLUDE='README.md'
WRITE='-r'
for a in $FILE_LIST
do 
  if [[ $a == $EXCLUDE ]]
  then
	continue
  fi
  #echo $a
  if grep -q $a README.md
  then
	continue
  else
	if [[ $1 == $WRITE ]]
	then
		echo ============ >> README.md
		echo $a >> README.md
	else
		echo $a
	fi
  fi
done
