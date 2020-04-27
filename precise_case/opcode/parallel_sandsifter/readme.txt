1. 配置
a). 依据guest里的CPU数目配置宏"TOTAL_PROCESSES"的大小，按经验一般配置成CPU数目减4可以全速跑，比如guest有64个CPU，我配置成了60.
b). 修改代码parallel_sandsifter/sandsifter/daemon/main.c:324中的"-P?"参数可以指定sandsifter测试带多少个前缀的指令，比如"-P2"就是测试带两个前缀的指令，最多可以是"-P4"，也就是最多可以测试带4个前缀的指令。

2. 编译
a). 编译capstone：
	cd parallel_sandsifter/capstone-4.0.1/
	./make.sh
	./make.sh install

b). 编译sandsifter：
	cd parallel_sandsifter/sandsifter/
	make clean;make
	注：因系统差异，如果编译不过可以把Makefile的第35行和第36行的注释调换一下子。
c). 编译daemon程序：
	cd parallel_sandsifter/sandsifter/daemon	
	make

3. 运行 
  cd parallel_sandsifter/sandsifter/daemon	
  ./start_test