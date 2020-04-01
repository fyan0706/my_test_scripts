#! /usr/bin/bash

# author: YanFeng/yan_feng@tsinghua.com/9520385@qq.com

# description: this script is for running the precise test on guest 
# and statistic the result.
# this script need a guest IP: -g
#		     user: -u

USEAGE()
{
        echo "*****************USEAGE****************"
        echo "USEAGE for this script:"
        echo 'you should can ssh to the guest without passwd'
	echo 'this script need a guest IP: -g'
	echo '			     user: -u	default:root'
	echo ' the pwd for the simd cases: -p'
        echo "***************************************"
}



#guest_ip=${1:-192.168.38.72}
guest_ip="192.168.38.72"
user=root
while getopts "g:u:s:" arg
do
        case $arg in
                g)
                guest_ip="$OPTARG"   # $OPTARG is the defaulf arg
                ;;
                u)
                user="$OPTARG"   # $OPTARG is the defaulf arg
                ;;
		s)
                simd="$OPTARG"   # $OPTARG is the defaulf arg
                ;;
                h)
                USEAGE
                exit
                ;;
                *)
                echo "unkonw argument"
                exit
                ;;
        esac
done

### boot the guest	need not for DSC
#./start_qemu.sh
#sleep 180   ###maybe 180 is not ok.

ssh="ssh root@${guest_ip}"

### CTRL+C clear the host+guest
trap 'onCtrlC' INT
function onCtrlC () 
{
	echo 'Ctrl+C in process'
	${ssh} "rm -rf ~/guest.sh ~/run.sh ~/${simd}"
	rm -rf ${snapshots_dir}/result.log ${snapshots_dir}/result_num.log
	exit
}	

### cp the guest.sh to guest and confirm you can ssh to the guest without passwd
echo "### cp the files to guest."
scp guest.sh ${user}@${guest_ip}:~
if [ $? -ne 0 ]
then
	echo "please check if you can ssh to ${guest_ip} without passwd"
	exit 1
fi

scp run.sh ${user}@${guest_ip}:~
if [ $? -ne 0 ]
then
	echo "please check if you can ssh to ${guest_ip} without passwd"
	exit 1
fi

scp ${simd} ${user}@${guest_ip}:~
if [ $? -ne 0 ]
then
	echo "please check if you can ssh to ${guest_ip} without passwd"
	exit 1
fi

### scp guanhua & jiye's case to guest


### run the guest.sh on guest
	### build guanhua's cases: 64/32/module
	### run guanhua's cases
	### run jiye's cases:run.sh
echo "### run all the cases, this may take 2-3 days."
#                          ${ssh} "~/guest.sh -d ${simd}"
#                          sleep 30
#./check.sh > check.log &
#while [ 1 ]
#do
#	sleep 600
#	# check if the cases done on guest 
#	ls ~/done
#	if [ $? -eq 0 ]
#	then
#		break
#	fi 
#	# check if the guest dead
#	now=`tail -1 check.log`
#	repeat=`grep ${now} check.log|wc -l`
#	if [ ${repeat} -ge 5 ]
#	then
#		qemu_pid=`ps aux|grep qemu-system-x86_64|head -1|awk '{print $2}'` 
#		kill -9 ${qemu_pid}
#		sleep 60
#		### maybe there need mv the snapshot to a new folder
#		./start_qemu.sh
#	fi
#done

### cp the logs on guest to host


snapshots_dir="/data/failed_snapshots/"


### replay the snapshots: replay.sh
echo "### replay the snapshots, this may take several hours."
rm -rf replay_hang.log
touch replay_hang.log
rm -rf remu.log
touch remu.log
cd $snapshots_dir
start_num=`ls -l $snapshots_dir|grep dump|head -1|awk '{print $NF}'|awk -F_ '{print $2}'|sed -r 's/0*([0-9])/\1/'`
end_num=`ls -l $snapshots_dir|grep dump|tail -1|awk '{print $NF}'|awk -F_ '{print $2}'|sed -r 's/0*([0-9])/\1/'`
#for i in {1..${num}}
echo "num is ${start_num} ${end_num}"
for ((i=${start_num};i<=${end_num};++i))
do
        timeout 10 remu --mode mtr_offline --path $snapshots_dir --id $i --inst=on >> remu.log
        if [ $? -ne 0 ]
        then
                echo "$i replay hang" >> replay_hang.log
        fi
        echo "we just run $i dump file" >> remu.log
done

#cp replay.sh $snapshots_dir/
#$snapshots_dir/replay.sh

### analysis the coverage

### get the detailed result: analysis.sh
#Get the instrction coverage from the precise test cases.
#
#=======================================================
#Create the result.log		# the result log include all the opcode name here.
#
#while all the ins files
#	delete 1st and last line
#	delete the opcode name and :       awk : $2 > x.log
#	paste result.log + x.log
#	rm x.log		
#done
#
#not_covered = `cat result.log |grep -v [1-9]|wc -l`
#result = ${not_covered}/3001

#add：
#statistic the total num that each opcode was runned.
#add all the num in the same line.
#awk '{b[NR]=$0; for(i=2;i<=NF;i++)a[NR]+=$i;}END{for(i=1;i<=NR;i++) print b[i]"\t"a[i]}' inputfile
#https://www.cnblogs.com/paul8339/p/9054409.html
#======================================================
echo "### now calculate the coverage."
awk -F: '{print $1}' ${start_num}.cnt.ins > result_tmp.log #result_tmp.log only include the opcode name
sed -i '1d' result_tmp.log
sed -i '$d' result_tmp.log

ulimit -n 8192

for file in `ls *.cnt.ins`
do
	num=${file}.num
	awk -F: '{print $2}' ${file} > ${num}
	sed -i '1d' ${num}
	sed -i '$d' ${num}
	# paste result.log ${num} > result.log #can not get the needed result
done

paste result_tmp.log *.cnt.ins.num > result.log #result.log include the opcode and all the num
paste *.cnt.ins.num > result_num.log #result_num only include all the number
not_covered=`cat result_num.log |grep -v [1-9]|wc -l`
rm *.cnt.ins.num result_tmp.log
echo "${not_covered} instructions is not covered"
#coverage=`echo "scale=4; (3001-${not_covered})*100/3001"|bc`
coverage=`echo "scale=4; (2722-${not_covered}+279)*100/2722"|bc`
echo "coverage is ${coverage}%"

### create the list for if the opcode is covered: detailed.sh
echo "### now generate the detailed list of the coverage."
file=result_num.log
rm -rf detailed.log
touch detailed.log
cat $file|while read line
do
	#echo "line is ${line}"
	#if grep [1-9] ${line}	
	if echo ${line}|grep [1-9] > /dev/null
	then
		echo Yes >> detailed.log 
	else
		echo No >> detailed.log
	fi
done

cd
### then we need compare the 2 detailed result manually

### clear the host
echo "### clear the host and guest."
rm -rf ${snapshots_dir}/result.log ${snapshots_dir}/result_num.log

### clear the guest
${ssh} "rm -rf ~/guest.sh ~/run.sh ~/${simd}"

### handle the log
#time_stamp=`date +"%Y-%m-%d"`
time_stamp=`date +%s`
new_snapshots=/data/snapshots_${time_stamp}
new_ins=/data/ins_${time_stamp}
new_log=/data/log_${time_stamp}
mkdir ${new_snapshots} ${new_ins} ${new_log}
rm -rf ^dump*1$
mv ${snapshots_dir}/*.gz ${new_snapshots}
mv ${snapshots_dir}/*.ins ${new_ins}
mv ${snapshots_dir}/* ${new_log} 

echo "### done ###"
