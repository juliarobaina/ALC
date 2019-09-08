#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int* alocarVetor(int tam){
	
	int* novo = (int*) malloc(tam * sizeof(float));

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

int retornarNumerador(int numerador1,int denominador2){
	
	int resultNumerador = numerador1 * denominador2;

	return resultNumerador;
}

int retornarDenominador(int numerador2, int denominador1){
	
	int resultDenominador = denominador1 * numerador2;
	
	return resultDenominador;
}

int retornarSomaFracao(int numerador1,int numerador2,int denominador1,int denominador2){
	
	int resultNumerador,resultDenominador;

	if(denominador1 == denominador2){
		resultNumerador = numerador1 + numerador2;
		resultDenominador = denominador1;
	}else{
		resultDenominador = denominador1 * denominador2;
		aux1 = denominador2 * numerador1;
		aux2 = denominador1 * numerador2;
		resultNumerador = aux1 + aux2;
	}

	return resultNumerador;
}

int main(){

	int numLinhas,numColunas,numIteracoes;

	printf("Digite o numero de linhas e colunas: ");
	scanf("%d %d",&numLinhas,&numColunas);

	int a[numLinhas][numColunas];//valores da matriz
	int b[numLinhas];//valores depois da igualdade da equação
	float x[numLinhas];//vetor solução inicial

	printf("Digite a matriz\n");
	for (int i = 0; i < numLinhas; i++){
		for(int j = 0; j < numColunas;j++){
			printf("a[%d][%d] = ",i,j);
			scanf("%d",&a[i][j]);
		}
	}

	printf("Digite os valores depois da equação\n");
	for (int i = 0; i < numLinhas; i++){
		printf("Digite o %dº valor\n",i+1);
		scanf("%d",&b[i]);
	}

	printf("A matriz e:\n");
	for (int i = 0; i < numLinhas; i++){
		for (int j = 0; j < numColunas; j++){
			printf("%5d",a[i][j]);
		}
		printf(" = %d\n",b[i]);
	}

	printf("Digite o vetor inicial\n");
	for (int i = 0; i < numLinhas; i++){
		printf("Digite o %dº valor\n",i+1);
		scanf("%f",&x[i]);
	}

	printf("Digite quantas iteracoes devem ser feitas: ");
	scanf("%d",&numIteracoes);

	int k = 0;
	float *y = calloc(numLinhas,sizeof(float));
	float temp;
	int **vetorsolucao = alocarMatriz(numLinhas,2);
	int aux;
	while(k < numIteracoes){
		
		for (int i = 0 ; i < numLinhas; i++){
			y[i] = b[i];
			for (int j = 0; j < numLinhas; j++){
				if(j != i){
					y[i] = y[i] - a[i][j] * x[j];//numerador
					aux = a[i][j] * x[j];
					printf("resultado vetor Y no y[%d]: %f\n",i,y[i]);
				}
			}
			//Para representar em fracao
			
			if(i != 0){
				int somaDoNumerador1 = retornarSomaFracao(aux + vetorsolucao[i-1][i-1],vetorsolucao[i-1][i-1],);
				vetorsolucao[i][i] = retornarNumerador(retornarSomaFracao(aux + vetorsolucao[i-1][i-1],),1);//vetorsolucao[i-1][i-1]
				vetorsolucao[i][i+1] = retornarDenominador(a[i][i],vetorsolucao[i-1][i]);	
			}else{
				vetorsolucao[i][i] = retornarNumerador(y[i],1);
				vetorsolucao[i][i+1] = retornarDenominador(a[i][i],y[i]);
			}
			
			//come Gauss-Seidel
			y[i] = y[i] / a[i][i];//y[i]->numerador,a[i][i] denominador
			temp = x[i];
			x[i] = y[i];
			y[i] = temp;
		}

		//critério de parada
		k++;
	}

	for (int i = 0; i < numLinhas; i++){
		printf("O vetor solucao e \n");
		printf(" x[%d] = %f\n",i+1,x[i]);
	}

	printf("\n");

	printf("-------------------------------------------\n");
	for (int i = 0; i < numLinhas; i++){
		
			printf(" vetSol[%d] = %d",i+1,vetorsolucao[i][i]);
			printf("---\n");
			printf("%10d\n",vetorsolucao[i][i+1]);
		
	}

	free(y);

	liberarMatriz(vetorsolucao,numLinhas);


	return 0;
}