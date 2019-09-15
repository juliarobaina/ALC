#ifndef _SEIDEL_H
#define _SEIDEL_H

#include <stdio.h>
#include <stdlib.h>

struct fracao{
	int numerador;
	int denominador;
};

typedef struct fracao Fracao;

	int somarFracao(int numerador1,int numerador2,int denominador1,int denominador2,int escolha);
	int dividirFracao(int numerador1,int numerador2,int denominador1,int denominador2,int escolha);
	int multiplicarFracao(int numerador1,int numerador2,int denominador1,int denominador2,int escolha);
	int MDC(int numerador,int denominador);
	
	int* alocarVetor(int tam);
	int** alocarMatriz(int linha,int coluna);
	void liberarMatriz(int** matriz,int linha);

#endif
