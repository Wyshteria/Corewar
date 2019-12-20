.name "TOTO"
	.comment "nothing" 	.name "test"

l2:  	sti r1, %:live, %1

live: live %1
	zjmp %:live
