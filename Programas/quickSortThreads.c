#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timeMeasurement.h"

#define REALLOCSIZE 10000
#define MAX_THREADS	4
//#define __PIVO_SIMPLES_

unsigned long encontra_pivo(unsigned int vetor[], int ini, int fim){
    #ifdef __PIVO_SIMPLES_
    return ini;
    #else
    unsigned int meio = (ini+fim)/2;

    if(((vetor[meio]>vetor[ini])&&(vetor[meio]<vetor[fim]))||
       ((vetor[meio]>vetor[fim])&&(vetor[meio]<vetor[ini]))){
            return meio;
    }else if(((vetor[ini]>vetor[meio]) && (vetor[ini]<vetor[fim]))||
             ((vetor[ini]>vetor[fim] ) && (vetor[ini]<vetor[meio]))){
            return ini;
    }else{
        return fim;
    }
    #endif // __PIVO_SIMPLES_
}

void trocar(unsigned int *a, unsigned int *b){
    unsigned int aux = *a;
    *a = *b;
    *b = aux;

}

typedef struct{
	int ini;
	int fim;
	unsigned int *vetor;
}quickParam_t;

int nthreads = 0;

void *QuickSortThread(void *param){
    	unsigned int pos_pivo, i, j;
	
	int ini = ((quickParam_t *)param)->ini;
	int fim = ((quickParam_t *)param)->fim;
	unsigned int *vetor = ((quickParam_t *)param)->vetor;


    	if(fim - ini < 2){
        	if(fim - ini == 1){
            		if(vetor[ini]>vetor[fim]){
                		trocar(&vetor[ini], &vetor[fim]);
            		}
        	}
    	}else{
        	pos_pivo = encontra_pivo(vetor, ini, fim);
        	trocar(&vetor[pos_pivo], &vetor[fim]);
        	i = ini;
        	j = fim - 1;
        	while(j>=i){
        	    while((i<=j)&&(vetor[i]<vetor[fim])){
        	        i = i + 1;
        	    }
        	    while((j>=i)&&(vetor[j]>vetor[fim])){
        	        j = j - 1;
        	    }
        	    if(j>=i){
        	        trocar(&vetor[i], &vetor[j]);
        	        i = i + 1;
        	        j = j - 1;
        	    }
        	}
        	trocar(&vetor[i], &vetor[fim]);

		quickParam_t param1, param2;
		pthread_t threads[2];
		int criou1, criou2;

		param1.ini = ini;
		param1.fim = i-1;
		param1.vetor = vetor;

		param2.ini = i+1;
		param2.fim = fim;
		param2.vetor = vetor;
		
		criou1 = criou2 = 0;

		if(nthreads<MAX_THREADS){
			nthreads++;	// Tem uma condição de corrida aqui, mas não é tão ruim. Vamos ter apenas mais de dois threads
					// rodando ao mesmo tempo
			criou1 = 1;
			pthread_create(&threads[0], NULL, QuickSortThread, (void*)&param1);
		}
		
		if(nthreads<MAX_THREADS){
			nthreads++;	// Aqui também
			criou2 = 1;
			pthread_create(&threads[1], NULL, QuickSortThread, (void*)&param2);
		}

		if(!criou1){
			QuickSortThread(&param1);
		}

		if(!criou2){
			QuickSortThread(&param2);
		}
		
		if(criou1){
			pthread_join(threads[0], NULL);
			nthreads--;
		}

		if(criou2){
			pthread_join(threads[1], NULL);
			nthreads--;
		}
    	}

	return NULL;
}

void imprimeVetor(unsigned int ptr[], unsigned int tamanho){
	unsigned int i;
	for(i=0; i < tamanho; i++){
		printf("%u ", ptr[i]);
	}
	printf("\n");
}

int main(int argc, char **argv){
	int inteiro;
	unsigned int *ptr=NULL;
	unsigned int contador=0, tamanho=0;

	while(fscanf(stdin,"%u", &inteiro) != EOF){
		if(tamanho <= contador){
			tamanho += REALLOCSIZE;
			ptr = (unsigned int*) realloc((void*)ptr, tamanho*sizeof(unsigned int));
		}
		ptr[contador] = inteiro;
		contador++;
	}
	
	timespec_t tempo, aux;
	quickParam_t paramthread;	

	paramthread.ini = 0;
	paramthread.fim = contador-1;
	paramthread.vetor = ptr;

	timeEnter(&tempo);
	QuickSortThread(&paramthread);
	getTimeElapsed(&tempo, &aux);

	printTimeElapsed3("Tempo gasto ", &aux);

//	imprimeVetor(ptr, contador);
	
	return 0;
}
