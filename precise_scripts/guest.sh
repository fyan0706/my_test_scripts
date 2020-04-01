#! /usr/bin/bash

# author: YanFeng/yan_feng@tsinghua.com/9520385@qq.com

# description: this is the test script run on guest for the precise test.
#              including the following fuction:
        ### build guanhua's cases: 64/32/module
        ### run guanhua's cases
        ### run jiye's cases:run.sh

USEAGE()
{
	echo "*****************USEAGE****************"
	echo "USEAGE for this script:"
	echo ''
	echo "***************************************"
}

while getopts "d:t:h" arg
do
        case $arg in
		d)
		simd="$OPTARG"   # $OPTARG is the defaulf arg
		;;
		t)
		TIME="$OPTARG"   # $OPTARG is the defaulf arg
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

### build guanhua's cases: 64/32/module


### run guanhua's cases


### run jiye's cases:run.sh
tar jxvf ${simd}
simd_dir=binary
cp run.sh ${simd_dir}
cd ${simd_dir}
./run.sh   # maybe the pwd need be update



