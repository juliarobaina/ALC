#include "seidel-prova.c"

int main(int argc, char const *argv[]){
	

	double** matriz = gerarMatriz(30);
	double* b = gerarTermosIndependentes(30);

	double* x = alocarVetor(30);

	for (int i = 0; i < 30; ++i)
	{
		x[i] = 0;
	}

	

	double* vetorSolucao = alocarVetor(30);


	vetorSolucao = sor(1000,30,b,matriz,x,0.5);

	printf("\n");
	imprimirVetorSolucao(30,vetorSolucao);

	printf("-----------------------------------------------------------\n");
	
	/*double** m = alocarMatriz(3,3);

	double* b2 = alocarVetor(3);
	b2[0] = 1;
	b2[1] = 0;
	b2[2] = 0;

	double* x2 = alocarVetor(3);

	x2[0] = 0;
	x2[1] = 0;
	x2[2] = 0;

	for (int i = 0; i < 3; i++){
		for(int j = 0; j < 3;j++){
			printf("a[%d][%d] = ",i,j );
			scanf("%lf",&m[i][j]);
		}
	}

	double* v = alocarVetor(3);

	v = sor(3,3,b2,m,x2,0.5);

	imprimirVetorSolucao(3,v);*/



	//free(v);//liberando o vetorSolucao libero o x
	free(x);
	free(b);
	liberarMatriz(matriz,30);
	
	









	return 0;
}