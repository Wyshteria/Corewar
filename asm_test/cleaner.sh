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

