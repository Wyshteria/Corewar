.name "test lldi"
.comment "just a basic lldi tester"

		lldi %:ldpos, %2, r1
s1p:	sti r1, %:s1p, %0
ldpos:	ld %2147483647, r2
s2p:	sti r2, %:s2p, %0
