.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %3
		and r1, %0, r2

live:	#live %1
		zjmp %:live
