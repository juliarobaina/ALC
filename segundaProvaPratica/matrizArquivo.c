#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int main(){

	FILE* arquivo;

	arquivo = fopen("matrizArquivo.txt","w");

	if(arquivo == NULL)
		printf("Erro ao abrir um arquivo\n");
	else
		printf("Arquivo criado com sucesso\n");

	double m[MAX][MAX],b[MAX];
	int cont = 0;

	//Preenche a matriz diagonal inferior
	for(int i = 0; i < MAX; i++){

		cont = 1;
		for(int j = 1; j < MAX; j++){
	
			m[j][i] = cont;
			if(i != j && j > i){
				
				cont++;
			}
			
		}	
	}

	int aux = cont = 20;//a PRIMEIRA VERSAO CONT É IGUAL A 21

	//Preenche a matriz diagonal superior
	for(int i = 0; i < MAX; i++){

		cont--;
		for(int j = MAX - 1; j > i; j--){
			m[i][j] = cont;
			cont--;
			
		}
		cont = aux - 1;
		aux--;
	}

	//Preenche o vetor b
	for (int i = 0; i < MAX; ++i)
	{
		m[i][i] = 0;
		b[i] = i + 1;
	}

	//Escreve no arquivo
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){

			fprintf(arquivo, "%lf", m[i][j]);

			if(j + 1 == 20)
				fprintf(arquivo, "%lf\n",b[i]);
		}
	}


	fclose(arquivo);

	

	for(int i = 0;i < MAX;i++){
		for(int j = 0; j < MAX; j++){

			printf("%5.1lf ",m[i][j]);
		}
		printf(" = %.1lf",b[i]);
		printf("\n");
	}

	return 0;
}
