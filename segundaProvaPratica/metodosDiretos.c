#include "metodosDiretos.h"
#include <string.h>
void imprimirMatriz(double** matriz, int ordem){

	for(int i = 0; i < ordem; i++){
		for(int j = 0; j < ordem; j++){

			printf("%6.2lf",matriz[i][j]);
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
            	/*Esse loop defini o multitrocarLicador da linha*/
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
    	  valor do vetor solução, por exemtrocarLo. E assim sucessivamente. solut recebe todos os valores em ordem. Assim,
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
            	/*Esse loop defini o multitrocarLicador da linha*/
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
            	/*Esse loop defini o multitrocarLicador da linha*/
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

    printf("\nVetor solucao - Eliminacao de Gauss\n");
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
            	/*Esse loop defini o multitrocarLicador da linha*/
            	//printf("-matriz[m][k] / matriz[k][k] = %.5lf / %.5lf ||| %d - %d\n",matriz[m][k],matriz[k][k],k,m);
                double F = -matriz[m][k] / matriz[k][k]; 

                matriz[m][k] = 0; //evita uma iteração
                
                L[m][k] = -F;//coloca os multitrocarLicadores na matriz triangular inferior, -F para pegar o valor original de (matriz[m][k] / matriz[k][k])
                //vetorB[m] = vetorB[m] + F * vetorB[k];

                for(int l = k + 1; l < ordem; l++){
                	//Atualização da linha, matriz[k][l] é o elemento da linha do pivô
                    matriz[m][l] = matriz[m][l] + F * matriz[k][l];
                }

                //imprimirMatriz(matriz,ordem);
                //printf("\n");
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

int is_simetrica(double** A, int ordem){

    for (int i = 0; i < ordem; ++i){
        for (int j = 0; j < ordem; ++j){
            if(i != j){
                if(A[i][j] != A[j][i]){
                    return 0;
                }
            }
        }
    }

    return 1;
}

void cholesky(double** A, double* vetorB, int ordem){//A matriz deve ser positiva definida

    double** G = alocarMatriz(ordem);
    double** G_t = alocarMatriz(ordem);
    double soma = 0,soma2 = 0;
    char* v;

    if(A[0][0] == 0){
        printf("Nao e possivel calcular cholesky\n");
   }else if(is_simetrica(A, ordem) == 0){
        printf("Nao e possivel calcular cholesky, matriz nao e simetrica\n");
    }else{


        G[0][0] = sqrt(A[0][0]);//G11 = raiz(a11)

        for(int i = 1; i < ordem;i++){
            //Fica uma matriz triangular inferior
            soma = 0;
            G[i][0] = A[i][0] / G[0][0];//calcular valores da 1ª coluna
           
            for(int j = 0; j <= i - 1;j++){
                //calcular valores da diagonal principal
                if(i >= 2 && j != 0){//calcular os valores das demais linhas e colunas
                    for(int p = 2; p < ordem; p++){
                        for(int r = 1;r < p;r++){
                             
                            soma2 = A[p][r];
                           
                            for(int k = 0; k < r; k++){
                                soma2 = soma2 - G[p][k] * G[r][k];
                            }
                            if(G[r][r] == 0){
                                printf("Nao e possivel calcular Cholesky\n");                            
                                exit(1);
                            }
                            G[p][r] = soma2 / G[r][r];
                        }                   
                    } 
                }
              
                soma = soma + pow(G[i][j],2);         
            }

            G[i][i] = sqrt(A[i][i] - soma);//calcular valores da diagonal principal      
        }

        //obtém a matriz G transposta
        for (int i = 0; i < ordem; ++i){
            for (int j = 0; j < ordem; ++j){
                G_t[i][j] = G[j][i];
            }
        }

       /* printf("\nA = G * Gt\n");
        printf("Matriz G:\n");
        imprimirMatriz(G,ordem);
        printf("\nMatriz Gt:\n");
        imprimirMatriz(G_t,ordem);*/
     
        

        /*
            ALGORITMO DA UFRJ
        
        for(int i = 0; i < ordem;i++){
            G[i][i] = sqrt(A[i][i]);
            for(int k = i+1;k < ordem;k++){
                G[i][k] = A[i][k] / G[i][i];
            }
            for(int k = i+1;k < ordem;k++){
                for(int j = k; j < ordem;j++){
                    A[k][j] = A[k][j] - G[i][k] * G[i][j];
                }
            }
        }*/
        

        
        /*                                     
            A * x = b               A = G * Gt 
                                               ^                      ^
            (G * Gt)* x = b         Gt * x = y |    direção de cálculo|
                                    G * y = b  |
        */
        double* vetorSolucao_matrizL = alocarVetor(ordem);
        vetorSolucao_matrizL = triangularInferior(G,vetorB,vetorSolucao_matrizL,ordem);

        for (int i = 0; i < ordem; i++){
            v = malloc(9 * sizeof(char));

            *v = vetorSolucao_matrizL[i];
            if(strcmp(v,"INFINITY") || strcmp(v,"NAN") || (!(vetorSolucao_matrizL[i] > 0) && !(vetorSolucao_matrizL[i] < 0))){
                printf("Nao e possivel calcular Cholesky\n");
                exit(1);
            }
            free(v);
        }
        printf("\nVetor solucao da matriz G\n");
        for (int i = 0; i < ordem; i++){
            printf("x_G[%d] = %.5lf\n",i,vetorSolucao_matrizL[i]);
        }


        double* vetorSolucao_matrizU = alocarVetor(ordem);
        vetorSolucao_matrizU = triangularSuperior(G_t,vetorSolucao_matrizL,vetorSolucao_matrizU,ordem);

        for (int i = 0; i < ordem; i++){
            v = malloc(9 * sizeof(char));

            *v = vetorSolucao_matrizL[i];
            if(strcmp(v,"INFINITY") || strcmp(v,"NAN") || (!(vetorSolucao_matrizL[i] > 0) && !(vetorSolucao_matrizL[i] < 0))){
                printf("Nao e possivel calcular Cholesky\n");
                exit(1);
            }
            free(v);
        }

        printf("\nVetor solucao da matriz Gt\n");
        for (int i = 0; i < ordem; i++){
            printf("x_Gt[%d] = %.5lf\n",i,vetorSolucao_matrizU[i]);
        }

        printf("\nA = G * Gt\n");
        printf("Matriz G:\n");
        imprimirMatriz(G,ordem);
        printf("\nMatriz Gt:\n");
        imprimirMatriz(G_t,ordem);

        free(vetorSolucao_matrizL);
        free(vetorSolucao_matrizU);
    }

   



    liberarMatriz(G,ordem);
    liberarMatriz(G_t,ordem);
    //free(v);


}


/*FUNÇÕES ABAIXO PARA A PROVA 2*/
/*void decomposicaoLU_PivoteamentoTotal(double** matriz, double* vetorB ,int ordem){

    double** L = alocarMatriz(ordem);
    double** P = alocarMatriz(ordem);
    double** U;

    for(int i = 0;i < ordem;i++){
        
        L[i][i] = 1;
        P[i][i] = 1;
    }

    int* variaveis = (int*) malloc(ordem * sizeof(int));
    
    //inicializa o variaveis em ordem crescente.
    for(int i = 0; i < ordem;i++){
        
        variaveis[i] = i; //x[0],x[1],x[2],...,x[n-1].          
    }

    //ETAPA DE ESCALONAMENTO
    for(int k = 0; k < ordem - 1; k++){
       
        double max = fabs(matriz[k][k]);
        int maxIndexL = k;//O maior valor da linha
        int maxIndexC = k;//O maior valor da coluna

        printf("PASSO A PASSO 4\n");
            imprimirMatriz(matriz,ordem);
            imprimirVetor(vetorB,ordem);
            
    

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

                /*double temp2 = L[j][k];
                L[j][k] = L[j][maxIndexC];
                L[j][maxIndexC] = temp2;*/

               /* int tempV = variaveis[k];
                variaveis[k] = variaveis[maxIndexC];
                variaveis[maxIndexC] = tempV;

               
            }
        }
         printf("PASSO A PASSO 1\n");
            imprimirMatriz(matriz,ordem);
            imprimirVetor(vetorB,ordem);
  

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
            /*for(int j = 0; j < ordem; j++) {
                double temp = matriz[k][j];
                matriz[k][j] = matriz[maxIndexL][j];
                matriz[maxIndexL][j] = temp;

                double temp2 = L[k][j];
                L[k][j] = L[maxIndexL][j];
                L[maxIndexL][j] = temp2;
                
            }
            double temp = vetorB[k];
            vetorB[k] = vetorB[maxIndexL];
            vetorB[maxIndexL] = temp;
        }
         printf("PASSO A PASSO 2\n");
            imprimirMatriz(matriz,ordem);
            imprimirVetor(vetorB,ordem);
   

        //Se A[k][k] é zero, então a matriz dos coeficiente é singular
        //det A = 0
         
        if(matriz[k][k] == 0){
            printf("A matriz dos coeficientes é singular\n");
            return;
        }else{
            /* printf("PASSO A PASSO\n");
            imprimirMatriz(matriz,ordem);
            imprimirVetor(vetorB,ordem);*/
   
            //realiza o escalonamento
           // for(int m = k + 1; m < ordem; m++){
                /*Esse loop defini o multitrocarLicador da linha*/
               /* double F = -matriz[m][k] / matriz[k][k];
                matriz[m][k] = 0; //evita uma iteração
                vetorB[m] = vetorB[m] + F * vetorB[k];

               
                L[m][k] = -F;//coloca os multitrocarLicadores na matriz triangular inferior, -F para pegar o valor original de (matriz[m][k] / matriz[k][k])
                for(int l = k + 1; l < ordem; l++){
                    //Atualização da linha, matriz[k][l] é o elemento da linha do pivô
                    matriz[m][l] = matriz[m][l] + F * matriz[k][l];
                }
            }
            printf("PASSO A PASSO 3\n");
            imprimirMatriz(matriz,ordem);
            imprimirVetor(vetorB,ordem);
     
        }
    }



    U = matriz;

    double* x = alocarVetor(ordem);

    //ETAPA DE RESOLUÇÃO DO SISTEMA
    for (int i = ordem - 1; i >= 0; i--){
        x[i] = vetorB[i];
        for(int j = i + 1; j < ordem; j++){
            x[i] = x[i] - x[j] * L[i][j];
        }

        x[i] = x[i] / L[i][i];
    }

    
    int ind = 0;

    double solut[ordem];
    

    for(int i = 0; i < ordem;i++){
        for(int j = 0;j < ordem; j++){
            if(i == variaveis[j])
                ind = j;
        }
        solut[i] = vetorB[ind];
    }

    printf("¨$$$$$$$$$$\n");
    imprimirMatriz(P,ordem);
        
    printf("Solut ->\n");
    //imprimirVetor(solut,ordem);
    imprimirVetor(x,ordem);
    for(int i = 0;i < ordem;i++){ 
        L[i][i] = 1;
    }

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
    free(variaveis);
    free(x);
}*/
double** gerarMatriz(){

    double** m = alocarMatriz(MAX);
    int cont = 0;

    //Preenche a matriz diagonal inferior
    for(int i = 0; i < MAX; i++){

        cont = 1;
        for(int j = 1; j < MAX; j++){
    
            m[j][i] = cont;
            if(i != j && j > i){
                
                cont++;
            }
            
        }   
    }

    int aux = cont = 21;//a PRIMEIRA VERSAO CONT É IGUAL A 21

    //Preenche a matriz diagonal superior
    for(int i = 0; i < MAX; i++){

        cont--;
        for(int j = MAX - 1; j > i; j--){
            m[i][j] = cont;
            cont--;
            
        }
        cont = aux - 1;
        aux--;
    }

    //Preenche a diagonal principal
    for (int i = 0; i < MAX; ++i){
        m[i][i] = 0;
    }

    return m;
}

double* gerarTermosIndependentes(){

    double* b = alocarVetor(MAX);
    //Preenche o vetor b
    for (int i = 0; i < MAX; ++i){
        b[i] = i + 1;
    }

    return b;
}

void inversa_LU(double** matriz, double* vetorB ,int ordem){

    double** L = alocarMatriz(ordem);
    double** U;
    double** I = alocarMatriz(ordem);

    for(int i = 0;i < ordem;i++){
        
        L[i][i] = 1;
        I[i][i] = 1;
    }

    int variaveis[ordem],variaveis2[ordem];
    
    //inicializa o variaveis em ordem crescente.
    for(int i = 0; i < ordem;i++){
       
        variaveis[i] = i; //x[0],x[1],x[2],...,x[n-1].          
        variaveis2[i] = i;
        
    }


    //ETAPA DE ESCALONAMENTO
    for(int k = 0; k < ordem - 1; k++){

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

                double temp2 = I[j][k];
                I[j][k] = I[j][maxIndexC];
                I[j][maxIndexC] = temp2;
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
            printf("entei, %d %d\n",maxIndexL,k);
            /*troca a equação k pela equação com o
              maior k-ésimo coeficiente em módulo. Troca o pivô.
             */
            for(int j = 0; j < ordem; j++) {
                double temp = matriz[k][j];
                matriz[k][j] = matriz[maxIndexL][j];
                matriz[maxIndexL][j] = temp;

                double temp2 = I[k][j];
                I[k][j] = I[maxIndexL][j];
                I[maxIndexL][j] = temp2;
            }

            int tempV = variaveis2[k];
            variaveis2[k] = variaveis2[maxIndexL];
            variaveis2[maxIndexL] = tempV;
        }
      
        if(matriz[k][k] == 0){
            printf("A matriz dos coeficientes é singular\n");
            return;
        }else{
            //realiza o escalonamento
            for(int m = k + 1; m < ordem; m++){
                /*Esse loop defini o multitrocarLicador da linha*/
                double F = -matriz[m][k] / matriz[k][k]; 

                matriz[m][k] = 0; //evita uma iteração
                
                L[m][k] = -F;

                for(int l = k + 1; l < ordem; l++){
                    //Atualização da linha, matriz[k][l] é o elemento da linha do pivô
                    matriz[m][l] = matriz[m][l] + F * matriz[k][l];
                }
            }
        }
     
    }

    U = matriz;

    
 double solut[ordem],solut2[ordem];
        int ind;
    

  
    printf("\n-----------------------------------------------------------------------------\n");
    
    
    double* vetorSolucao_matrizL;
    double* vetorSolucao_matrizU;

    for(int k = 0;k < ordem; k++){

        vetorSolucao_matrizL = alocarVetor(ordem);
        vetorSolucao_matrizU = alocarVetor(ordem);

            for (int j = 0; j < ordem; ++j){
                  vetorB[j] = I[j][k];
            }

            vetorSolucao_matrizL = triangularInferior(L,vetorB,vetorSolucao_matrizL,ordem);

            vetorSolucao_matrizU = triangularSuperior(U,vetorSolucao_matrizL,vetorSolucao_matrizU,ordem);
            
            for(int i = 0; i < ordem;i++){
                for(int j = 0;j < ordem; j++){
                   
                    if(i == variaveis[j])
                        ind = j;
                }
               
                solut[i] = vetorSolucao_matrizU[ind];
            }
            
            for(int i = 0; i < ordem;i++){
                for(int j = 0;j < ordem; j++){
                   
                    if(i == variaveis2[j])
                        ind = j;
                }
               
                solut2[i] = solut[ind];
            }

            for (int i = 0; i < ordem; i++){
                I[i][k] = solut2[i];
            }

        free(vetorSolucao_matrizL);
        free(vetorSolucao_matrizU);
    }

     
    imprimirMatriz(I,ordem);
    
    


    liberarMatriz(L,ordem);
    liberarMatriz(I,ordem);


}

void decomposicaoLU_PivoteamentoTotal(double** matriz, double* vetorB ,int ordem){

    double** L = alocarMatriz(ordem);
    double** U;
    int i, j, k, trocarC, trocarL;
    double F, maxIndexC, maxIndexL, temp;
    int* variaveis = (int*) malloc(ordem * sizeof(int));

    for(int i = 0;i < ordem;i++){
        variaveis[i] = i;
        L[i][i] = 1;
    }

    

    U = matriz;

    for(int i = 0; i < ordem; i++){

        maxIndexL = fabs(U[i][i]);
        maxIndexC = fabs(U[i][i]);     

        for(int j = i + 1; j < ordem; j++){           
            if((fabs(U[i][j])) > maxIndexC){
                maxIndexC = fabs(U[i][j]);
                trocarC = j;
            }
            
            if((fabs(U[j][i])) > maxIndexL){
                maxIndexL = fabs(U[j][i]);
                trocarL = j;
            }
        }

        if((maxIndexL > maxIndexC) || (maxIndexL == maxIndexC)){
            
            if(fabs(U[i][i]) != maxIndexL){

                for(int k = 0; k < ordem; k++){
                    temp = U[trocarL][k];
                    U[trocarL][k] = U[i][k];
                    U[i][k] = temp;

                    temp = L[trocarL][k];
                    L[trocarL][k] = L[i][k];
                    L[i][k] = temp;
                }
                double temp = vetorB[i];
                vetorB[i] = vetorB[trocarL];
                vetorB[trocarL] = temp;
            }

        }else if(maxIndexC > maxIndexL){
            
            if(fabs(U[i][i]) != maxIndexC){

                for(int k = 0; k < ordem; k++){
                    temp = U[k][trocarC];
                    U[k][trocarC] = U[k][i];
                    U[k][i] = temp;
                }

                temp = variaveis[i];
                variaveis[i] = variaveis[trocarC];
                variaveis[trocarC] = temp;
            }
        }
        
        for(int k = i + 1; k < ordem; k++){
            F = -( U[k][i] / U[i][i] );
            L[k][i] = -F;

            for(int j = i; j < ordem; j++){
                if(j == i){
                    U[k][j] = 0;
                }
                else{
                    U[k][j] = U[k][j] + (F * U[i][j]);
                }
            }
        }

    }

    for(int i = 0; i < ordem; i++){
        L[i][i] = 1;
    }


    double* vetorSolucao_matrizL = alocarVetor(ordem);
    vetorSolucao_matrizL = triangularInferior(L,vetorB,vetorSolucao_matrizL,ordem);

    double solut[ordem];

    for(int k = 0; k < ordem; k++){
        for(int i = 0; i < ordem; i++){
            int ind = variaveis[i];
            solut[ind] = vetorSolucao_matrizL[i];
        }
    }

    printf("\n-----------------------------------------------------------------------------\n");

    printf("\nVetor solucao da matriz L\n");
    for (int i = 0; i < ordem; i++){
        printf("x_L[%d] = %.5lf\n",i,solut[i]);
    }


    double* vetorSolucao_matrizU = alocarVetor(ordem);
    vetorSolucao_matrizU = triangularSuperior(U,vetorSolucao_matrizL,vetorSolucao_matrizU,ordem);


    for(int k = 0; k < ordem; k++){
        for(int i = 0; i < ordem; i++){
            int ind = variaveis[i];
            solut[ind] = vetorSolucao_matrizU[i];
        }
    }

    printf("\nVetor solucao da matriz U\n");
    for (int i = 0; i < ordem; i++){
        printf("x_U[%d] = %.5lf\n",i,solut[i]);
    }

    printf("Matriz triangular\n");
    imprimirMatriz(L,ordem);
    printf("\nMatriz Superior\n");
    imprimirMatriz(U,ordem);
    printf("\nMatriz Escalonada\n");
    imprimirMatriz(matriz,ordem);

    liberarMatriz(L,ordem);
    free(vetorSolucao_matrizL);
    free(vetorSolucao_matrizU);
    free(variaveis);
}

void inversa(double** matriz, double* vetorB ,int ordem){

    double** L = alocarMatriz(ordem);
    double** I = alocarMatriz(ordem);
    double** U;
    int i, j, k, trocarC, trocarL;
    double F, maxIndexC, maxIndexL, temp;
    int* variaveis = (int*) malloc(ordem * sizeof(int));

    for(int i = 0;i < ordem;i++){
        variaveis[i] = i;
        L[i][i] = 1;
        I[i][i] = 1;
    }

    

    U = matriz;

    for(int i = 0; i < ordem; i++){

        maxIndexL = fabs(U[i][i]);
        maxIndexC = fabs(U[i][i]);     

        for(int j = i + 1; j < ordem; j++){           
            if((fabs(U[i][j])) > maxIndexC){
                maxIndexC = fabs(U[i][j]);
                trocarC = j;
            }
            
            if((fabs(U[j][i])) > maxIndexL){
                maxIndexL = fabs(U[j][i]);
                trocarL = j;
            }
        }

        if((maxIndexL > maxIndexC) || (maxIndexL == maxIndexC)){
            
            if(fabs(U[i][i]) != maxIndexL){

                for(int k = 0; k < ordem; k++){
                    temp = U[trocarL][k];
                    U[trocarL][k] = U[i][k];
                    U[i][k] = temp;

                    temp = L[trocarL][k];
                    L[trocarL][k] = L[i][k];
                    L[i][k] = temp;

                    temp = I[trocarL][k];
                    I[trocarL][k] = I[i][k];
                    I[i][k] = temp;
                }
                double temp = vetorB[i];
                vetorB[i] = vetorB[trocarL];
                vetorB[trocarL] = temp;
            }

        }else if(maxIndexC > maxIndexL){
            
            if(fabs(U[i][i]) != maxIndexC){

                for(int k = 0; k < ordem; k++){
                    temp = U[k][trocarC];
                    U[k][trocarC] = U[k][i];
                    U[k][i] = temp;
                }

                temp = variaveis[i];
                variaveis[i] = variaveis[trocarC];
                variaveis[trocarC] = temp;
            }
        }
        
        for(int k = i + 1; k < ordem; k++){
            F = -( U[k][i] / U[i][i] );
            L[k][i] = -F;

            for(int j = i; j < ordem; j++){
                if(j == i){
                    U[k][j] = 0;
                }
                else{
                    U[k][j] = U[k][j] + (F * U[i][j]);
                }
            }
        }

    }

    for(int i = 0; i < ordem; i++){
        L[i][i] = 1;
    }


    printf("\n-----------------------------------------------------------------------------\n");

    double* vetorSolucao_matrizL;
    double* vetorSolucao_matrizU;
    double** resultadoI  = alocarMatriz(ordem);

    for(int k = 0;k < ordem; k++){

        vetorSolucao_matrizL = alocarVetor(ordem);
        vetorSolucao_matrizU = alocarVetor(ordem);

            for (int j = 0; j < ordem; ++j){
                  vetorB[j] = I[j][k];
            }

            vetorSolucao_matrizL = triangularInferior(L,vetorB,vetorSolucao_matrizL,ordem);

            vetorSolucao_matrizU = triangularSuperior(U,vetorSolucao_matrizL,vetorSolucao_matrizU,ordem);
           
            for (int i = 0; i < ordem; i++){
                int ind = variaveis[i];
                resultadoI[ind][k] = vetorSolucao_matrizU[i];
            }

        free(vetorSolucao_matrizL);
        free(vetorSolucao_matrizU);
    }


    imprimirMatriz(resultadoI,ordem);

    liberarMatriz(resultadoI,ordem);
    liberarMatriz(L,ordem);
    free(variaveis);
    liberarMatriz(I,ordem);
}
