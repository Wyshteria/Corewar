.comment ""
.name "01234567890123456789012345678901234567891		
#help
l2:	sti r1, %:live, %1
	and r1, %0, r1

live: live %1
	zjmp %:live
