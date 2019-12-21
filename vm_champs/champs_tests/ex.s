	.name 		"zork"
	.comment "just a basic living prog"
		#test comment
    l2:live	%1
    l2:sti	r98,%:live, %-420
    l2:sti	r97,%:live, %-420
    l2:sti	r96,%:live, %-420
    l2:sti	r95,%:live, %-420
    l2:sti	r94,%:live, %-420
    l2:sti	r93,%:live, %-420
    l2:sti	r92,%:live, %-420
    l2:sti	r91,%:live, %-420
    l2:sti	r90,%:live, %-420
    l2:sti	r89,%:live, %-420
    l2:sti	r88,%:live, %-420
    l2:sti	r87,%:live, %-420
    l2:sti	r86,%:live, %-420
    l2:sti	r85,%:live, %-420
    l2:sti	r84,%:live, %-420
    l2:sti	r89,%:live, %-420
    l2:sti	r89,%:live, %-420
    l2:sti	r89,%:live, %-420
    l2:sti	r83,%:live, %-420
    l2:sti	r82,%:live, %-420
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
