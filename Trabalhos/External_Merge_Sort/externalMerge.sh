#!/bin/bash

if [ $# -ne "2" ]; then
   echo "--Usage: $0 <n_particoes> <database_path>"
   exit 1
fi

N_SEG=$(echo "2^$1" | bc);
FILENAME=$2;

CREATIONFILES="criando_filhos";
JOINFILES="juntando_filhos";

Creation_bin_name="n_external";
Joining_bin_name="inter";

if [[ ! -d "$(pwd)/$CREATIONFILES" ]]; then
    mkdir "$(pwd)/$CREATIONFILES";
fi

if [[ ! -d "$(pwd)/$JOINFILES" ]]; then
    mkdir "$(pwd)/$JOINFILES";
fi

if [[ ! -e "$(pwd)/$FILENAME" ]]; then
    echo "Nao foi possivel encontrar a base de dados $Filename. Verifique se ela se encontra no diretorio '$(pwd)/$CREATIONFILES'";
    exit 1;
else 
    mv "$(pwd)/$FILENAME" "$(pwd)/$CREATIONFILES/$FILENAME"
fi

if [[ ! -e "./$CREATIONFILES/$Creation_bin_name" ]]; then
    gcc -o $Creation_bin_name "external_segmentation.c";
    mv $Creation_bin_name "./$CREATIONFILES";
fi

if [[ ! -e "./$JOINFILES/$Joining_bin_name" ]]; then
    gcc -o $Joining_bin_name "external_join.c"
    mv $Joining_bin_name "./$JOINFILES";
fi

cd "./$CREATIONFILES";

if [[ ! -e "./$Creation_bin_name" ]]; then
    echo "Nao foi possivel encontrar o binario $Creation_bin_name. Verifique se ela se encontra no diretorio '$(pwd)/$CREATIONFILES'";
    exit 1;
fi

./$Creation_bin_name $N_SEG $FILENAME && echo "Programa de particao ($Creation_bin_name) executado com sucesso" && rm ./$Creation_bin_name;

mv cep_* "../$JOINFILES"

cd "../$JOINFILES"

if [[ ! -e "./$Joining_bin_name" ]]; then
    echo "Nao foi possivel encontrar o binario $Joining_bin_name. Verifique se ela se encontra no diretorio '$(pwd)/$CREATIONFILES'";
    exit 1;
fi

./$Joining_bin_name $N_SEG && echo "Programa de juncao ($Joining_bin_name) executado com sucesso" && rm ./$Joining_bin_name;

echo "O arquivo remanescente equivale ao original.. :)"

