#include "seidel.h"

int somarFracao(int numerador1,int numerador2,int denominador1,int denominador2,int escolha){

	int resultNumerador,resultDenominador,aux1,aux2;

	if(abs(denominador1) == abs(denominador2)){
		resultNumerador = numerador1 + numerador2;
		resultDenominador = denominador1;
	}else{
		resultDenominador = denominador1 * denominador2;
		aux1 = denominador2 * numerador1;
		aux2 = denominador1 * numerador2;
		resultNumerador = aux1 + aux2;
	}

	if (escolha == 1) 
		return resultNumerador; 
	else
		return resultDenominador;
}

int dividirFracao(int numerador1,int numerador2,int denominador1,int denominador2,int escolha){
	
	int resultNumerador,resultDenominador;

	resultNumerador = numerador1 * denominador2;
	resultDenominador = denominador1 * numerador2;

	if (escolha == 1) 
		return resultNumerador; 
	else
		return resultDenominador;
}

int multiplicarFracao(int numerador1,int numerador2,int denominador1,int denominador2,int escolha){

	int resultNumerador,resultDenominador;

	resultNumerador = numerador1 * numerador2;
	resultDenominador = denominador1 * denominador2;

	if (escolha == 1) 
		return resultNumerador; 
	else
		return resultDenominador;
}

int MDC(int numerador,int denominador){

	int resto = numerador % denominador;
	int aux = 1;

	while(resto != 0){
		aux = resto;
		resto = denominador % resto;
		denominador = aux;
	}

	return aux;
}

int* alocarVetor(int tam){
	
	int* novo = (int*) malloc(tam * sizeof(int));

	return novo;
}

int** alocarMatriz(int linha,int coluna){
	
	int** novo = (int**) malloc(linha * sizeof(int*));
	
	for (int i = 0; i < linha; i++){
		novo[i] = alocarVetor(coluna);
	}

	return novo;
}

void liberarMatriz(int** matriz,int linha){

	for(int i = 0;i < linha;i++){
		free(matriz[i]);
	}

	free(matriz);
}
