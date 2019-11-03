#include "metodosDiretos.h"

double* triangularInferior(double** matriz, double* vetorB, double* vetorSolucao, int ordem){

	double* x = vetorSolucao;

	for(int i = 0; i < ordem; i++){

		x[i] = vetorB[i];

		for(int j = 0; j <= i - 1; j++){

			x[i] = x[i] - matriz[i][j] * x[j];
		}

		x[i] = x[i] / matriz[i][i];
	}
	
	return x;
}

double* triangularSuperior(double** matriz, double* vetorB, double* vetorSolucao, int ordem){

	double* x = vetorSolucao;

	for(int i = ordem - 1; i >= 0; i--){

		x[i] = vetorB[i];

		for(int j = i + 1; j < ordem; j++){

			x[i] = x[i] - matriz[i][j] * x[j];
		}

		x[i] = x[i] / matriz[i][i];
	}

	return x;
}

void imprimirMatriz(double** matriz, int ordem){

	for(int i = 0; i < ordem; i++){
		for(int j = 0; j < ordem; j++){

			printf("%10.5lf",matriz[i][j]);
		}

			printf("\n");
	}
}