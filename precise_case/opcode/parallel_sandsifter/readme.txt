1. ����
a). ����guest���CPU��Ŀ���ú�"TOTAL_PROCESSES"�Ĵ�С��������һ�����ó�CPU��Ŀ��4����ȫ���ܣ�����guest��64��CPU�������ó���60.
b). �޸Ĵ���parallel_sandsifter/sandsifter/daemon/main.c:324�е�"-P?"��������ָ��sandsifter���Դ����ٸ�ǰ׺��ָ�����"-P2"���ǲ��Դ�����ǰ׺��ָ���������"-P4"��Ҳ���������Բ��Դ�4��ǰ׺��ָ�

2. ����
a). ����capstone��
	cd parallel_sandsifter/capstone-4.0.1/
	./make.sh
	./make.sh install

b). ����sandsifter��
	cd parallel_sandsifter/sandsifter/
	make clean;make
	ע����ϵͳ���죬������벻�����԰�Makefile�ĵ�35�к͵�36�е�ע�͵���һ���ӡ�
c). ����daemon����
	cd parallel_sandsifter/sandsifter/daemon	
	make

3. ���� 
  cd parallel_sandsifter/sandsifter/daemon	
  ./start_test