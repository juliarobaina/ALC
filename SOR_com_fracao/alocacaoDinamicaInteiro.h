#ifndef _ALOCACAODINAMICAINTEIRO_H
#define _ALOCACAODINAMICAINTEIRO_H

#include <stdlib.h>

	int* alocarVetor(int tam);
	int** alocarMatriz(int linha,int coluna);
	void liberarMatriz(int** matriz,int linha);


#endif