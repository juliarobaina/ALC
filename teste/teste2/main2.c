#include "seidel.c"

int main(){

	int numLinhas,numColunas,numIteracoes;

	printf("Digite o numero de linhas e colunas: ");
	scanf("%d %d",&numLinhas,&numColunas);

	int a[numLinhas][numColunas];//valores da matriz
	int b[numLinhas];//valores depois da igualdade da equação
	int x[numLinhas];//vetor solução inicial

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
		scanf("%d",&x[i]);
	}

	printf("\n");

	printf("Digite quantas iteracoes devem ser feitas: ");
	scanf("%d",&numIteracoes);

	printf("\n");

	int k = 0;
	int *y = calloc(numLinhas,sizeof(int));
	float temp;
	int aux;

	//Para fazer a fração
	int auxMultN,auxMultD,auxDiviN,auxDiviD,auxSomaN,auxSomaD;
	int **vetorsolucao = alocarMatriz(numLinhas,2);
	int **matrizParaCalcular = alocarMatriz(2, 2);
	int **vetorAuxiliar = alocarMatriz(1,2);
	int **vetorAuxiliar2 = alocarMatriz(1,2);

	int cont = 0;
	int vetorAuxN, vetorAuxD;
	
	for (int i = 0; i < numLinhas; i++){
		vetorsolucao[i][0] = x[i];
		vetorsolucao[i][1] = 1;
		/*printf("o valor do x %d\n",x[i]);
		printf("vetorsolucao[%d][0] = %d\n",i,vetorsolucao[i][0]);
		printf("vetorsolucao[%d][1] = %d\n",i,vetorsolucao[i][1]);*/
	}
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	while(k < numIteracoes){
		
		for (int i = 0 ; i < numLinhas; i++){
			y[i] = b[i];
			cont = 0;
			for (int j = 0; j < numLinhas; j++){
				if(j != i){

					/*if(i == 1){
						printf("---------------------------------------\n");
						printf("%d\n",vetorsolucao[j][0]);
						printf("%d\n",vetorsolucao[j][1]);
						
						printf("---------------------------------------\n");
					}*/

					matrizParaCalcular[cont][0] = multiplicarFracao((a[i][j] * -1),vetorsolucao[j][0],1,vetorsolucao[j][1],1);
					matrizParaCalcular[cont][1] = multiplicarFracao((a[i][j] * -1),vetorsolucao[j][0],1,vetorsolucao[j][1],2);
					
					//matrizParaCalcular[cont][0] = somarFracao(y[i],matrizParaCalcular[cont][0],1,matrizParaCalcular[cont][1],1);
					//matrizParaCalcular[cont][1] = somarFracao(y[i],matrizParaCalcular[cont][0],1,matrizParaCalcular[cont][1],2);
					//printf("%d - cont %d\n",matrizParaCalcular[cont][0],cont);
					//printf("%d - cont %d\n",matrizParaCalcular[cont][1],cont);
					
					/*printf("%d - cont %d\n",vetorsolucao[j][0],cont);
					printf("%d - cont %d\n",vetorsolucao[j][1],cont);*/
					//printf("%d - cont %d\n",matrizParaCalcular[cont][1],cont);

					cont++;
					//y[i] = y[i] - a[i][j] * x[j];
				}
				
			}

			/*auxSomaN = somarFracao(y[i],auxMultN,1,auxMultD,1);
			matrizParaCalcular[cont][1] = somarFracao(y[i],auxMultN,1,auxMultD,2);*/
			vetorAuxiliar[0][0] = somarFracao(matrizParaCalcular[0][0],matrizParaCalcular[1][0],matrizParaCalcular[0][1],matrizParaCalcular[1][1],1);
					/*printf("%d\n",matrizParaCalcular[0][0]);
					printf("%d\n",matrizParaCalcular[0][1]);
					printf("%d\n",matrizParaCalcular[1][0]);
					printf("%d\n",matrizParaCalcular[1][1]);
					printf("&&&& %d \n",vetorAuxiliar[0][0]);*/
			vetorAuxiliar[0][1] = somarFracao(matrizParaCalcular[0][0],matrizParaCalcular[1][0],matrizParaCalcular[0][1],matrizParaCalcular[1][1],2);
					//printf("$$$$ %d \n",vetorAuxiliar[0][1]);

			vetorAuxiliar2[0][0] = somarFracao(b[i],vetorAuxiliar[0][0],1,vetorAuxiliar[0][1],1);
			vetorAuxiliar2[0][1] = somarFracao(b[i],vetorAuxiliar[0][0],1,vetorAuxiliar[0][1],2);
				/*	printf("%d\n",b[i]);
					printf("%d\n",vetorAuxiliar[0][0]);
					printf("%d\n",vetorAuxiliar[0][1]);
					
					printf("&&&& %d \n",vetorAuxiliar[0][0]);
			printf("VetorSuxiliar2 %d\n",vetorAuxiliar2[0][0]);
			printf("VetorSuxiliar2 %d\n",vetorAuxiliar2[0][1]);*/

			vetorsolucao[i][0] = dividirFracao(vetorAuxiliar2[0][0],a[i][i],vetorAuxiliar2[0][1],1,1);
			//printf("Vetor Auxiliar %d\n",vetorsolucao[i][0]);
			vetorsolucao[i][1] = dividirFracao(vetorAuxiliar2[0][0],a[i][i],vetorAuxiliar2[0][1],1,2);

			int valorMDC = MDC(vetorsolucao[i][0],vetorsolucao[i][1]);

			if(valorMDC != 1){
				vetorsolucao[i][0] = vetorsolucao[i][0] / valorMDC;
				vetorsolucao[i][1] = vetorsolucao[i][1] / valorMDC;
			}
			
			printf("Iteracao %d -> Numerador: %d\n",k,vetorsolucao[i][0]);
			printf("Iteraao %d -> Denominador: %d\n",k,vetorsolucao[i][1]);
			/*y[i] = y[i] / a[i][i];
			temp = x[i];
			x[i] = y[i];
			y[i] = temp;*/
		}

		//critério de parada
		k++;
	}

	/*for (int i = 0; i < numLinhas; i++){
		printf("O vetor solucao e \n");
		printf(" x[%d] = %d\n",i+1,x[i]);
	}*/

	printf("\n");

	printf("-------------------------------------------\n");
	for (int i = 0; i < numLinhas; i++){
		
			printf(" vetSol[%d] = %d",i+1,vetorsolucao[i][0]);
			printf("---\n");
			printf("%10d\n",vetorsolucao[i][1]);
		
	}

	printf("\n");

	


	free(y);
	liberarMatriz(vetorsolucao,numLinhas);
	liberarMatriz(matrizParaCalcular,2);
	liberarMatriz(vetorAuxiliar,1);
	liberarMatriz(vetorAuxiliar2,1);


	return 0;
}
