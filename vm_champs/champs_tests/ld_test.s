.name "test ld"
.comment "just a basic ld tester"

		ld 14, r1
s1p:	sti r1, %:s1p, %0
ldpos:	ld %2147483647, r2
s2p:	sti r2, %:s2p, %0
