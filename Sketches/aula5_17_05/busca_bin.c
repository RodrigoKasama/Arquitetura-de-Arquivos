#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int main(int argc, char **argv)
{
    FILE *fd;
    Endereco addr;
    int counter = 0;
    
    char *filename = "cep_ordenado.dat";
    char *cep_req = "25250640";

    fd = fopen(filename, "rb");
    // desloca o cursor para o  0 bytes de distancia da flag fim do arquivo
    if (fseek(fd, 0, SEEK_END) < 0)
    {
        fprintf(stderr, "Não foi possivel percorrer o arquivo destino");
        return -1;
    }
    // diz em Qual byte o cursor está atualmente
    long numBy = ftell(fd);
    // Divide pelo size de um unico elemento da lista
    long numAdds = numBy / sizeof(Endereco);


    // Esquema de busca binaria
    int inicio = 0, fim = numAdds - 1, meio = 0;
    int diff_addrs = 0;

    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;

        // vai para o meio do intervalo 
        fseek(fd, meio * sizeof(Endereco), SEEK_SET);
        // Le a struct e joga na variavel addr
        fread(&addr, sizeof(Endereco), 1, fd);
        // Compara a diff entre as duas strings
        diff_addrs = strncmp(cep_req, addr.cep, 8);

        if (diff_addrs == 0)
        {
            fprintf(stdout, "Endereco encontrado!\nEndereco: %s", addr.logradouro);
            break;
        }
        else if (diff_addrs > 0)
        {
            inicio = meio + 1;
        }
        else if (diff_addrs < 0)
        {
            fim = meio - 1;
        }
        counter++;
    }
    
    printf("%d\n", counter);
    fprintf(stdout, "\nFim da procura...");
    fclose(fd);
}