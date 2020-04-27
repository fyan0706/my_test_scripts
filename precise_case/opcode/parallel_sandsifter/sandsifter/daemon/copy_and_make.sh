scp bhorse@192.168.30.193:/home/bhorse/source_code/cicada/sce/tool/opcode/parallel_sandsifter/sandsifter/daemon/* .
scp bhorse@192.168.30.193:/home/bhorse/source_code/cicada/sce/tool/opcode/parallel_sandsifter/sandsifter/injector.c ../
scp bhorse@192.168.30.193:/home/bhorse/source_code/cicada/sce/tool/opcode/parallel_sandsifter/sandsifter/circ_buf.h ../
cd ../;make clean;make;cd -;make clean;make
