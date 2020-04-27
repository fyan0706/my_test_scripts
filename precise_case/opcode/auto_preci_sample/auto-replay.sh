#!/bin/sh

exec_file=`cat files-name`

rm -fr /tmp/failed_snapshots/*

for current_file_name in $exec_file
do
	#echo $current_file_name
	expect<<-EOF 
	set timeout 50
	spawn /usr/bin/ssh root@192.168.122.100
	expect "*password*"
	send "ross\r"
	expect "*]#"
	send "cd /root/binary-test\r"
	expect "*binary-test*"
	send "./${current_file_name}\r"
	expect "*]#"
	send "rm -f ${current_file_name}\r"
	expect "*]#"
	send "exit\r"
	expect eof
	EOF
	current_id=`ls /tmp/failed_snapshots`
	if [ -n "${current_id}" ]; then
	# means there is snapshots existing in certain path
		sleep 3s
		/root/code/replay/bin/remu --mode mtr_offline --path /tmp/failed_snapshots/ --disasm on --inst-profile=on --id=${current_id##*dump_}
		sleep 7s
		echo "/tmp/failed_snapshots/${current_id}"
		rm -fr /tmp/failed_snapshots/${current_id}
		mv /tmp/failed_snapshots/*.ins /root/code/test-ins/
	fi
done


