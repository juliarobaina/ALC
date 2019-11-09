#include "metodosDiretos.h"

void imprimirMatriz(double** matriz, int ordem){

	for(int i = 0; i < ordem; i++){
		for(int j = 0; j < ordem; j++){

			printf("%10.5lf",matriz[i][j]);
		}

		printf("\n");
	}
}

void imprimirVetor(double* vet, int ordem){
	
	for (int i = 0; i < ordem; i++){
		printf("%.5lf\n",vet[i]);
	}
}

double* triangularInferior(double** matriz, double* vetorB, double* vetorSolucao, int ordem){

	double* x = vetorSolucao;

	for(int i = 0; i < ordem; i++){

		x[i] = vetorB[i];

		for(int j = 0; j <= i - 1; j++){

			x[i] = x[i] - matriz[i][j] * x[j];
		}

		x[i] = x[i] / matriz[i][i];
	}
	
	return x;
}

double* triangularSuperior(double** matriz, double* vetorB, double* vetorSolucao, int ordem){

	double* x = vetorSolucao;

	for(int i = ordem - 1; i >= 0; i--){

		x[i] = vetorB[i];

		for(int j = i + 1; j < ordem; j++){

			x[i] = x[i] - matriz[i][j] * x[j];
		}

		x[i] = x[i] / matriz[i][i];
	}

	return x;
}

void eliminacaoGauss_pivoteamentoTotal(double** matriz, double* vetorB ,int ordem){//eliminação de Gauss com Pivoteamento Total
	
	int* variaveis = (int*) malloc(ordem * sizeof(int));
	
	//inicializa o variaveis em ordem crescente.
	for(int i = 0; i < ordem;i++){
		
		variaveis[i] = i; //x[0],x[1],x[2],...,x[n-1].			
	}


    //ETAPA DE ESCALONAMENTO
    for(int k = 0; k < ordem - 1; k++){
    	/*RODA N - 1 VEZES POR QUE EU NÃO PRECISO 
    	ESCALONAR ATÉ A ÚLTIMA COLUNA PARA TER UMA 
    	MATRIZ TRIANGULAR SUPERIOR. OS 0'S VÃO ATÉ A PENÚLTIMA COLUNA. N É O TAMANHO HUMANO; N - 1 TAMANHO DA MÁQUINA;
    	< N - 1 -> PERCORRA ATÉ A PENÚLTIMA LINHA */
    	
        double max = fabs(matriz[k][k]);
        int maxIndexL = k;//O maior valor da linha
        int maxIndexC = k;//O maior valor da coluna

        for(int i = k; i < ordem;i++){//procura o maior elemento da matriz
        	for(int j = 0; j < ordem; j++){
        		if(max < fabs(matriz[i][j])){
               		max = fabs(matriz[i][j]);
               		maxIndexC = j;
            	}
        	}
        }

        if(maxIndexC != k){//troca as colunas

        	for(int j = 0; j < ordem; j++){

                double temp = matriz[j][k];
                matriz[j][k] = matriz[j][maxIndexC];
                matriz[j][maxIndexC] = temp;

                int tempV = variaveis[k];
            	variaveis[k] = variaveis[maxIndexC];
            	variaveis[maxIndexC] = tempV;
            }
        }

        max = fabs(matriz[k][k]);

        for(int i = k + 1; i < ordem; i++){//procura o maior elemento da coluna, encontra a linha que está.
            if(max < fabs(matriz[i][k])){
                max = fabs(matriz[i][k]);
                maxIndexL = i;
            }
        }

        if(maxIndexL != k) {//Troca as linhas

            /*troca a equação k pela equação com o
              maior k-ésimo coeficiente em módulo. Troca o pivô.
             */
            for(int j = 0; j < ordem; j++) {
                double temp = matriz[k][j];
                matriz[k][j] = matriz[maxIndexL][j];
                matriz[maxIndexL][j] = temp;
            }
            double temp = vetorB[k];
            vetorB[k] = vetorB[maxIndexL];
            vetorB[maxIndexL] = temp;
        }

        //Se A[k][k] é zero, então a matriz dos coeficiente é singular
        //det A = 0
        if(matriz[k][k] == 0){
            printf("A matriz dos coeficientes é singular\n");
            return;
        }else{
            //realiza o escalonamento
            for(int m = k + 1; m < ordem; m++){
            	/*Esse loop defini o multiplicador da linha*/
                double F = -matriz[m][k] / matriz[k][k];
                matriz[m][k] = 0; //evita uma iteração
                vetorB[m] = vetorB[m] + F * vetorB[k];
                for(int l = k + 1; l < ordem; l++){
                	//Atualização da linha, matriz[k][l] é o elemento da linha do pivô
                    matriz[m][l] = matriz[m][l] + F * matriz[k][l];
                }
            }
        }
    }

    double* x = alocarVetor(ordem);

    //ETAPA DE RESOLUÇÃO DO SISTEMA
    for (int i = ordem - 1; i >= 0; i--){
        x[i] = vetorB[i];
        for(int j = i + 1; j < ordem; j++){
            x[i] = x[i] - x[j] * matriz[i][j];
        }

        x[i] = x[i] / matriz[i][i];
    }
     
    int cont = 0;
    int ind = 0;

    double solut[ordem];

    for(int i = 0; i < ordem;i++){
    	for(int j = 0;j < ordem; j++){
    		/*O vetor x da solução do sistema está trocado.
				Procuro o elemento que é igual ao índice i; 0,1,...,n-1; no vetor variaveis. Variaveis é onde se encontra
				as posições atuais dos vetores x1,x2,...,xn.
    		*/
    		if(i == variaveis[j])
    			ind = j;
    	}
    	/* solut recebe o valor de x de índice ind. x de índice ind, contém a posição que se encontra o primeiro
    	  valor do vetor solução, por exemplo. E assim sucessivamente. solut recebe todos os valores em ordem. Assim,
    	  se obtém o vetor solução na ordem correta.
    	 */
    	solut[i] = x[ind];
    }

    printf("\nVetor solucao - Eliminacao de Gauss com Pivoteamento Total\n");
    while(cont < ordem){

    	printf("x[%d] = %.5lf\n",cont,solut[cont]);
    
   		cont++;
    }
   
    printf("\n");
    free(x);
    free(variaveis);

}

void eliminacaoGauss_pivoteamentoParcial(double** matriz, double* vetorB ,int ordem){//eliminação de Gauss com Pivoteamento Total

    //ETAPA DE ESCALONAMENTO
    for(int k = 0; k < ordem - 1; k++){
    	/*RODA N - 1 VEZES POR QUE EU NÃO PRECISO 
    	ESCALONAR ATÉ A ÚLTIMA COLUNA PARA TER UMA 
    	MATRIZ TRIANGULAR SUPERIOR. OS 0'S VÃO ATÉ A PENÚLTIMA COLUNA. N É O TAMANHO HUMANO; N - 1 TAMANHO DA MÁQUINA;
    	< N - 1 -> PERCORRA ATÉ A PENÚLTIMA LINHA */
    	
        double max = fabs(matriz[k][k]);
        int maxIndexL = k;//O maior valor da linha

        for(int i = k + 1; i < ordem; i++){//procura o maior elemento da coluna, encontra a linha que está.
            if(max < fabs(matriz[i][k])){
                max = fabs(matriz[i][k]);
                maxIndexL = i;
            }
        }

        if(maxIndexL != k) {//Troca as linhas

            /*troca a equação k pela equação com o
              maior k-ésimo coeficiente em módulo. Troca o pivô.
             */
            for(int j = 0; j < ordem; j++) {
                double temp = matriz[k][j];
                matriz[k][j] = matriz[maxIndexL][j];
                matriz[maxIndexL][j] = temp;
            }
            double temp = vetorB[k];
            vetorB[k] = vetorB[maxIndexL];
            vetorB[maxIndexL] = temp;
        }

        //Se A[k][k] é zero, então a matriz dos coeficiente é singular
        //det A = 0
        if(matriz[k][k] == 0){
            printf("A matriz dos coeficientes é singular\n");
            return;
        }else{
            //realiza o escalonamento
            for(int m = k + 1; m < ordem; m++){
            	/*Esse loop defini o multiplicador da linha*/
                double F = -matriz[m][k] / matriz[k][k];
                matriz[m][k] = 0; //evita uma iteração
                vetorB[m] = vetorB[m] + F * vetorB[k];
                for(int l = k + 1; l < ordem; l++){
                	//Atualização da linha, matriz[k][l] é o elemento da linha do pivô
                    matriz[m][l] = matriz[m][l] + F * matriz[k][l];
                }
            }
        }
    }

    double* x = alocarVetor(ordem);

    //ETAPA DE RESOLUÇÃO DO SISTEMA
    for (int i = ordem - 1; i >= 0; i--){
        x[i] = vetorB[i];
        for(int j = i + 1; j < ordem; j++){
            x[i] = x[i] - x[j] * matriz[i][j];
        }

        x[i] = x[i] / matriz[i][i];
    }
     
    int cont = 0;

    printf("\nVetor solucao - Eliminacao de Gauss com Pivoteamento Parcial\n");
    while(cont < ordem){

    	printf("x[%d] = %.5lf\n",cont,x[cont]);
    
   		cont++;
    }
   
    printf("\n");
    free(x);

}

void eliminacaoGauss(double** matriz, double* vetorB ,int ordem){//eliminação de Gauss com Pivoteamento Total

    //ETAPA DE ESCALONAMENTO
    for(int k = 0; k < ordem - 1; k++){
    	/*RODA N - 1 VEZES POR QUE EU NÃO PRECISO 
    	ESCALONAR ATÉ A ÚLTIMA COLUNA PARA TER UMA 
    	MATRIZ TRIANGULAR SUPERIOR. OS 0'S VÃO ATÉ A PENÚLTIMA COLUNA. N É O TAMANHO HUMANO; N - 1 TAMANHO DA MÁQUINA;
    	< N - 1 -> PERCORRA ATÉ A PENÚLTIMA LINHA */
    	

        //Se A[k][k] é zero, então a matriz dos coeficiente é singular
        //det A = 0
        if(matriz[k][k] == 0){
            printf("A matriz dos coeficientes é singular\n");
            return;
        }else{
            //realiza o escalonamento
            for(int m = k + 1; m < ordem; m++){
            	/*Esse loop defini o multiplicador da linha*/
                double F = -matriz[m][k] / matriz[k][k];
                matriz[m][k] = 0; //evita uma iteração
                vetorB[m] = vetorB[m] + F * vetorB[k];
                for(int l = k + 1; l < ordem; l++){
                	//Atualização da linha, matriz[k][l] é o elemento da linha do pivô
                    matriz[m][l] = matriz[m][l] + F * matriz[k][l];
                }
            }
        }
    }

    double* x = alocarVetor(ordem);

    //ETAPA DE RESOLUÇÃO DO SISTEMA
    for (int i = ordem - 1; i >= 0; i--){
        x[i] = vetorB[i];
        for(int j = i + 1; j < ordem; j++){
            x[i] = x[i] - x[j] * matriz[i][j];
        }

        x[i] = x[i] / matriz[i][i];
    }
     
    int cont = 0;

    printf("\nVetor solucao - Eliminacao de Gauss com Pivoteamento Parcial\n");
    while(cont < ordem){

    	printf("x[%d] = %.5lf\n",cont,x[cont]);
    
   		cont++;
    }
   
    printf("\n");
    free(x);

}

void decomposicaoLU(double** matriz, double* vetorB ,int ordem){

	double** L = alocarMatriz(ordem);
	double** U;

	for(int i = 0;i < ordem;i++){
		
		L[i][i] = 1;
	}


	//ETAPA DE ESCALONAMENTO
    for(int k = 0; k < ordem - 1; k++){
    	
        if(matriz[k][k] == 0){
            printf("A matriz dos coeficientes é singular\n");
            return;
        }else{
            //realiza o escalonamento
            for(int m = k + 1; m < ordem; m++){
            	/*Esse loop defini o multiplicador da linha*/
            	printf("-matriz[m][k] / matriz[k][k] = %.5lf / %.5lf ||| %d - %d\n",matriz[m][k],matriz[k][k],k,m);
                double F = -matriz[m][k] / matriz[k][k];                
                matriz[m][k] = 0; //evita uma iteração
                
                L[m][k] = -F;//coloca os multiplicadores na matriz triangular inferior, -F para pegar o valor original de (matriz[m][k] / matriz[k][k])
                //vetorB[m] = vetorB[m] + F * vetorB[k];

                for(int l = k + 1; l < ordem; l++){
                	//Atualização da linha, matriz[k][l] é o elemento da linha do pivô
                    matriz[m][l] = matriz[m][l] + F * matriz[k][l];
                }

                imprimirMatriz(matriz,ordem);
                printf("\n");
            }
        }
    }

    U = matriz;

    printf("\n-----------------------------------------------------------------------------\n");
    printf("Matriz triangular\n");
    imprimirMatriz(L,ordem);
    printf("\nMatriz Superior\n");
    imprimirMatriz(U,ordem);
    printf("\nMatriz Escalonada\n");
    imprimirMatriz(matriz,ordem);


    double* vetorSolucao_matrizL = alocarVetor(ordem);
    vetorSolucao_matrizL = triangularInferior(L,vetorB,vetorSolucao_matrizL,ordem);

    printf("\nVetor solucao da matriz L\n");
    for (int i = 0; i < ordem; i++){
    	printf("x_L[%d] = %.5lf\n",i,vetorSolucao_matrizL[i]);
    }


    double* vetorSolucao_matrizU = alocarVetor(ordem);
    vetorSolucao_matrizU = triangularSuperior(U,vetorSolucao_matrizL,vetorSolucao_matrizU,ordem);

    printf("\nVetor solucao da matriz U\n");
    for (int i = 0; i < ordem; i++){
    	printf("x_U[%d] = %.5lf\n",i,vetorSolucao_matrizU[i]);
    }


    liberarMatriz(L,ordem);
    free(vetorSolucao_matrizL);
    free(vetorSolucao_matrizU);
  
}
