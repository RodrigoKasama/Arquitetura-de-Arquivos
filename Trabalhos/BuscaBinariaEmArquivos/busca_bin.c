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
    if (argc != 3)
    {
        fprintf(stderr, "Usage: get_cep <CEP> <Database>\n");
        fprintf(stderr, "Este programa utiliza o conceito de busca binária e, por esse motivo, a base de dados PRECISA estar ordenada.\n");
        fprintf(stderr, "Escrito por Rodrigo Parracho (RodrigoKasama)\n");
        exit(1);
    }

    FILE *fd;
    Endereco addr;
    int counter = 0;

    char *cep_req = argv[1];
    char *filename = argv[2];

    fd = fopen(filename, "rb");

    if (!fd)
    {
        fprintf(stderr, "Não foi possivel encontrar a base de dados %s.\nVerifique se a mesma encontra-se no mesmo diretório que o programa", filename);
        return -1;
    }

    // Desloca o cursor para o  0 bytes de distancia da flag SEEK_END -> "Fim do Arquivo"
    if (fseek(fd, 0, SEEK_END) < 0)
    {
        fprintf(stderr, "Não foi possivel percorrer o arquivo %s", filename);
        return -1;
    }

    // Retorna em qual byte da stream o cursor está atualmente
    long numBy = ftell(fd);

    // Divide pelo size de um unico elemento da lista
    long numAdds = numBy / sizeof(Endereco);

    // Esquema de busca binaria
    int inicio = 0, fim = numAdds - 1, meio = 0;
    int diff_addrs, flag = 0;

    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;

        // Vai para o meio do intervalo
        fseek(fd, meio * sizeof(Endereco), SEEK_SET);

        // Lê a struct e joga na variavel addr
        fread(&addr, sizeof(Endereco), 1, fd);

        // Compara a diff entre as duas strings
        diff_addrs = strncmp(cep_req, addr.cep, 8);

        //fprintf(stderr,"%s\n", addr.logradouro);

        // Não há diferença, é o que procuro..
        if (diff_addrs == 0)
        {
            fprintf(stdout, "Endereco encontrado!\nEndereco: %s", addr.logradouro);
            flag = 1;
            break;
        }
        else if (diff_addrs > 0)
        {
            // Redefine a partição para procurar
            inicio = meio + 1;
        }
        else if (diff_addrs < 0)
        {
            // Redefine a partição para procurar
            fim = meio - 1;
        }
        // Verifica quantas buscas são feitas
        counter++;
    }

    fclose(fd);
    fprintf(stdout, "\nFim da procura...");

    if (flag == 1)
    {
        fprintf(stdout, "Foram realizadas %d buscas para encontrar este CEP.\n", counter);
    }
    else
    {
        fprintf(stderr, "Não foi posivel encontrar o CEP %s, verifique se o CEP foi digitado corretamente ou se a base de dados realmente está ordenada e tente de novo.\n", cep_req);
        return -1;
    }
    return 0;
}