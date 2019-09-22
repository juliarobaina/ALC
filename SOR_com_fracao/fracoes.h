#ifndef _FRACOES_H
#define _FRACOES_H

#include "stdlib.h"

	struct fracao{
		int numerador;
		int denominador;
	};

	typedef struct fracao Fracao;

	int somarFracao(int numerador1,int numerador2,int denominador1,int denominador2,int escolha);
	int dividirFracao(int numerador1,int numerador2,int denominador1,int denominador2,int escolha);
	int multiplicarFracao(int numerador1,int numerador2,int denominador1,int denominador2,int escolha);
	int MDC(int numerador,int denominador);



#endif