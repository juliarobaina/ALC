#include <stdio.h>
#include <stdlib.h>
struct fracao{
	int numerador;
	int denominador;
};
struct fracao Fracao[2];

int main(){
	
	int esc;
	int sair;
	
	while(1){
		printf("Escolha a operação:\n");
		printf("1 - Soma\n");
		printf("2 - Divisão\n");
		printf("30 - Sair\n");
		scanf("%d",&esc);

		if(esc == 30) exit(1);

		
		printf("Digite o numerador1: ");
		scanf("%d",&Fracao[0].numerador);
		printf("Digite o numerador2:");
		scanf("%d",&Fracao[1].numerador);
		printf("-------------------------\n");
		printf("Digite o denominador1: ");
		scanf("%d",&Fracao[0].denominador);
		printf("Digite o denominador2: ");
		scanf("%d",&Fracao[1].denominador);


		int resultNumerador,resultDenominador,aux1,aux2;

		switch(esc){
			case 1:
				if(Fracao[0].denominador == Fracao[1].denominador){
					resultNumerador = Fracao[0].numerador + Fracao[1].numerador;
					resultDenominador = Fracao[0].denominador;
				}else{
					resultDenominador = Fracao[0].denominador * Fracao[1].denominador;
					aux1 = Fracao[1].denominador * Fracao[0].numerador;
					aux2 = Fracao[0].denominador * Fracao[1].numerador;
					resultNumerador = aux1 + aux2;
				}

				break;
			case 2:
				resultNumerador = Fracao[0].numerador * Fracao[1].denominador;
				resultDenominador = Fracao[0].denominador * Fracao[1].numerador;
				break;
			default:
				printf("Opcao incorreta\n");
		}

		printf("O resultado é: \n");
		printf("%d\n",resultNumerador);
		printf("---\n");
		printf("%d\n",resultDenominador);
	}


	return 0;
}
