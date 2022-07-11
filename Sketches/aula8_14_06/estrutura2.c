#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _sinasc sinasc;

struct _sinasc
{
    char CODMUNNASC[6]; /* Código do Município de Nascimento */
    char CODESTAB[7];   /* Código do Estabelecimento */
    char CODMUNRES[6];  /* Código do Município de Residência */
    char DTNASC[8];     /* Data de Nascimento no formato DDMMAAAA */
    char SEMAGESTAC[2]; /* Número de Semanas de Gestação */
    char SEXO[1];       /* Sexo 0 não informado, 1 Masculino ou 2 Feminino */
    char PESO[4];       /* Peso em gramas */
    char DTNASCMAE[8];  /* Data de Nascimento no formato DDMMAAAA */
};

int main(int argc, char *argv)
{

    sinasc el;
    FILE *fd, *curr_fd;

    int count = 1;
    char *filename = "sinasc-sp-2018-ordenado.dat";
    char out_filename[] = "0000000";
    fd = fopen(filename, "rb");

    fseek(fd, 0, SEEK_END);

    int size_file = ftell(fd);
    int size_el = sizeof(sinasc);
    long int qnt_els = size_file / size_el;

    rewind(fd);

    while (!feof(fd))
    {
        fread(&el, 1, size_el, fd);

        if(strncmp(el.CODESTAB, "0000000", 7) ==0)
        {

        }
        else

    }
}