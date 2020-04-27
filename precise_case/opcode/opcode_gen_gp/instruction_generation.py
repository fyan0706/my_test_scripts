import re
import sys
import os

def generate_oprand(a, b, c):
    if (a == None):
        return ''
    elif (a == 'Ap'):
        return '(%rdi)'
    elif (a == 'Eb'):
        return '%bl'
    elif (a == 'Ew'):
        return '%bx'
    elif (a == 'Ed'):
        return '%ebx'
    elif (a == 'Eq'):
        return '%rbx'
    elif (a == 'Ep'):
        return '%rbx'
    elif (a == 'Ebd'):
        return '%rbx'
    elif (a == 'Ewd'):
        return '%rbx'
    elif (a == 'Fq'):
        return '%rbx'
    elif (a == 'Gb'):
        return '%bl'
    elif (a == 'Gw'):
        return '%bx'
    elif (a == 'Gd'):
        return '%ebx'
    elif (a == 'Gq'):
        return '%rbx'
    elif (a == 'Rb'):
        return '%bl'
    elif (a == 'Rw'):
        return '%bx'
    elif (a == 'Rd'):
        return '%ebx'
    elif (a == 'Rq'):
        return '%rbx'
    elif (a == 'Ib'):
        return '$0x70'
    elif (a == 'Iw'):
        return '$0x7000'
    elif (a == 'Id'):
        return '$0x70000000'
    elif (a == 'Iq'):
        return '$0x7000000000000000'
    elif (a == 'AL'):
        return '%al'
    elif (a == 'AX'):
        return '%ax'
    elif (a == 'RX'):
        return '%bx'
    elif (a == 'EAX'):
        return '%eax'
    elif (a == 'RAX'):
        return '%rax'
    elif (a == 'DX'):
        return '%dx'
    elif (a == 'CR0'):
        return '%cr0'
    elif (a == 'CR2'):
        return '%cr2'
    elif (a == 'CR3'):
        return '%cr3'
    elif (a == 'CR4'):
        return '%cr4'
    elif (a == 'Yb'):
        return ''
    elif (a == 'Xb'):
        return ''
    elif (a == 'Yw'):
        return ''
    elif (a == 'Xw'):
        return ''
    elif (a == 'Yd'):
        return ''
    elif (a == 'Xd'):
        return ''
    elif (a == 'Yq'):
        return ''
    elif (a == 'Xq'):
        return ''
    elif (a == 'Sw'):
        return ''
    elif (a == 'Dd'):
        return '%db0'
    elif (a == 'Dq'):
        return '%db0'
    elif (a == 'Jb'):
        return '{!s}_{!s} \\n\\t {!s}_{!s}:\\n\\t'.format(b, a, b, a)
    elif (a == 'Jw'):
        return '{!s}_{!s} \\n\\t {!s}_{!s}:\\n\\t'.format(b, a, b, a)
    elif (a == 'Jd'):
        return '{!s}_{!s} \\n\\t {!s}_{!s}:\\n\\t'.format(b, a, b, a)
    elif (a == 'Jq'):
        return '{!s}_{!s} \\n\\t {!s}_{!s}:\\n\\t'.format(b, a, b, a)
    elif (a[0] == 'M'):
        return '(%rsi)'
    elif (a == 'Fd'):
        return ''
    elif (a == 'Fw'):
        return ''
    elif (a == 'Ob'):
        return '%ds:(0x0000)'
    elif (a == 'Ow'):
        return '%ds:(0x0000)'
    elif (a == 'Od'):
        return '%ds:(0x0000)'
    elif (a == 'Oq'):
        return '%ds:(0x0000)'
    elif (a[0] == 'P' or a[0] == 'V' or a[0] == 'H' or a[0] == 'N' or a[0] == 'W'):
	if b != None and b.find('Kmask') != -1:
	    if c == 64:
	        return '%mm0'
	    elif c == 128:
	        return '%xmm0{%k1}'
	    elif c == 256:
	        if (a[1:3] == 'ps' or a[1:3] == 'pd' or a[1:3] == 'dq'):
	            return '%ymm0{%k1}'
	        elif (a[1:3] == 'ss' or a[1:3] == 'sd'):
		    return '%xmm0{%k1}'
		else:
		    return '(%rdi)'
            elif c == 512:
	        if (a[1:3] == 'ps' or a[1:3] == 'pd' or a[1:3] == 'dq'):
	            return '%zmm0{%k1}'
	        elif (a[1:3] == 'ss' or a[1:3] == 'sd'):
		    return '%xmm0{%k1}' 
		else:
		    return '(%rdi)'
	
        if c == 64:
	    return '%mm0'
	elif c == 128:
	    return '%xmm0'
	elif c == 256:
	    if (a[1:3] == 'ps' or a[1:3] == 'pd' or a[1:3] == 'dq'):
	        return '%ymm0'
	    elif (a[1:3] == 'ss' or a[1:3] == 'sd'):
		return '%xmm0'
	    else:
		return '(%rdi)'
        elif c == 512:
	    if (a[1:3] == 'ps' or a[1:3] == 'pd' or a[1:3] == 'dq'):
	        return '%zmm0'
	    elif (a[1:3] == 'ss' or a[1:3] == 'sd'):
		return '%xmm0' 
	    else:
		return '(%rdi)'

    elif (a[0] == 'Q'):
        return '(%rdi)'
    elif (a[0] == 'U'):
        if c == 64:
	    return '%mm0'
	elif c == 128:
	    return '%xmm0'
	elif c == 256:
	    return '%ymm0'
        elif c == 512:
	    return '%zmm0'
    elif (a == 'K'):
	return '%k5'
    elif (a == 'Bd'):
        return '%ebx'
    elif (a == 'Bq'):
        return '%rbx'
    elif (a == 'Op16'):
        return ''
    elif (a == 'Op32'):
        return ''
    elif (a == 'Op64'):
        return ''
    elif (a == 'Op'):
        return ''
    elif (a == '16'):
        return ''
    elif (a == '32'):
        return ''
    elif (a == '64'):
        return ''
    elif (a == 'SINGLE'):
        return '(%rsi)'
    elif (a == 'DOUBLE'):
        return '(%rsi)'
    elif (a == 'EXTENDED'):
        return '(%rsi)'
    elif (a == 'WORD'):
        return '(%rsi)'
    elif (a == 'DWORD'):
        return '(%rsi)'
    elif (a == 'QWORD'):
        return '(%rsi)'
    elif (a == 'PACKED'):
        return '(%rsi)'
    elif (a == 'ST0'):
        return '%st'
    elif (a == 'STi'):
        return '%st(1)'
    elif (a == 'STj'):
        return '%st(2)'
    else:
        return 'mismatch'

def process_oprand(oprand):
    src1 = None
    src2 = None
    src3 = None
    dst = None
    kmask = 0
    num = 0
    oprand_size = 128
    oprand_size_str = None

    #print oprand

    if oprand != '':
	oprand = re.sub('(K[A-Z]{1}[a-z]{1})', 'K', oprand)

    if oprand != '':
	oprand_size_str = re.findall('({.*})', oprand)
        if len(oprand_size_str) != 0:
            #print oprand_size_str[0]
	    if oprand_size_str[0] == '{128}':
                oprand_size = 128
            if oprand_size_str[0] == '{256}':
                oprand_size = 256
            if oprand_size_str[0] == '{512}':
                oprand_size = 512

    if oprand != '':
    	match_arr = re.findall('([A-Z]{1}[a-z]{0,2})', oprand)
    	if match_arr == None:
	    return {"num":num, "src1":src1, "src2":src2, "src3":src3, "dst":dst, "len":oprand_size}
    else:
	return {"num":num, "src1":src1, "src2":src2, "src3":src3, "dst":dst, "len":oprand_size}
        #print len(match_obj)
        #print "####################"
        #print oprand
        #print len(match_arr)
    if oprand.find('VSib') != -1:
	if oprand.find('VSib') == 0:
	    return {"num":2, "src1":oprand[4:7], "src2":src2, "src3":src3, "dst":'P', "len":oprand_size}
	else:
	    return {"num":2, "src1":'P', "src2":src2, "src3":src3, "dst":oprand[0:3], "len":oprand_size}

    if oprand.find('Kmask') != -1:
        kmask = 1
    if len(oprand) == 4:
	num = 2
        dst = oprand[0:2]
        src1 = oprand[2:4]
        if oprand[0] == 'X' or oprand[0] == 'Y':
            dst = None
	    num -= 1
        if oprand[2] == 'X' or oprand[2] == 'Y':
            src1 = None
	    num -= 1
    elif len(oprand) == 5:
        num = 2
        if oprand[1] == 'A' or oprand[0:2] == 'CR':
            dst = oprand[0:3]
            src1 = oprand[3:5]
	elif oprand[3] == 'A' or oprand[2:4] == 'CR':
	    dst = oprand[0:2]
            src1 = oprand[2:6]
        else:
            src1 = match_arr[1]
	    dst = match_arr[0]
    else:
	if len(match_arr) == 1:
	    src1 = match_arr[0]
	    num = 1
        elif len(match_arr) == 2:
	    src1 = match_arr[1]
	    dst = match_arr[0]
	    num = 2

	elif len(match_arr) == 3:
	    src2 = match_arr[2]
	    src1 = match_arr[1]
	    dst = match_arr[0]
	    num = 3

	elif len(match_arr) == 4 or len(match_arr) == 5:
	    src3 = match_arr[3]
	    src2 = match_arr[2]
	    src1 = match_arr[1]
	    dst = match_arr[0]

	    num = 4
	else:
	    num = 0

    return {"num":num, "src1":src1, "src2":src2, "src3":src3, "dst":dst, "len":oprand_size}

def process_oprand_fpu(oprand1, oprand2):
    src1 = None
    src2 = None
    src3 = None
    dst = None
    num = 2
    if oprand2 == 'REAL':
        dst = None
        src1 = oprand1
    elif oprand2 == 'INTEGER':
        dst = None
        src1 = oprand1
    elif oprand2 == 'BCD':
        dst = None
        src1 = oprand1
    else:
        dst = oprand1
        src1 = oprand2
    return {"num":num, "src1":src1, "src2":src2, "src3":src3, "dst":dst, "len":128}


def main(argv=None):
    if argv is None:
        argv = sys.argv

    mismatch = 0

    f = open(argv[1], 'r')
    for eachline in f:
	opcode = None
	oprand = None
	oprand_e = None
	prefix = None
	suffix = None
	oprand_dict = None
	comment = None
        match_obj = re.match('BX_IA(_.*),(.*),(.*),(.*),(.*),(.*),', eachline, re.M | re.I)
        if match_obj != None:
	    comment = match_obj.group(2)
            match_arr = re.findall("_([A-Z0-9a-z]*)",match_obj.group(1))
	    if len(match_arr) == 1:
		opcode = match_arr[0]
		oprand = ''
		#disasm = 'asm("{!s}");'.format(match_arr[0].lower())
                #print match_obj.group(1)
            elif len(match_arr) == 2:
		opcode = match_arr[0].lower()
		oprand = match_arr[1]
		#print oprand
	    elif len(match_arr) == 3:
		#print eachline
		if match_arr[2] == 'INTEGER' or match_arr[2] == 'REAL' or match_arr[2] == 'BCD':
		    opcode = match_arr[0].lower()
		    oprand = 'M'
		elif match_arr[0] == 'REP':
		    opcode = match_arr[0].lower() + ' ' + match_arr[1].lower()
		    oprand = match_arr[2]
		elif match_arr[0] == 'V128' or match_arr[0] == 'V256' or match_arr[0] == 'V512':
		    #print "###333##{!s}".format(eachline)
		    opcode = match_arr[1].lower()
		    oprand = match_arr[2] + '{' + match_arr[0][1:4] + '}'
		else:
		    if match_arr[1][0:2] == 'Op':
			opcode = match_arr[0]
			oprand = match_arr[2]
		    else:
			opcode = match_arr[0]
			oprand = match_arr[1]
			oprand_e = match_arr[2]
	    elif len(match_arr) == 4:
		if match_arr[0] == 'V128' or match_arr[0] == 'V256' or match_arr[0] == 'V512':
		    #print "###444##{!s}".format(eachline)
		    suffix = match_arr[3]
		    opcode = match_arr[1].lower()
		    oprand = match_arr[2] + '{' + match_arr[0][1:4] + '}'
		    #print oprand

	    if oprand[0:2] != 'ST':
	        oprand_dict = process_oprand(oprand)
	    else:
		oprand_dict = process_oprand_fpu(oprand, oprand_e)

	    if oprand_dict['num'] == 0:
		disasm = 'asm("{!s}");'.format(opcode.lower())
	    elif oprand_dict['num'] == 1:
		disasm = 'asm("{!s} {!s}");'.format(opcode.lower(), generate_oprand(oprand_dict["src1"], opcode, oprand_dict["len"]))
	    elif oprand_dict['num'] == 2:
		disasm = 'asm("{!s} {!s}, {!s}");'.format(opcode.lower(), generate_oprand(oprand_dict["src1"], opcode, oprand_dict["len"]), generate_oprand(oprand_dict["dst"], suffix, oprand_dict["len"]))
	    elif oprand_dict['num'] == 3:
		disasm = 'asm("{!s} {!s}, {!s}, {!s}");'.format(opcode.lower(), generate_oprand(oprand_dict["src2"], opcode, oprand_dict["len"]), generate_oprand(oprand_dict["src1"], "", oprand_dict["len"]), generate_oprand(oprand_dict["dst"], suffix, oprand_dict["len"]))
	    elif oprand_dict['num'] == 4:
            	disasm = 'asm("{!s} {!s}, {!s}, {!s}, {!s}");'.format(opcode.lower(), generate_oprand(oprand_dict["src3"], opcode, oprand_dict["len"]), generate_oprand(oprand_dict["src2"], "", oprand_dict["len"]), generate_oprand(oprand_dict["src1"], "", oprand_dict["len"]), generate_oprand(oprand_dict["dst"], suffix, oprand_dict["len"]))

	    if disasm.find('mismatch') != -1:
                mismatch += 1
                print "//" + disasm
		#print "//" + oprand_dict
		print "//" + eachline
	    else:
		#print eachline
		#print oprand_dict
		print disasm + ' \t//' + comment + '\t' + match_obj.group(1)
    print "// mismatch = {}".format(mismatch)
    return 0

if __name__ == "__main__":
    sys.exit(main())
