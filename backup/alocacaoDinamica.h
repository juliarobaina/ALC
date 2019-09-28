#ifndef _ALOCACAODINAMICA_H
#define _ALOCACAODINAMICA_H

#include <stdlib.h>

	double* alocarVetor(int tam);
	double** alocarMatriz(int linha,int coluna);
	void liberarMatriz(double** matriz,int linha);


#endif