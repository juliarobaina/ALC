#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

	printf("\n");

	printf("Digite os valores depois da equação\n");
	for (int i = 0; i < numLinhas; i++){
		printf("Digite o %dº valor\n",i+1);
		scanf("%d",&b[i]);
	}

	printf("\n");

	printf("A matriz e:\n");
	for (int i = 0; i < numLinhas; i++){
		for (int j = 0; j < numColunas; j++){
			printf("%5d",a[i][j]);
		}
		printf(" = %d\n",b[i]);
	}

	printf("\n");

	printf("Digite o vetor inicial\n");
	for (int i = 0; i < numLinhas; i++){
		printf("Digite o %dº valor\n",i+1);
		scanf("%f",&x[i]);
	}

	printf("\n");

	printf("Digite quantas iteracoes devem ser feitas: ");
	scanf("%d",&numIteracoes);

	printf("\n");

	int k = 0;
	float *y = calloc(numLinhas,sizeof(float));
	float temp;
	int aux;

	while(k < numIteracoes){
		
		for (int i = 0 ; i < numLinhas; i++){
			y[i] = b[i];
			for (int j = 0; j < numLinhas; j++){
				if(j != i)
					y[i] = y[i] - a[i][j] * x[j];
				
			}
			
			y[i] = y[i] / a[i][i];
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


	free(y);



	return 0;
}