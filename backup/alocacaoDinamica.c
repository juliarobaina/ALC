#include "alocacaoDinamica.h"

double* alocarVetor(int tam){
	
	double* novo = (double*) malloc(tam * sizeof(double));

	return novo;
}

double** alocarMatriz(int linha,int coluna){
	
	double** novo = (double**) malloc(linha * sizeof(double*));
	
	for (int i = 0; i < linha; i++){
		novo[i] = alocarVetor(coluna);
	}

	return novo;
}

void liberarMatriz(double** matriz,int linha){

	for(int i = 0;i < linha;i++){
		free(matriz[i]);
	}

	free(matriz);
}