#include "metodosIterativosComFracao.h"

Fracao* calcularSeidelComFracao(int numIteracoes, int numLinhas, int* b, int** a,float* x){
	
	int cont;
	int k = 0;

	Fracao fracaoAuxiliar;
	Fracao fracaoAuxiliar2;
	Fracao* fracaoSolucao =  malloc(numLinhas * sizeof(Fracao));
	Fracao* fracaoAuxiliar3 = malloc(numLinhas * sizeof(Fracao));
	int **matrizParaCalcular = alocarMatriz(numLinhas-1, 2);

	for (int i = 0; i < numLinhas; i++){
		fracaoSolucao[i].numerador = x[i];
		fracaoSolucao[i].denominador = 1;
	}

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
					fracaoSolucao[i].numerador = dividirFracao(fracaoAuxiliar2.numerador,a[i][i],fracaoAuxiliar2.denominador,1,1);					
					fracaoSolucao[i].denominador = dividirFracao(fracaoAuxiliar2.numerador,a[i][i],fracaoAuxiliar2.denominador,1,2);
					
					//Calcula o máximo divisor comum
					int valorMDC = MDC(fracaoSolucao[i].numerador,fracaoSolucao[i].denominador);					
					//Faz a simplificação
					fracaoSolucao[i].numerador /= valorMDC;
					fracaoSolucao[i].denominador /= valorMDC;

				}else{
					exit(1);
				}
			}

			//critério de parada
			k++;
	}

	liberarMatriz(matrizParaCalcular,2);
	free(fracaoAuxiliar3);

	return fracaoSolucao;	
}

Fracao* calcularJacobiComFracao(int numIteracoes, int numLinhas, int* b, int** a,float* x){
	
	int k = 0,cont;

	Fracao fracaoAuxiliar;
	Fracao fracaoAuxiliar2;
	Fracao* fracaoSolucao =  malloc(numLinhas * sizeof(Fracao));
	Fracao* fracaoAuxiliar3 = malloc(numLinhas * sizeof(Fracao));
	int **matrizParaCalcular = alocarMatriz(numLinhas-1, 2);

	for (int i = 0; i < numLinhas; i++){
		fracaoSolucao[i].numerador = x[i];
		fracaoSolucao[i].denominador = 1;
	}

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

	liberarMatriz(matrizParaCalcular,2);
	free(fracaoAuxiliar3);

	return fracaoSolucao;
}

void imprimirVetorSolucao(int numLinhas,Fracao* x){

	for (int i = 0; i < numLinhas; i++){
		
		printf(" vetSol[%d] =\n %d",i+1,x[i].numerador);
		printf("\n ---\n");
		printf(" %d\n",x[i].denominador);		
	}
}