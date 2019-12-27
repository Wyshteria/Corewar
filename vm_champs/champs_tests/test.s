	.name 		"testchamp"
	.comment "testing commands"

aff		r1
#test3:
#	lld		%:test3, r2
#	st		r2, 50
#	lld		-10, r2
#	st		r2, 50
#	lfork	%:test3
#	st		r10, r2
#	st		r1, 6
#	live	%-1
#	ld		-4, r2
#	and		r1, r2, r5
#	and		4, 8, r6
#	and		%30, %40, r7
#	st		r5, 6
#	live	%1
#	or		r5, r4, r6
#	or		%30, %40, r7
#	or		4, 8, r8
#	xor		r1, r2, r6
#	xor		%30, %40, r7
#	xor		4, 8, r8
#	xor		r1, r1, r10
#	zjmp	%:test
#	st		r2, 150
#	st		r3, 160
#	st		r4, 170
#	st		r6, 180
#	st		r7, 190

#test2:
#	st		r1, r2
#	live	%1
#	ld		10, r3
#	and		%-25, 10, r4
#	st		r4, 6
#	live	%1
#	or		10, %-5, r6
#	st		r2, 150
#	st		r3, 160
#	st		r4, 170
#	st		r6, 180
#	st		r7, 190
  #reste a tester toutes les fonctions apres zjmp	
