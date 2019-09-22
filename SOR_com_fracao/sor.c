#include "sor.h"

float* calcularSeidel(int numIteracoes, int numLinhas, int* b, int** a,float* x){


	int k = 0;
	float* y = (float*) calloc(numLinhas,sizeof(float));
	float* x2 = (float*) calloc(numLinhas,sizeof(float));;
	
	int* b2 = calloc(numLinhas,sizeof(int));
	
	for (int i = 0; i < numLinhas; i++){
		x2[i] = x[i];

		b2[i] = b[i];

	}

	for (int i = 0; i < numLinhas; i++){
		x2[i] = 0.0;
	}
	
	float temp;
	
	while(k < numIteracoes){
		
		for (int i = 0 ; i < numLinhas; i++){
		
			y[i] = b2[i];
			for (int j = 0; j < numLinhas; j++){
				if(j != i){
					y[i] = y[i] - a[i][j] * x2[j];
					
				}				
			}
			
			y[i] = y[i] / a[i][i];
			temp = x2[i];
			x2[i] = y[i];
			y[i] = temp;

		}

		//critério de parada
		k++;
	}


	

	free(b2);
	free(y);
	
	return x2;

}

void imprimirVetorSolucao(int numLinhas,float* x){

	for (int i = 0; i < numLinhas; i++){
		printf("O vetor solucao e \n");
		printf(" x[%d] = %f\n",i+1,x[i]);
	}
}