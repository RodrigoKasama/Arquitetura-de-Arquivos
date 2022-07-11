#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _sinasc sinasc;

struct _sinasc
{
	char CODMUNNASC[6]; /* Código do Município de Nascimento */
	char CODESTAB[7];	/* Código do Estabelecimento */
	char CODMUNRES[6];	/* Código do Município de Residência */
	char DTNASC[8];		/* Data de Nascimento no formato DDMMAAAA */
	char SEMAGESTAC[2]; /* Número de Semanas de Gestação */
	char SEXO[1];		/* Sexo 0 não informado, 1 Masculino ou 2 Feminino */
	char PESO[4];		/* Peso em gramas */
	char DTNASCMAE[8];	/* Data de Nascimento no formato DDMMAAAA */
};

int compara_cod(const void *el1, const void *el2)
{
	return strncmp(((sinasc *)el1)->CODESTAB, ((sinasc *)el2)->CODESTAB, 7);
}

int main(int argc, char *argv)
{
	sinasc *el, *els_sort;
	FILE *fd, *fd2, *fd3;
	char *filename = "sinasc-sp-2018.dat";
	char *fileoutput = "sinasc-sp-capital-2018.dat";
	int size_el = sizeof(sinasc);
	long size_file;
	fd = fopen(filename, "rb");
	if (!fd)
	{
		printf("aaaaaaaaaaa\n");
		return -1;
	}


	fseek(fd, 0, SEEK_END);
	size_file = ftell(fd);

	fprintf(stdout, "1) Tamanho do arquivo: %ld\n", size_file);
	fprintf(stdout, "2) Tamanho do item %d\n", size_el);
	long int qnt_els = size_file / size_el;
	fprintf(stdout, "3) Quantidade de elementos no arquivo %ld\n", qnt_els);

	fseek(fd, 0, SEEK_SET);

	fd2 = fopen("sinasc-sp-capital-2018.dat", "wb");
	if (!fd2)
	{
		printf("sdjklldjfl\n");
		return -1;
	}
	int els_added = 0;
	int girls_santistas = 0;
	int bebes_magros = 0;
	while (!feof(fd))
	{
		fread(el, 1, size_el, fd);

		if (strncmp(el->CODMUNNASC, "355030", 6) == 0)
		{
			fwrite(el, 1, size_el, fd2);
			els_added++;
		}

		if (strncmp(el->SEXO, "2", 1) == 0 && strncmp(el->CODMUNNASC, "354850", 6) == 0)
		{
			girls_santistas++;
		}

		if (strncmp(el->PESO, "2500", 4) < 0 && strncmp(el->CODMUNNASC, "350950", 6) == 0)
		{
			bebes_magros++;
		}
	}

	fprintf(stdout, "4) Elementos adicionado no novo arquivo %s: %d\n", fileoutput, els_added);
	fprintf(stdout, "5) Meninas nascidas em Santos: %d\n", girls_santistas);
	fprintf(stdout, "6) Bebes com baixo peso em Campinas: %d\n", bebes_magros);

	rewind(fd);

	els_sort = (sinasc *)malloc(size_file);

	fread(els_sort, 1, size_file, fd);

	qsort(els_sort, qnt_els, sizeof(sinasc), compara_cod);

	fd3 = fopen("sinasc-sp-2018-ordenado.dat","wb");

	fwrite(els_sort, 1, size_file, fd3);

	fclose(fd);
	fclose(fd2);
	fclose(fd3);
}