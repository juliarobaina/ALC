#ifndef _SOR_H
#define _SOR_H

#include <stdio.h>
#include <stdlib.h>
#include "seidel.c"

	float* calcularSeidel(int numIteracoes, int numLinhas, int* b, int** a,float* x);
	void imprimirVetorSolucao(int numLinhas,float* x);



#endif