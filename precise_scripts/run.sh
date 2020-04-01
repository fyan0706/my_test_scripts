#/bin/bash

for file in `ls *.out`
do
	echo "now running $file"
	timeout 30 ./$file
	#./$file
	if [ $? -ne 0 ]
	then	
		echo "$file not run" >> not_run.txt
	fi
	sleep 30
	rm -rf $file
done

host_ip=${1:-192.168.38.60}
ssh root@${host_ip} "touch ~/done"
