#include "funcoesBase.h"


float* alocarVetor(int tam){
	
	float* novo = (float*) malloc(tam * sizeof(float));

	return novo;
}

float** alocarMatriz(int linha,int coluna){
	
	float** novo = (float**) malloc(linha * sizeof(float*));
	
	for (int i = 0; i < linha; i++){
		novo[i] = alocarVetor(coluna);
	}

	return novo;
}

void liberarVetor(float* vetor){
	free(vetor);
}

void liberarMatriz(float** matriz,int linha){

	for(int i = 0;i < linha;i++){
		free(matriz[i]);
	}

	free(matriz);
}


float somarMatriz(float** matriz1,float** matriz2,int linha, int coluna){

	float soma = 0;

	for (int i = 0; i < linha; i++){
		for (int j = 0; j < coluna; j++){
			soma += (matriz1[i][j] + matriz2[i][j]);
		}
	}

	return soma;
}

float subtrairMatriz(float** matriz1,float**matriz2,int linha, int coluna){

	float sub = 0;

	for (int i = 0; i < linha; i++){
		for (int j = 0; j < coluna; j++){
			sub -= (matriz1[i][j] - matriz2[i][j]);
		}
	}

	return sub;
}

float multiplicarMatriz(float** matriz1,float**matriz2,int linha, int coluna){

	float mult = 1;

	for (int i = 0; i < linha; i++){
		for (int j = 0; j < coluna; j++){
			mult *= (matriz1[i][j] * matriz2[i][j]);
		}
	}

	return mult;
}

int matrizParaVetor(int** matriz,int linha, int coluna){

}

int podeSomarSubtrair(int linha1,int linha2,int coluna1,int coluna2){
	//mesmo número de linhas e colunas
	if((linha1 == linha2) && (coluna1 == coluna2)) 
		return 0; 
	else
		return 1;
}

int podeMultiplicar(int coluna1,int linha2){
	//o nº de colunas da primeira deve ser igual ao nº de linhas da segunda matriz
	if(coluna1 == linha2)
		return 0;
	else
		return 1;
}

float** retornarMatrizSoma(float** matriz1,float**matriz2,int linha, int coluna){

	float** matrizAux = alocarMatriz(linha,coluna);

	for (int i = 0; i < linha; i++){
		for (int j = 0; j < coluna; j++){
			matrizAux[i][j] = matriz1[i][j] + matriz2[i][j];
		}
	}

	return matrizAux;
}
float** retornarMatrizSubtracao(float** matriz1,float**matriz2,int linha, int coluna){

	float** matrizAux = alocarMatriz(linha,coluna);

	for (int i = 0; i < linha; i++){
		for (int j = 0; j < coluna; j++){
			matrizAux[i][j] = matriz1[i][j] - matriz2[i][j];
		}
	}

	return matrizAux;
}

float** retornarMatrizMultiplicacao(float** matriz1,float**matriz2,int linha1, int coluna1,int coluna2){

	float** matrizAux = alocarMatriz(linha1,coluna2);

	for(int i = 0;i < linha1;i++){
		for (int j = 0; j < coluna2; j++){
			for(int k = 0;k < coluna1;k++){
				matrizAux[i][j] += (matriz1[i][k] * matriz2[k][j]);
			}
		}
	}

	return matrizAux;
}
