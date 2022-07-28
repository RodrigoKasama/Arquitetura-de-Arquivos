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
	char lixo[2];
};

int intercalar_arquivos(int indice, int lastadded)
{
	FILE *fd1, *fd2, *out;
	Endereco *end1, *end2;
	char arq1[12], arq2[12], arq3[12];

	// Forma o nome dos arquivos de entrada
	sprintf(arq1, "cep_%d.dat", indice);
	sprintf(arq2, "cep_%d.dat", indice + 1);
	// Forma o nome do arquivo de saida
	sprintf(arq3, "cep_%d.dat", lastadded);

	// Antes de passar o valor, reserve o espaço com malloc()
	end1 = (Endereco *)malloc(sizeof(Endereco));
	end2 = (Endereco *)malloc(sizeof(Endereco));

	// Abrindo arquivos..
	fd1 = fopen(arq1, "rb");
	if (!fd1)
	{
		fprintf(stderr, "Nao foi possivel abrir o arquivo %s\n", arq1);
		return -1;
	}

	fd2 = fopen(arq2, "rb");
	if (!fd2)
	{
		fprintf(stderr, "Nao foi possivel abrir o arquivo %s\n", arq2);
		return -1;
	}

	out = fopen(arq3, "wb");
	fprintf(stderr, "\tAnalisando os arquivos %s e %s e escrevendo em %s\n", arq1, arq2, arq3);

	// Lê o primeiro de cada e faz a rotina de comaparação por intercalação
	fread(end1, sizeof(Endereco), 1, fd1);
	fread(end2, sizeof(Endereco), 1, fd2);

	int diff;
	// Enquanto um dos arquivos não terminar...
	while (!feof(fd1) && !feof(fd2))
	{
		diff = strncmp(end1->cep, end2->cep, 8);
		// Compara, escreve o menor e anda com o cursor no que andou
		if (diff < 0)
		{
			fwrite(end1, sizeof(Endereco), 1, out);
			fread(end1, sizeof(Endereco), 1, fd1);
		}
		else if (diff > 0)
		{
			fwrite(end2, sizeof(Endereco), 1, out);
			fread(end2, sizeof(Endereco), 1, fd2);
		}
		else
		{
			// Prevenção de elementos repetidos elementos repetidos
			fprintf(stderr, "Aviso! Elementos repetido em dois arquivos diferentes\n");
			fwrite(end2, sizeof(Endereco), 1, out);
			// Anda com qualquer um
			fread(end1, sizeof(Endereco), 1, fd1);
		}
	}
	// Para evitar/fugir dos while's, bastaria calcular o quanto falta para o final do arquivo com fseek e escrever um único bloco de uma vez
	while (!feof(fd1))
	{
		fwrite(end1, sizeof(Endereco), 1, out);
		fread(end1, sizeof(Endereco), 1, fd1);
	}
	while (!feof(fd2))
	{
		fwrite(end2, sizeof(Endereco), 1, out);
		fread(end2, sizeof(Endereco), 1, fd2);
	}

	// Fecha os arquivos de leitura e escrita
	fclose(fd1);
	fclose(fd2);
	fclose(out);

	// Tenta apagar os arquivos de entrada para aliviar o armazenamento..
	// Os arquivos de entrada estao organizados no arq de saida
	if (remove(arq1) == 0)
	{
		fprintf(stdout, "\t%s apagado com sucesso\n", arq1);
	}
	if (remove(arq2) == 0)
	{
		fprintf(stdout, "\t%s apagado com sucesso\n", arq2);
	}

	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Numero de argumentos invalidos\n");
		return -1;
	}

	int nomeint = 0;
	int lastadded = atoi(argv[1]);

	while (lastadded - nomeint > 1)
	{
		if (intercalar_arquivos(nomeint, lastadded) != 0)
		{
			fprintf(stderr, "Algo deu errado durante o processo de intercalacao\n");
			return -1;
		}
		lastadded++;
		nomeint += 2;
	}

	fprintf(stdout, "Fim do processo de join.\n"); //\nIndice do Arquivo final: %d.\n", lastadded - 1);
	return 0;
}
