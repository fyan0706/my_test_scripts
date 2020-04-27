import re
import sys
import os

def exist_in_file(f, c):
    f.seek(0)
    for eachline in f:
	if eachline.find(c) != -1:
	    return True
    return False

def list_all_files(root_dir):
    files = []
    list = os.listdir(root_dir)
    for i in range(0, len(list)):
	path = os.path.join(root_dir, list[i])
	if os.path.isdir(path):
	    files.extend(list_all_files(path))
	else:
	    files.append(path)
    return files


def main(argv = None):
    if argv is None:
        argv = sys.argv

    lines = 0
    opcode_cnt = 0
    covered_opcode = 0
    opcode_available = 0
    unsupported = 0
    file_cnt = 0
    file_list = []

    #f1 = open(argv[2], 'r')
    #print file_cnt
    f2 = open(argv[1], 'r')
    
    file_name_list = list_all_files(argv[2])
    inst_cnt_dict = {}
    
    for eachfile in file_name_list:
	f1 = open(eachfile)
        for eachline in f1:
	    #print eachline
            match_obj = re.match('(.*):(.*)', eachline, re.M | re.I)
	
            if match_obj != None:
	        opcode = match_obj.group(1)
	        ins_cnt = int(match_obj.group(2))

		if inst_cnt_dict.has_key(opcode) == True:
		    inst_cnt_dict[opcode] += ins_cnt
		else:
		    inst_cnt_dict[opcode] = ins_cnt

        

    for i in inst_cnt_dict.keys():
         #print i
         #print inst_cnt_dict[i]
         if exist_in_file(f2, i) == True:
	    opcode_cnt += 1
	    if inst_cnt_dict[i] != 0:
	        covered_opcode += 1
	    else:
		print i
	 else:
	     unsupported += 1
    
    print "opcodes = {0}, covered ins = {1}, coverage = {2}% unsupported = {3}".format(opcode_cnt, covered_opcode, covered_opcode * 100 / opcode_cnt, unsupported)
    return 0

if __name__ == "__main__":
    sys.exit(main())
