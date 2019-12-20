.name "TOTO\n
working?"
.comment "nothing"

l2:  	sti r1, %:live, %1

live: live %1
	zjmp %:live
