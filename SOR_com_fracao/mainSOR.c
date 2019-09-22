#include "sor.c"

int main(int argc, char const *argv[]){
	

	int numLinhas,numColunas,numIteracoes;
	float w;//w é o peso

	printf("Digite o numero de linhas e colunas: ");
	scanf("%d %d",&numLinhas,&numColunas);

	//int a[numLinhas][numColunas];//valores da matriz
	int** a = alocarMatriz(numLinhas,numColunas);
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

	printf("Digite o peso: ");
	scanf("%f",&w);
	printf("PESO = %.3f\n",w);
	printf("Digite quantas iteracoes devem ser feitas: ");
	scanf("%d",&numIteracoes);

	printf("\n");

	int k = 0;
	float *y = calloc(numLinhas,sizeof(float));
	float *vetorSolucao = calloc(numLinhas,sizeof(float));
	float* seidel;
	
	while(k < numIteracoes){
		
		seidel = calcularSeidel(k+1,numLinhas,b,a,x);
		
		for (int i = 0 ; i < numLinhas; i++){
			
			y[i] = b[i];
			
			for (int j = 0; j < numLinhas; j++){
				if(j != i){
					y[i] = y[i] - a[i][j] * x[j];					
				}
				
				
			}
			
			
			y[i] = ((y[i] / a[i][i]) * (1 - w)) + (seidel[i] * w);
		
			vetorSolucao[i] = y[i];
			
		}	

		for (int p = 0; p < numLinhas; p++)
		{
			x[p] = vetorSolucao[p];
		}
		

		//critério de parada
		k++;
	}

	imprimirVetorSolucao(numLinhas,x);



	free(y);
	free(seidel);
	free(vetorSolucao);
	liberarMatriz(a,numLinhas);




	return 0;
}
