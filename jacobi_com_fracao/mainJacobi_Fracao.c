#include "seidel.c"

int main(){

	int numLinhas,numColunas,numIteracoes;
	//Para fazer a fração	
	
	int cont = 0;
	
	Fracao fracaoAuxiliar;
	Fracao fracaoAuxiliar2;


	printf("Digite o numero de linhas e colunas: ");
	scanf("%d %d",&numLinhas,&numColunas);
	if (numLinhas != numColunas || numLinhas == 0 || numColunas == 0){
		printf("Nao e uma matriz quadrada\n");
		exit(1);
	}

	int **matrizParaCalcular = alocarMatriz(numColunas-1, 2);
	int a[numLinhas][numColunas];//valores da matriz
	int b[numLinhas];//valores depois da igualdade da equação
	Fracao* fracaoSolucao =  malloc(numLinhas * sizeof(Fracao));//Primeiramente recebe o vetor inicial
	Fracao* fracaoAuxiliar3 = malloc(numLinhas * sizeof(Fracao));
	
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
		scanf("%d",&fracaoSolucao[i].numerador);
		fracaoSolucao[i].denominador = 1;
	}

	printf("\n");

	printf("Digite quantas iteracoes devem ser feitas: ");
	scanf("%d",&numIteracoes);

	if(numIteracoes == 0){
		exit(1);
	}

	printf("\n");

	int k = 0;

	while(k < numIteracoes){
		
		for (int i = 0 ; i < numLinhas; i++){

			if(a[i][i] != 0){//Não faz divisão por zero

				cont = 0;

				for (int j = 0; j < numLinhas; j++){
					
					if(j != i){
						//faz a multiplicação do a[i][j] * x[j]
						matrizParaCalcular[cont][0] = multiplicarFracao((a[i][j] * -1),fracaoSolucao[j].numerador,1,fracaoSolucao[j].denominador,1);
						matrizParaCalcular[cont][1] = multiplicarFracao((a[i][j] * -1),fracaoSolucao[j].numerador,1,fracaoSolucao[j].denominador,2);
						
						cont++;
					}
					
				}

				if(numLinhas == 2){//Só tem uma variável no outro lado da equação

					fracaoAuxiliar.numerador = matrizParaCalcular[0][0];
					fracaoAuxiliar.denominador = matrizParaCalcular[0][1];
						
				}else if(numLinhas == 1){
					
					fracaoSolucao[i].numerador = dividirFracao(b[i],a[i][i],1,1,1);
					fracaoSolucao[i].denominador = dividirFracao(b[i],a[i][i],1,1,2);
					break;

				}else{

					//somar x1 com x2, por exemplo
					fracaoAuxiliar.numerador = somarFracao(matrizParaCalcular[0][0],matrizParaCalcular[1][0],matrizParaCalcular[0][1],matrizParaCalcular[1][1],1);					
					fracaoAuxiliar.denominador = somarFracao(matrizParaCalcular[0][0],matrizParaCalcular[1][0],matrizParaCalcular[0][1],matrizParaCalcular[1][1],2);												
				}

				//somar o resultado anterior com o valor depois da equacao
				fracaoAuxiliar2.numerador = somarFracao(b[i],fracaoAuxiliar.numerador,1,fracaoAuxiliar.denominador,1);
				fracaoAuxiliar2.denominador = somarFracao(b[i],fracaoAuxiliar.numerador,1,fracaoAuxiliar.denominador,2);
				
				//dividir o resultado com o a[i][i]
				fracaoAuxiliar3[i].numerador = dividirFracao(fracaoAuxiliar2.numerador,a[i][i],fracaoAuxiliar2.denominador,1,1);					
				fracaoAuxiliar3[i].denominador = dividirFracao(fracaoAuxiliar2.numerador,a[i][i],fracaoAuxiliar2.denominador,1,2);
				
				

			}else{
				exit(1);
			}
		}

		for (int p = 0; p < numLinhas; p++)
		{
			
			fracaoSolucao[p].numerador = fracaoAuxiliar3[p].numerador;
			fracaoSolucao[p].denominador = fracaoAuxiliar3[p].denominador;

			int valorMDC = MDC(fracaoSolucao[p].numerador,fracaoSolucao[p].denominador);					
			//Faz a simplificação
			fracaoSolucao[p].numerador /= valorMDC;
			fracaoSolucao[p].denominador /= valorMDC;
		}

		
		//critério de parada
		k++;
	}


	printf("\n");

	printf("-------------------------------------------\n");
	for (int i = 0; i < numLinhas; i++){
		
		printf(" vetSol[%d] =\n %d",i+1,fracaoSolucao[i].numerador);
		printf("\n ---\n");
		printf(" %d\n",fracaoSolucao[i].denominador);		
	}

	printf("\n");

	

	free(fracaoSolucao);
	free(fracaoAuxiliar3);
	liberarMatriz(matrizParaCalcular,2);
	


	return 0;
}
