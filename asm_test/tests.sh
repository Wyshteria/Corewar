#!/bin/sh

path_to_test="./"
path_to_testok="./srcsok/"
path_to_testko="./srcsko/"
path_to_ft_asm="../"
path_to_asm="./"
#tester=$path_to_test"/test"
ft_asm=$path_to_ft_asm"asm"
asm=$path_to_asm"asm"
launcher_log=$path_to_test"launcher.log"

let "koTest = 0"
let "okTest = 0"
let "success = 0"
let "fail = 0"
let "invalid_error = 0"
let "invalid_dump = 0"
let "discarded = 0"
let "total = 0"

rm -f $launcher_log
#rm -f "$path_to_test/"*.s
rm -f "$path_to_testok"*.cor
rm -f "$path_to_testok"*.diff
rm -f "$path_to_testok"*.txt
rm -f "$path_to_testok"*.log
rm -f "$path_to_testko"*.log
rm -f "$path_to_testko"*.txt
rm -f "$path_to_testko"*.cor
rm -f "$path_to_testko"*.diff

#echo "\033[0;32m==Building $tester==\033[0m"	| tee	-a	$launcher_log
#make -C $path_to_test							>>			$launcher_log
echo "\n\033[0;32m==Building $ft_asm==\033[0m"	| tee	-a	$launcher_log
make -C $path_to_ft_asm fclean_asm asm			>>			$launcher_log
#if [ -x $tester ]
#then
	if [ -x $asm ]
	then
		if [ -x $ft_asm ]
		then
		echo "\033[0;34mProducing testing .s file\033[0m"
		#$tester >> $launcher_log
		allKo=`ls "$path_to_testko"`
		let "total = `ls $path_to_testko | wc -l`"
		for file in $allKo # Starting test with invalid syntax source files
		do
			let "koTest = $koTest + 1"
			$asm "$path_to_testko$file" >> $launcher_log
			cor=`echo $file | rev | cut -d'.' -f2- | rev`
			if [ -f "$path_to_testko$cor.cor" ]
			then
				mv $path_to_testko$file $path_to_testok$file
				let "discarded = $discarded + 1"
			else
				$asm "$path_to_testko$file" > "$path_to_testko$cor.txt"
				$ft_asm "$path_to_testko$file" >> $launcher_log
				$ft_asm "$path_to_testko$file" > "$path_to_testko$cor.my.txt"
				if [ -f "$path_to_testko$cor.cor" ]
				then
					let "fail = $fail + 1"
					hexdump -vC "$path_to_testko$cor.cor" > "$path_to_testko$cor.log"
				else
					diff "$path_to_testko$cor.txt" "$path_to_testko$cor.my.txt" > "$path_to_testko$cor.diff"
					if [ -s "$path_to_testko$cor.my.txt" ]
					then
						let "success = $success + 1"
						if [ -s "$path_to_testko$cor.diff" ]
						then
							let "invalid_error = $invalid_error + 1"
							cat "$path_to_testko$cor.my.txt">> $launcher_log
						fi
					else
						let "fail = $fail + 1"
						echo "$path_to_testko$cor\n"
					fi
					rm "$path_to_testko$cor.diff"
					rm "$path_to_testko$cor.my.txt"
					rm "$path_to_testko$cor.txt"			
				fi
			fi
			echo "\033[A\033[2K\033[0;36mkoTests: $koTest tests, $discarded discarded, $success success, $fail fails, $invalid_error invalid error\033[0m"
		done
		echo "\n\n"
		let "success = 0"
		let "fail = 0"
		let "discarded = 0"
		allOk=`ls "$path_to_testok"`
		let "total = `ls $path_to_testok | wc -l`"
		for file in $allOk # Starting test with valid syntax source files
		do
			let "okTest = $okTest + 1"
			$asm "$path_to_testok$file" >> $launcher_log
			cor=`echo $file | rev | cut -d'.' -f2- | rev`
			if [ -f "$path_to_testok$cor.cor" ]
			then
				hexdump -vC "$path_to_testok$cor.cor" > "$path_to_testok$cor.txt"
				rm -f "$path_to_testok$cor.cor"
				$ft_asm "$path_to_testok$file" >> $launcher_log
				if [ -f "$path_to_testok$cor.cor" ]
				then
					hexdump -vC "$path_to_testok$cor.cor" > "$path_to_testok$cor.my.txt"
					diff "$path_to_testok$cor.txt" "$path_to_testok$cor.my.txt" > "$path_to_testok$cor.diff"
					if [ -s "$path_to_testok$cor.diff" ]
					then
						let "invalid_dump = $invalid_dump + 1"
					else
						let "success = $success + 1"
						rm "$path_to_testok$cor.diff"
					fi
				else
					$ft_asm "$path_to_testok$file" > "$path_to_testok$cor.log"
					let "fail = $fail + 1"
				fi
			else
				#mv $path_to_testok$file $path_to_testko$file
				let "discarded = $discarded + 1"
			fi
			echo "\033[A\033[2K\033[0;36mokTests: $okTest tests, $discarded discarded, $success success, $fail fails, $invalid_dump invalid dumps\033[0m"
		done
		else
			echo "$ft_asm is not executable"
		fi
	else
		echo "$asm is not executable"
	fi
#else
	#echo "$test is not executable"
#fi
