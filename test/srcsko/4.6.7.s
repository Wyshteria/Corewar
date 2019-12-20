.name "something"
.comment "4"

:lol		sti r1, %:live, %1

live: live %+0
	zjmp %:lol

