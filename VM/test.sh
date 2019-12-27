VM_PATH=../vm_champs/corewar
MY_VM_PATH=./vm

CHAMP_PATH=../vm_champs/

#CHAMP1="${CHAMP_PATH}champs/jumper.cor"
#CHAMP1="${CHAMP_PATH}champs/Mortel.cor"
#CHAMP1="${CHAMP_PATH}champs/Octobre_rouge_V4.2.cor"
#CHAMP1="${CHAMP_PATH}champs/Toto.cor"
#CHAMP1="${CHAMP_PATH}champs/slider2.cor"
#CHAMP1="${CHAMP_PATH}champs/examples/fluttershy.cor"
#CHAMP1="${CHAMP_PATH}champs/championships/2018/bcozic/pai_mu_tan.cor"
#CHAMP1="${CHAMP_PATH}champs/championships/2014/gbir/_.cor"
#CHAMP1="${CHAMP_PATH}champs/championships/2018/mkamel/le_pet_de_nonne.cor"

#CHAMP1="${CHAMP_PATH}champs/car.cor"
CHAMP1="${CHAMP_PATH}champs/maxidef.cor"

#CHAMP1="${CHAMP_PATH}champs_tests/test.cor"

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


$VM_PATH $MY_ARGS $CHAMP1 $CHAMP1> zaz_file
$MY_VM_PATH $MY_ARGS $CHAMP1 $CHAMP1> my_file

diff zaz_file my_file
