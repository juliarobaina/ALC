#include "metodosDiretos.c"

int main(){

	int ordem, esc,op = 100;

	

	do{
		int cont = 0;

		printf("Digite a ordem da matriz: ");
		scanf("%d",&ordem);

		double** m = alocarMatriz(ordem);
		double* b = alocarVetor(ordem);

		double* vetorSolucao = alocarVetor(ordem);

		printf("Digite os valores da matriz:\n");
		
		for (int i = 0; i < ordem; i++){
			for (int j = 0; j < ordem; j++){
				printf("a[%d][%d] = ",i,j);
				scanf("%lf",&m[i][j]);
			}
		}

		printf("\nDigite o vetor de termos independentes:\n");

		for (int i = 0; i < ordem; ++i){
			printf("b[%d] = ",i);
			scanf("%lf",&b[i]);
		}

		printf("\n");

		printf("Matriz:\n");
		imprimirMatriz(m,ordem);

		printf("Vetor de termos independentes:\n");
		imprimirVetor(b,ordem);

	
		printf("\nDigite:\n");
		printf("1 - Triangular Inferior\n");
		printf("2 - Triangular Superior\n");
		printf("3 - Eliminacao de Gauss com pivoteamento total\n");
		printf("4 - Eliminacao de Gauss com pivoteamento parcial\n");
		printf("5 - Eliminacao de Gauss\n");
		printf("6 - Decomposicao LU\n");
		printf("7 - Fatoracao de Cholesky\n");
		printf("200 - Sair\n");
		scanf("%d",&esc);

		
		
		switch(esc){
			case 1:
				vetorSolucao = triangularInferior(m,b,vetorSolucao,ordem);
				printf("\nVetor solucao - Triangular Inferior\n");
			    while(cont < ordem){

			    	printf("x[%d] = %.5lf\n",cont,vetorSolucao[cont]);
			    
			   		cont++;
			    }
			break;
			case 2:
				vetorSolucao = triangularSuperior(m,b,vetorSolucao,ordem);
				printf("\nVetor solucao - Triangular Superior\n");
			    while(cont < ordem){

			    	printf("x[%d] = %.5lf\n",cont,vetorSolucao[cont]);
			    
			   		cont++;
			    }
			break;
			case 3:
				eliminacaoGauss_pivoteamentoTotal(m,b,ordem);
				
				printf("\nMatriz Escalonada com pivoteamento total:\n");
				imprimirMatriz(m,ordem);
				
				printf("\nVetor de termos independentes:\n");
				imprimirVetor(b,ordem);
				
			break;
			case 4:
				eliminacaoGauss_pivoteamentoParcial(m,b,ordem);
				
				printf("\nMatriz Escalonada com pivoteamento prcial:\n");
				imprimirMatriz(m,ordem);
				
				printf("\nVetor de termos independentes:\n");
				imprimirVetor(b,ordem);
				
			break;
			case 5:
				eliminacaoGauss(m,b,ordem);
				
				printf("\nMatriz Escalonada:\n");
				imprimirMatriz(m,ordem);
				
				printf("\nVetor de termos independentes:\n");
				imprimirVetor(b,ordem);
				
			break;
			case 6:
				decomposicaoLU(m,b,ordem);
			break;
			case 7:
				cholesky(m,b,ordem);
			break;
			case 200:
				op = 200;
			break;
			default:
				printf("Opcao errada\n");
		}
		if(esc != 200){
			printf("\n\nDeseja fazer outra operacao?\n");
			printf("100 - sim\n");
			printf("200 - nao\n");
			scanf("%d",&op);
			printf("\n\n\n******************************************************************************\n\n");	
		}
		
		free(vetorSolucao);
		free(b);
		liberarMatriz(m,ordem);
	}while(op != 200);

	

	

	return 0;
}
