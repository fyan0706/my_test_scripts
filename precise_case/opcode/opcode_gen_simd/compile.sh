#!/bin/sh


compile()
{
    if [ -z "$3" ]; then
        ls *.c | while read line
        do
            ${cc}  ${flags} ${line}  ../template/main.c ../template/sampling.c -I../template/  -o ${line}.out
        done
    else
        ${cc}  ${flags} $3  ../template/main.c ../template/sampling.c -I../template/   -o $3.out
    fi
}



flags=" -w -g -O0 "



gcc_flags= -w -g -msse  -msse2  -msse3  -mssse3  -msse4.1  -msse4.2  -msse4  -mavx -mavx2  -mavx512f -mavx512pf  -mavx512er  -mavx512cd  -mavx512vl -mavx512bw  -mavx512dq  -mavx512ifma -mavx512vbmi   -mxsavec  -mxsaves -msse4a   -mpopcnt  -mabm -mbmi  -mtbm  -mfma4  -mxop -mlzcnt  -mbmi2  -mfxsr  -mxsave  -mxsaveopt  -mrtm  -mlwp  -mmpx -mmwaitx  -mclzero  -mpku  -mthreads -mgfni  -mvaes -mshstk -mavx512vbmi2 -mvpclmulqdq -mavx512bitalg -mmovdiri -mmovdir64b -mavx512vpopcntdq



if [ -z "$1" ] ; then
    cc=gcc
    flags=${flags} ${gcc_flags}
    compile
else
    case $1 in
        gcc)
        cc=$1
        flags=${flags} $2
        compile
        ;;

        icc)
        cc=$1
        flags=${flags} $2
        compile
        ;;
        
        *)
        echo "illegal parameter" 
        exit
        ;;
    esac
fi





