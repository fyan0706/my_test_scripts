#!/bin/bash

rm -f log_file_*;

for i in `seq 0 32 255`; 
do 
	n=$((i+31))
	j=`printf "%02X" $i`
	k=`printf "%02X" $n`
	echo "j=$j,k=$k"
	./injector -P1 -t -0 -z $j -i ${j}0000000000000000000000000000 -e ${k}FFFFFFFFFFFFFFFFFFFFFFFFFFFF >/dev/null &
	sleep 1;
	#echo "${j}0000000000000000000000000000,${k}FFFFFFFFFFFFFFFFFFFFFFFFFFFF"
done    

