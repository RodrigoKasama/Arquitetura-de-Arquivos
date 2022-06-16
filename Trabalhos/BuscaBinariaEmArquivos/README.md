# Busca Binária em Arquivo

Trabalho abordando o conceito de busca binária em um arquivo de CEP's. 

Para compilação do código, recomenda-se utilizar o **gcc**

``` bash
gcc -o main busca_bin.c
```
O arquivo utiliza as funções ```fseek()``` e ```ftell()``` para cálculo e deslocamento do cursor no arquivo.

Para execução, insira o CEP desejado como primeiro argumento e o diretório do arquivo de dados como segundo. 
Assim como no exemplo:
``` bash
./main <CEP> <FILEBASE_PATH>
```

**Obs**: Vale lembrar que a busca binária baseia-se em uma sequência de itens **ordenados** por um parâmetro, caso não esteja ordenado, a busca não será funcional.
