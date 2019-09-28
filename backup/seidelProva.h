#ifndef _SEIDELPROVA_H
#define _SEIDELPROVA_H

#include <stdio.h>
#include <math.h>
#include "alocacaoDinamica.c"

	double** gerarMatriz(int n);
	double* gerarTermosIndependentes(int n);
	double* seidel(int numIteracoes,int numLinhas, double* b, double** a,double* x);
	double* sor(int numIteracoes,int numLinhas, double* b, double** a,double* x,double w);

	void imprimirVetorSolucao(int numLinhas,double* x);
	void calcularErro(double* erro, double* x,int numLinhas);


#endif