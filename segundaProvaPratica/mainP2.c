#include "../metodosDiretos.c"

int main(){

	//double* x = alocarVetor(MAX);
	//double* vetorSolucao = alocarVetor(MAX);

	int ordem, esc,op = 100;

	

	do{

		double** m = gerarMatriz();
		double* b = gerarTermosIndependentes();
	
		printf("\nDigite:\n");
		printf("1 - Eliminacao de Gauss com pivoteamento total\n");
		printf("2 - Eliminacao de Gauss com pivoteamento parcial\n");
		printf("3 - Decomposicao LU\n");
		printf("4 - Fatoracao de Cholesky\n");
		printf("200 - Sair\n");
		scanf("%d",&esc);

		
		switch(esc){
			case 1:
				eliminacaoGauss_pivoteamentoTotal(m,b,MAX);
				
				printf("\nMatriz Escalonada com pivoteamento total:\n");
				imprimirMatriz(m,MAX);
				
				printf("\nVetor de termos independentes:\n");
				imprimirVetor(b,MAX);
				
			break;
			case 2:
				eliminacaoGauss_pivoteamentoParcial(m,b,MAX);
				
				printf("\nMatriz Escalonada com pivoteamento prcial:\n");
				imprimirMatriz(m,MAX);
				
				printf("\nVetor de termos independentes:\n");
				imprimirVetor(b,MAX);
				
			break;
			case 3:
				decomposicaoLU(m,b,MAX);
			break;
			case 4:
				cholesky(m,b,MAX);
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
		
		free(b);
		liberarMatriz(m,MAX);
	}while(op != 200);

	/*free(b);
	free(x);
	free(vetorSolucao);*/

	return 0;
}