#include "alocacaoDinamicaInteiro.h"

int* alocarVetor(int tam){
	
	int* novo = (int*) malloc(tam * sizeof(int));

	return novo;
}

int** alocarMatriz(int linha,int coluna){
	
	int** novo = (int**) malloc(linha * sizeof(int*));
	
	for (int i = 0; i < linha; i++){
		novo[i] = alocarVetor(coluna);
	}

	return novo;
}

void liberarMatriz(int** matriz,int linha){

	for(int i = 0;i < linha;i++){
		free(matriz[i]);
	}

	free(matriz);
}