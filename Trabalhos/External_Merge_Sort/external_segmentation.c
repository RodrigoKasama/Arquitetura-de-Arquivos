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

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco *)e1)->cep, ((Endereco *)e2)->cep, 8);
}

int main(int argc, char **argv)
{
	FILE *fd, *saida;
	Endereco *el;
	long comp_arquivo, qnt_els, passo, count = 0;
	int size_el = sizeof(Endereco);
	char output[12];
	
	if (argc != 2)
	{
		fprintf(stderr, "Numero de argumentos invalidos");
		return -1;
	}
	int n_particoes = atoi(argv[1]);
	fd = fopen("cep.dat", "rb");
	if (!fd)
	{
		printf("Nao foi possivel abrir o arquivo..\n");
		return -1;
	}

	fseek(fd, 0, SEEK_END);
	comp_arquivo = ftell(fd);
	rewind(fd);

	qnt_els = comp_arquivo / size_el;
	printf("Enderecos no original %ld\n", qnt_els);

	passo = qnt_els / n_particoes;
	count = 0;
	for (int i = 0; i < n_particoes; i++)
	{
		sprintf(output, "cep_%d.dat", i);
		saida = fopen(output, "wb");
		if (i + 1 == n_particoes && qnt_els % n_particoes != 0) // Caso o numero de elementos não seja divisivel, ou seja, não é possivel fazer n arquivos com x elementos iguais, então o último arquivo terá o que restar da divisão
		{
			// Onde eu estou e quanto falta para o fim?
			long curr_pos = ftell(fd);
			long bloco_que_falta = comp_arquivo - curr_pos;
			// Maloca um espaço que falta e escreve ele, independente de qnts elementos tem..
			el = (Endereco *)malloc(bloco_que_falta);
			fread(el, bloco_que_falta, 1, fd);
			qsort(el, bloco_que_falta, 1, compara);
			fwrite(el, bloco_que_falta, 1, saida);
			count += bloco_que_falta / size_el; // Contador de elementos escritos
			printf("%s -> %ld\n", output, bloco_que_falta / size_el);
		}
		else
		{
			// Alloca x elementos, ordena e escreve no arquivo
			el = (Endereco *)malloc(passo * size_el);
			fread(el, passo, size_el, fd);
			qsort(el, passo, size_el, compara);
			fwrite(el, passo, size_el, saida);
			count += passo;
			printf("%s -> %ld\n", output, passo);
		}
		free(el);
		fclose(saida);
	}
	fclose(fd);
	return 0;
}
