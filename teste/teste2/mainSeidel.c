#include "seidel.c"

int res(int n,int n2){
	return n + n2;
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

	//Para fazer a fração
	int auxMultN,auxMultD,auxDiviN,auxDiviD,auxSomaN,auxSomaD;
	int **vetorsolucao = alocarMatriz(numLinhas,2);
	
	for (int i = 0; i < numLinhas; i++){
		vetorsolucao[i][i] = x[i];
		vetorsolucao[i][i+1] = 1;
	}
	int o = 0;

	while(k < numIteracoes){
		
		for (int i = 0 ; i < numLinhas; i++){
			y[i] = b[i];
			for (int j = 0; j < numLinhas; j++){
				if(j != i){
					if(i == 0){
						auxMultN = multiplicarFracao(a[i][j],vetorsolucao[i][i],1,vetorsolucao[i][i+1],1);
						auxMultD = multiplicarFracao(a[i][j],vetorsolucao[i][i],1,vetorsolucao[i][i+1],2);
					

					
						printf("Entrei\n");
						auxSomaN = somarFracao(y[i],auxMultN,1,auxMultD,1);
						auxSomaD = somarFracao(y[i],auxMultN,1,auxMultD,2);
						printf("AuxMult = %d -- %d\n",auxMultN,auxMultD);
						printf("AuxSoma = %d -- %d\n",auxSomaN,auxSomaD);
					}else if(i == 1){
						//auxMultN = multiplicarFracao(a[i][j],vetorsolucao[i-1][i-1],1,vetorsolucao[i-1][i],1);
						auxMultN = multiplicarFracao(vetorsolucao[i-1][i-1],a[i][j],vetorsolucao[i-1][i],1,1);
						auxMultD = multiplicarFracao(vetorsolucao[i-1][i-1],a[i][j],vetorsolucao[i-1][i],1,2);

						//auxSomaN = somarFracao(y[i],auxMultN,1,auxMultD,1);
						auxSomaN = somarFracao(auxMultN,y[i],auxMultD,1,1);
						auxSomaD = somarFracao(auxMultN,y[i],auxMultD,1,2);
						printf("AuxMult = %d -- %d\n",auxMultN,auxMultD);
						printf("AuxSoma = %d -- %d\n",auxSomaN,auxSomaD);
					}else{
						if(j == 1){
							//auxMultN = multiplicarFracao(a[i][j],vetorsolucao[i-1][i-1],1,vetorsolucao[i-1][i],1);
						auxMultN = multiplicarFracao(vetorsolucao[i-j][i-j],a[i][j],vetorsolucao[i-j][i],1,1);
						auxMultD = multiplicarFracao(vetorsolucao[i-j][i-j],a[i][j],vetorsolucao[i-j][i],1,2);

						auxSomaN = somarFracao(y[i],auxMultN,1,auxMultD,1);
						//auxSomaN = somarFracao(auxMultN,y[i],auxMultD,1,1);
						auxSomaD = somarFracao(y[i],auxMultN,1,auxMultD,2);
						printf("AuxMult = %d -- %d\n",auxMultN,auxMultD);
						printf("AuxSoma = %d -- %d\n",auxSomaN,auxSomaD);
						}
						
					}
					
					
					/*else{
						printf("NAAAO\n");
						auxSomaN = somarFracao(x[i],auxMultN,1,auxMultD,1);
						auxSomaD = somarFracao(x[i],auxMultN,1,auxMultD,2);
					}*/
					
					
					//vetorsolucao[i][i] = auxSomaN;
					//vetorsolucao[i][i+1] = auxSomaD;

					y[i] = y[i] - a[i][j] * x[j];
				}


				
			}

			if(i == 0){
				vetorsolucao[i][i] = auxSomaN;
				vetorsolucao[i][i+1] = a[i][i];
			}else{
				auxDiviN = dividirFracao(auxSomaN,a[i][i],auxSomaD,1,1);
				auxDiviD = dividirFracao(auxSomaN,a[i][i],auxSomaD,1,2);
				printf("AuxdiviN e: %d\n",auxSomaN);
				vetorsolucao[i][i] = auxDiviN;
				vetorsolucao[i][i+1] = auxDiviD;
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