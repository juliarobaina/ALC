#include "seidelProva.h"

double** gerarMatriz(int n){

    double** matriz = alocarMatriz(n,n);

    for(int i=0;i<n;i++){
           

        for(int j=0;j<n;j++){
            
            matriz[i][j] = 0;            
        }

        if(i > 0 && i < 29){
            
            matriz[i][i-1] = 1;
            matriz[i][i] = matriz[0][0];
            matriz[i][i+1] = 1;
        }
                
        matriz[0][0] = -2*(1+(0.1*0.1));
        matriz[0][1] = 1;
        matriz[29][28] = 1;
        matriz[29][29] = matriz[0][0];
	}


    return matriz;
}

double* gerarTermosIndependentes(int n){

    double* b = alocarVetor(n);

    for(int i=0;i<n;i++){
           

        if(i > 0 && i < 29){
            b[i] = 0;
        }else{
            b[i] = 1;
        }
       
    }

    return b;
}

void imprimirVetorSolucao(int numLinhas,double* x){

    for (int i = 0; i < numLinhas; i++){
        
        printf(" vetSol[%d] = %lf\n",i+1,x[i]);
           
    }
}

void calcularErro(double* erro, double* x,int numLinhas){

    double maiorErro = erro[0];

    double maiorX = x[0];
    for (int i = 0; i < numLinhas; i++){
       
        if(erro[i] > maiorErro)
            maiorErro = erro[i];
        

        if(x[i] > maiorX)
            maiorX = x[i];      
    }

    printf("Maior erro %.5lf\n",maiorErro);
    printf("Maior X %.5lf\n",maiorX);
    printf("Erro %.5lf\n",(fabs(maiorX - maiorErro))/maiorX);

}

double* seidel(int numIteracoes,int numLinhas, double* b, double** a,double* x){

    double *y = alocarVetor(numLinhas);
    double *x_velho = alocarVetor(numLinhas);
    double *erro = alocarVetor(numLinhas);//para exibir a margem de erro
    double temp;

    int sair = 0;
    int k = 0;

    for(int i = 0; i < numLinhas;i++){
        x_velho[i] = x[i];
    }

    while(k < numIteracoes && sair != 1){
        
        for (int i = 0 ; i < numLinhas; i++){
            y[i] = b[i];
            for (int j = 0; j < numLinhas; j++){
                if(j != i)
                    y[i] = y[i] - a[i][j] * x[j];
               
            }
            
            y[i] = y[i] / a[i][i];
            temp = x[i];
            x[i] = y[i];
            y[i] = temp;
            erro[i] = x_velho[i];//Para exibir a margem de erro
        }

        for(int i = 0; i < numLinhas;i++){
           
            if((fabs(x[i] - x_velho[i])) < 0.000000001){
               
                sair = 1;
               break;
            }

        }

        for(int i = 0; i < numLinhas;i++){
            x_velho[i] = x[i];
        }

        k++;
    }
  
   /* for (int i = 0 ; i < numLinhas; i++){
        y[i] = b[i];
        for (int j = 0; j < numLinhas; j++){
            if(j != i)
                y[i] = y[i] - a[i][j] * x[j];
            
        }
        
        y[i] = y[i] / a[i][i];
        temp = x[i];
        x[i] = y[i];
        y[i] = temp;
    }

    
    int k = 0;
    while(sair != 1){ 
       
        for (int i = 0 ; i < numLinhas; i++){
            y[i] = b[i];
            for (int j = 0; j < numLinhas; j++){
                if(j != i)
                    y[i] = y[i] - a[i][j] * x[j];
                
            }
            
            y[i] = y[i] / a[i][i];
            temp = x[i];
           // x_novo[i] = x_velho[i];
            x[i] = y[i];
            y[i] = temp;
        }

     for(int i = 0; i < numLinhas;i++){
            
        if((fabs(x[i] - x_velho[i])) < 0.000000001 || k == 30){
           
            sair = 1;
            break;
        }

     }
     k++;
    }*/

   // calcularErro(erro,x,numLinhas); Tirar o comentario depois, em baixo tb
   // printf("Foram %d iteracoes\n",k);
    /*double maiorErro = erro[0];

    double maiorX = x[0];
    for (int i = 0; i < numLinhas; i++){
       
        if(erro[i] > maiorErro){
            maiorErro = erro[i];
        }

        if(x[i] > maiorX)
            maiorX = x[i];

        
        printf(" vetSol[%d] = %.5lf\n",i+1,erro[i]);        
    }
    printf("Maior erro %.5lf\n",maiorErro);
    printf("Maior X %.5lf\n",maiorX);
    printf("Erro %.5lf\n",(fabs(maiorX - maiorErro))/maiorX);*/
    free(erro);
    free(y);
    free(x_velho);
    
    return x;
}

double* sor(int numIteracoes,int numLinhas, double* b, double** a,double* x,double w){

    int k = 0, sair = 0;
    double *y = calloc(numLinhas,sizeof(double));
    double *vetorSolucao = calloc(numLinhas,sizeof(double));
    double *x_velho = alocarVetor(numLinhas);
    double *x2 = alocarVetor(numLinhas);
    double* valorSeidel = alocarVetor(numLinhas);

    for(int i = 0; i < numLinhas;i++){
        
        x_velho[i] = x[i];
       
        x2[i] = x[i];
    }
    
    while(k < numIteracoes && sair != 1){
        
        valorSeidel = seidel(k+1,numLinhas,b,a,x2);
      // imprimirVetorSolucao(numLinhas,valorSeidel);
       // printf("Acaba por aqui seidel %d\n",k+1);
        for (int i = 0 ; i < numLinhas; i++){
            
            y[i] = b[i];
            
            for (int j = 0; j < numLinhas; j++){
                if(j != i){
                    y[i] = y[i] - a[i][j] * x[j];                   
                }
                
                
            }
            
            y[i] = ((y[i] / a[i][i]) * (1 - w)) + (valorSeidel[i] * w);
        
            vetorSolucao[i] = y[i];
            
        }   

        for (int p = 0; p < numLinhas; p++)
        {
            x[p] = vetorSolucao[p];
        }
        

        for(int i = 0; i < numLinhas;i++){
           
            if((fabs(x[i] - x_velho[i])) < 0.000000001){
               
                sair = 1;
                break;
            }
        }

        for(int i = 0; i < numLinhas;i++){
           x_velho[i] = x[i];
           x2[i] = 0;
        }

        k++;
    }

    printf("Foram %d iteracoes\n",k);

    free(y);
    free(x_velho);
    free(valorSeidel);
    free(vetorSolucao);
    //free(x2);

    return x;
}

