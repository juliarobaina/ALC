#include "metodosIterativosComFracao.c"

int main(int argc, char const *argv[]){
	
	int numLinhas,numColunas,numIteracoes;
	Fracao w;//w é o peso

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

	printf("Digite o peso:\n");
	printf("-- Numerador: ");
	scanf("%d",&w.numerador);
	printf("-- Denominador: ");
	scanf("%d",&w.denominador);
	printf("\n");
	printf("Digite quantas iteracoes devem ser feitas: ");
	scanf("%d",&numIteracoes);

	printf("\n");

	int k = 0;
	//float *y = calloc(numLinhas,sizeof(float));
	//float *vetorSolucao = calloc(numLinhas,sizeof(float));
	
	Fracao* seidel;
	Fracao* jacobi;
	Fracao fracaoAuxiliar;
	Fracao fracaoAuxiliar2;
	Fracao* fracaoAuxiliar3 =  malloc(numLinhas * sizeof(Fracao));
	Fracao* fracaoSolucao =  malloc(numLinhas * sizeof(Fracao));
	int **matrizParaCalcular = alocarMatriz(numColunas-1, 2);
	//float temp;
	//int aux;


	
	while(k < numIteracoes){
		
		seidel = calcularSeidelComFracao(k+1,numLinhas,b,a,x);

		/*printf("Printando Seidel\n");
		for (int p = 0; p < numLinhas; p++)
		{
			printf("%d\n",seidel[p].numerador);
			printf("---\n");
			printf("%d\n",seidel[p].denominador);
		}

		printf("\n");*/

		for (int i = 0 ; i < numLinhas; i++){

			//if(a[i][i] != 0){//Não faz divisão por zero
				printf("\n--------------------------ITERACAO----------------------------------%d\n",k+1);
				cont = 0;

				//for (int j = 0; j < numLinhas; j++){
					
					//if(j != i){
				if(k == 0){

						jacobi = calcularJacobiComFracao(k+1,numLinhas,b,a,x);
						/*printf("Printando Jacobi\n");
						for (int p = 0; p < numLinhas; p++)
						{
							printf("%d\n",jacobi[p].numerador);
							printf("---\n");
							printf("%d\n",jacobi[p].denominador);
						}*/

						printf("\n");
						//y[i] = y[i] - a[i][j] * x[j];
						
					//}
					
					
				//}

				
					//Faz a multiplicação do Jacobi com Peso (1-w)
					printf("\n%d %d %d %d\n",jacobi[i].numerador,somarFracao(1,-1 * w.numerador,
												1,w.denominador,1),jacobi[i].denominador,somarFracao(1,w.numerador,
												1,w.denominador,2) );
					fracaoAuxiliar.numerador = multiplicarFracao(jacobi[i].numerador,somarFracao(1,-1 * w.numerador,
												1,w.denominador,1),jacobi[i].denominador,somarFracao(1,w.numerador,
												1,w.denominador,2),1);

					
					fracaoAuxiliar.denominador = multiplicarFracao(jacobi[i].numerador,somarFracao(1,-1 * w.numerador,
												1,w.denominador,1),jacobi[i].denominador,somarFracao(1,w.numerador,
												1,w.denominador,2),2);
					printf("fracaoAuxiliar[%d] = %d && fracaoAuxiliar[%d] = %d\n",i,fracaoAuxiliar.numerador,
																					i,fracaoAuxiliar.denominador);
					//Faz a multiplicação do seidel com Peso w
					fracaoAuxiliar2.numerador = multiplicarFracao(seidel[i].numerador,w.numerador,seidel[i].denominador,w.denominador,1);
					fracaoAuxiliar2.denominador = multiplicarFracao(seidel[i].numerador,w.numerador,seidel[i].denominador,w.denominador,2);
					printf("fracaoAuxiliar2[%d] = %d && fracaoAuxiliar2[%d] = %d\n",i,fracaoAuxiliar2.numerador,
																					i,fracaoAuxiliar2.denominador);

					//Faz a soma dos dois resultados anteriores
					fracaoSolucao[i].numerador = somarFracao(fracaoAuxiliar.numerador,fracaoAuxiliar2.numerador,
												fracaoAuxiliar.denominador,fracaoAuxiliar2.denominador,1);
					fracaoSolucao[i].denominador = somarFracao(fracaoAuxiliar.numerador,fracaoAuxiliar2.numerador,
												fracaoAuxiliar.denominador,fracaoAuxiliar2.denominador,2);



					int valorMDC = MDC(fracaoSolucao[i].numerador,fracaoSolucao[i].denominador);					
					//Faz a simplificação
					fracaoSolucao[i].numerador /= valorMDC;
					fracaoSolucao[i].denominador /= valorMDC;
				}else{
					for (int j = 0; j < numLinhas; j++){
					
						if(j != i){
							printf("\n%d %d %d %d\n",fracaoSolucao[j].numerador,somarFracao(1,-1 * w.numerador,
												1,w.denominador,1),fracaoSolucao[j].denominador,somarFracao(1,w.numerador,
												1,w.denominador,2) );
							
							matrizParaCalcular[cont][0] = multiplicarFracao((a[i][j] * -1),fracaoSolucao[j].numerador,1,fracaoSolucao[j].denominador,1);
							matrizParaCalcular[cont][1] = multiplicarFracao((a[i][j] * -1),fracaoSolucao[j].numerador,1,fracaoSolucao[j].denominador,2);
						}
							fracaoAuxiliar.numerador = multiplicarFracao((a[i][j] * -1),fracaoSolucao[j].numerador,1,fracaoSolucao[j].denominador,1);
							fracaoAuxiliar.denominador = multiplicarFracao((a[i][j] * -1),fracaoSolucao[j].numerador,1,fracaoSolucao[j].denominador,2);
							//fracaoAuxiliar.numerador = multiplicarFracao(fracaoSolucao[j].numerador,somarFracao(1,-1 * w.numerador,
													//	1,w.denominador,1),fracaoSolucao[j].denominador,somarFracao(1,w.numerador,
														//1,w.denominador,2),1);

							
							
							printf("fracaoAuxiliar[%d] = %d && fracaoAuxiliar[%d] = %d\n",i,fracaoAuxiliar.numerador,
																							i,fracaoAuxiliar.denominador);
							//Faz a multiplicação do seidel com Peso w
							fracaoAuxiliar2.numerador = multiplicarFracao(seidel[i].numerador,w.numerador,seidel[i].denominador,w.denominador,1);
							fracaoAuxiliar2.denominador = multiplicarFracao(seidel[i].numerador,w.numerador,seidel[i].denominador,w.denominador,2);
							printf("fracaoAuxiliar2[%d] = %d && fracaoAuxiliar2[%d] = %d\n",i,fracaoAuxiliar2.numerador,
																							i,fracaoAuxiliar2.denominador);

							//Faz a soma dos dois resultados anteriores
							fracaoAuxiliar3[i].numerador = somarFracao(fracaoAuxiliar.numerador,fracaoAuxiliar2.numerador,
														fracaoAuxiliar.denominador,fracaoAuxiliar2.denominador,1);
							fracaoAuxiliar3[i].denominador = somarFracao(fracaoAuxiliar.numerador,fracaoAuxiliar2.numerador,
														fracaoAuxiliar.denominador,fracaoAuxiliar2.denominador,2);

						
					}

					



					
				}

				//y[i] = ((y[i] / a[i][i]) * (1 - w)) + (seidel[i] * w);
				
				//vetorSolucao[i] = y[i];
			//}else{
			//	exit(1);
			//}
		}	
		if(k > 0){
			for (int p = 0; p < numLinhas; p++)
		{
						
			fracaoSolucao[p].numerador = fracaoAuxiliar3[p].numerador;
			fracaoSolucao[p].denominador = fracaoAuxiliar3[p].denominador;

			int valorMDC = MDC(fracaoSolucao[p].numerador,fracaoSolucao[p].denominador);					
			//Faz a simplificação
			fracaoSolucao[p].numerador /= valorMDC;
			fracaoSolucao[p].denominador /= valorMDC;
		}
		}
		

		/*for (int p = 0; p < numLinhas; p++)
		{
			x[p] = vetorSolucao[p];
		}*/

		//critério de parada
		k++;
	}

	imprimirVetorSolucao(numLinhas,fracaoSolucao);



	//free(y);
	free(seidel);
	free(jacobi);
	free(fracaoAuxiliar3);
	free(fracaoSolucao);
	liberarMatriz(a,numLinhas);




	return 0;
}


