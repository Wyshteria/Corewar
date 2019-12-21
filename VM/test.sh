VM_PATH=../vm_champs/corewar
MY_VM_PATH=./vm

CHAMP_PATH=../vm_champs/

CHAMP1="${CHAMP_PATH}champs_tests/Backward.cor"
CHAMP2="${CHAMP_PATH}champs_tests/Backward.cor"

MY_ARGS=""
I=0;

for var in "$@"
do
	if [ i != 0 ]
	then
		MY_ARGS="${MY_ARGS} ${var}"
   	fi
	I=$I+1;
done


$VM_PATH $MY_ARGS $CHAMP1 $CHAMP2 > tmp_file1
$MY_VM_PATH $MY_ARGS $CHAMP1 $CHAMP2 > tmp_file2

diff tmp_file1 tmp_file2
