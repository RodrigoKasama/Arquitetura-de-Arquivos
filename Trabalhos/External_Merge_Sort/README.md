# External Merge Sort

### Introdução 
Durante as aulas foi reapresentado os conceitos de ordenação como Quicksort, Heapsort, Mergesort...

Todos esses métodos de ordenação basearam-se na afirmativa que o arquivo de dados cabe na memória principal da máquina, apesar de não ser a realidade na maioria dos casos de ordenação.

Por isso, é possivel abordar o conceito de *external sorting* o arquivo é segmentado em N arquivos pequenos o suficiente para o carregamento em memória.

### Cabeçalho da Tarefa
Através do conceito apresentado, o objetivo desse trabalho é criar um programa que, dado o arquivo "cep.dat", crie arquivos segmentados ordenados individualmente. Ou seja, dado um numero inteiro x como entrada o programa deve gerar 'y' arquivos de acordo com a equação y = 2^x.

Da mesma forma, a segunda parte dessa tarefa consiste em juntar esses 2^x elementos dois a dois para no fim, remontar o arquivo original "cep.dat".

## Instruções
Para compilação do código, recomenda-se utilizar o **gcc**, é possivel executar os programas individualmente.

``` bash
gcc -o main1 external_segmentation.c
gcc -o main2 external_join.c
```

Para execução do **external_segmentation.c**, insira o inteiro desejado como primeiro argumento e o diretório do arquivo "cep.dat". 
Assim como no exemplo:
``` bash
./main1 <N_PARTITIONS> <BASEFILE_PATH>
```

Para execução do **external_join.c**, basta inserir o **mesmo inteiro escrito anteriormente** como primeiro argumento. 
Assim como no exemplo:
``` bash
./main2 <N_PARTITIONS>
```
Obs.: No caso do *external_join.c* o programa deletará os arquivos gerados para liberar espaço no armazenamento. 

## Extra:
Para integração dos programas, utilizei um bash script para criar diretórios-filhos com o objetivo de isolar os arquivos gerados. Para utilizar basta usar o comando (BASH) como argumento um numero intero e o diretório do arquivo de dados "cep.dat". Ao final do programa, o arquivo remanescente na pasta de junção de arquivos será o igual ao arquivo "cep.dat"

``` bash
./externalMerge.sh N '/tmb/cep.dat'
```

(Atenção: Como a natureza desta equação é exponencial, tome cuidado com números muito altos, visto que pode causar lentidão e/ou resultados inesperados.) 

