#ifndef _METODOSDIRETOS_
#define _METODOSDIRETOS_

#include "alocacaoDinamica.c"

	double* triangularInferior(double** matriz, double* vetorB, double* vetorSolucao, int ordem);
	double* triangularSuperior(double** matriz, double* vetorB, double* vetorSolucao, int ordem);
	double** eliminacaoGauss(double** matriz, double* vetorB ,int ordem);

	void imprimirMatriz(double** matriz, int ordem);

#endif
