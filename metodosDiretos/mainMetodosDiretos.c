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

	printf("Matriz e vetor de termos independentes\n");

	imprimirMatriz(m,ordem);

	for (int i = 0; i < ordem; i++){
		printf("b[%d] = %.5lf\n",i,b[i]);
	}

	printf("Digite:\n");
	printf("1 - Triangular Inferior\n");
	printf("2 - Triangular Superior\n");
	scanf("%d",&esc);

	double* vetorSolucao = alocarVetor(ordem);

	switch(esc){
		case 1:
			vetorSolucao = triangularInferior(m,b,vetorSolucao,ordem);
		break;
		case 2:
			vetorSolucao = triangularSuperior(m,b,vetorSolucao,ordem);
		break;
		default:
			printf("Opcao errada\n");
			exit(1);
	}

	

	for (int i = 0; i < ordem; i++){
		printf("%.5lf\n",vetorSolucao[i]);
	}	

	free(vetorSolucao);


	return 0;
}