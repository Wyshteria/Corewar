.name "carry"
.comment "Carry tester"

# Setup
#	r1 = 0
#	r2 = 1
#	r3 = '1'
#	r4 = '0'
#	carry = 0
init:	ld %0, r1
		ld %1, r2
		ld %49, r3
		ld %48, r4

start:	lldi %:void, %5, r16
		zjmp %:end
void:
