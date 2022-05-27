#include <stdio.h>
#include <string.h>
// Quero separar os endereços do file cep.dat de acordo com seu UF e criar um ARQUIVO SEPARADO para cada UF.

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
    if (argc != 1)
    {
        fprintf(stderr, "mais inputs esperados do que necessario");
        return -1;
    }

    char curr_uf[2];
    char *in_filename = "cep.dat";
    char format_output[12];
    int c;

    FILE *fd, *uf_fd = NULL;
    Endereco addr;

    fd = fopen(in_filename, "r");

    // Na primeira instancia escreve o curr_uf como "  " -> NULL_TERMINATED == usar strn___();
    strncpy(curr_uf, "  ", 2);

    while (c = fread(&addr, sizeof(Endereco), 1, fd))
    {
        // Na primeira instância..
        if (strncmp(curr_uf, "  ", 2) == 0)
        {
            // Monta a output_filename dinamicamente
            sprintf(format_output, "UF_%.2s.dat", addr.sigla);

            // Abre o arquivo do uf atual
            uf_fd = fopen(format_output, "ab");

            // Caso abriu corretamente, atualiza o valor da current_uf
            strncpy(curr_uf, addr.sigla, 2);
        }
        // UF e o diferente da anterior? 
        else if (strncmp(addr.sigla, curr_uf, 2) != 0)
        {
            // Fecha o fd aberto anteriormente
            fclose(uf_fd);
            // Faz o mesmo processo com o novo uf
            sprintf(format_output, "ceps_%.2s.dat", addr.sigla);

            uf_fd = fopen(format_output, "ab");
            strncpy(curr_uf, addr.sigla, 2);
        }

        // Caso nao seja a primeira instancia e o UF nao mudou, continue escrevendo no fd aberto..
        fwrite(&addr, sizeof(Endereco), 1, uf_fd);
    }
    // O último nunca vai ser fechado se não passar por esse if
    if (uf_fd)
    {
        fclose(uf_fd);
    }
    // Fecha a stream do .dat
    fclose(fd);

    return 0;
}