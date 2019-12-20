.name "TOTO"
.comment "nothing"
.name "autre"

l2:  	sti r1, %:live, %1

live: live %1
	zjmp %:live
