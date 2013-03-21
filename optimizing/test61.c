/* Test a condition that results in no branches when compiled with -O2 */
/* 0000000000000000 <test61>:
   0:	83 ff 01             	cmp    $0x1,%edi
   3:	19 c0                	sbb    %eax,%eax
   5:	83 e0 df             	and    $0xffffffdf,%eax
   8:	83 c0 61             	add    $0x61,%eax
   b:	c3                   	retq 
 */
/* Suggest re-write it to:
   0000000000000000 <test61>:
   0:	             	cmp    $0x1,%edi	Node A
   1:	             	jb     4:		Node A
   2:	               	mov    0x61,%eax	Node B
   3:                   jmp    5:		Node B
   4:	             	mov    0x40,%eax	Node C
   5:	                retq 			Node D  (Due to join point)
 */

int test61 ( unsigned value );

int test61 ( unsigned value ) {
	int ret;
	if (value < 1)
		ret = 0x40;
	else
		ret = 0x61;
	return ret;
}

