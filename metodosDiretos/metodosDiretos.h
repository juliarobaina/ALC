#ifndef _METODOSDIRETOS_
#define _METODOSDIRETOS_

#include "alocacaoDinamica.c"
#include <math.h>

	//int verificarMatrizTriangular(double** matriz,int ordem);
	double* triangularInferior(double** matriz, double* vetorB, double* vetorSolucao, int ordem);
	double* triangularSuperior(double** matriz, double* vetorB, double* vetorSolucao, int ordem);
	void eliminacaoGauss_pivoteamentoTotal(double** matriz, double* vetorB ,int ordem);
	void eliminacaoGauss_pivoteamentoParcial(double** matriz, double* vetorB ,int ordem);
	void eliminacaoGauss(double** matriz, double* vetorB ,int ordem);
	void decomposicaoLU(double** matriz, double* vetorB ,int ordem);
	void cholesky(double** matriz,double* vetorB, int ordem);

	void imprimirMatriz(double** matriz, int ordem);
	void imprimirVetor(double* vet, int ordem);

#endif
