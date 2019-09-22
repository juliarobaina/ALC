#ifndef _METODOSITERATIVOSCOMFRACAO_H
#define _METODOSITERATIVOSCOMFRACAO_H

#include "alocacaoDinamicaInteiro.c"
#include "fracoes.c"
#include <stdio.h>

	Fracao* calcularSeidel(int numIteracoes, int numLinhas, int* b, int** a,float* x);
	Fracao* calcularJacobiComFracao(int numIteracoes, int numLinhas, int* b, int** a,float* x);
	void imprimirVetorSolucao(int numLinhas,Fracao* x);




#endif