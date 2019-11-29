	.name 		"zork"
	.comment "just a basic living prog"
		#test comment
    l2:sti	r1,%:live, %-420
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
