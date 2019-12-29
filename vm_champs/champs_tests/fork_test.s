.name "test fork"
.comment "just a basic fork tester"

		ld %48, r1
		fork %:disp
disp:	aff r1
		and %0, %0, r16
end:	zjmp %:end
