#ifndef _FUNCOESBASE_H
#define _FUNCOESBASE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


	float* alocarVetor(int tam);
	float** alocarMatriz(int linha,int coluna);//pode fazer, se for matriz quadrada, alocarMatriz(float matriz[][linha]);
	void liberarMatriz(float** matriz,int linha);
	void liberarVetor(float* vetor);

	int podeSomarSubtrair(int linha1,int linha2,int coluna1,int coluna2);
	int podeMultiplicar(int coluna1,int linha2);
	//somar todos os elementos da matriz
	float somarMatriz(float** matriz1,float** matriz2,int linha, int coluna);
	//subtrair todos os elmentos da matriz
	float subtrairMatriz(float** matriz1,float**matriz2,int linha, int coluna);
	//multiplicar todos os elementos da matriz
	float multiplicarMatriz(float** matriz1,float**matriz2,int linha, int coluna);
	int matrizParaVetor(int** matriz,int linha, int coluna);
	float** retornarMatrizSoma(float** matriz1,float**matriz2,int linha, int coluna);
	float** retornarMatrizSubtracao(float** matriz1,float**matriz2,int linha, int coluna);
	float** retornarMatrizMultiplicacao(float** matriz1,float**matriz2,int linha1, int coluna1,int coluna2);





#endif