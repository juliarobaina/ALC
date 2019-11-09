#include "metodosDiretos.c"

int main(){

	int ordem, esc;

	printf("Digite a ordem da matriz: ");
	scanf("%d",&ordem);

	double** m = alocarMatriz(ordem);
	double* b = alocarVetor(ordem);

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
	scanf("%d",&esc);

	double* vetorSolucao = alocarVetor(ordem);

	switch(esc){
		case 1:
			vetorSolucao = triangularInferior(m,b,vetorSolucao,ordem);
			imprimirVetor(vetorSolucao, ordem);
		break;
		case 2:
			vetorSolucao = triangularSuperior(m,b,vetorSolucao,ordem);
			imprimirVetor(vetorSolucao, ordem);
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
		default:
			printf("Opcao errada\n");
			exit(1);
	}

	

	free(vetorSolucao);
	free(b);
	liberarMatriz(m,ordem);

	return 0;
}
