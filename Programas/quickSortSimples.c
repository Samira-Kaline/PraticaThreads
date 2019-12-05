#include <stdio.h>
#include <stdlib.h>
#include "timeMeasurement.h"

#define REALLOCSIZE 10000
//#define __PIVO_SIMPLES_

unsigned int encontra_pivo(unsigned int vetor[], unsigned  int ini, unsigned int fim){
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

void QuickSort(int ini, int fim, unsigned int vetor[]){
    int pos_pivo, i, j;
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
        QuickSort(ini, i-1, vetor);
        QuickSort(i+1, fim, vetor);
    }
}

void imprimeVetor(unsigned int ptr[], int tamanho){
	int i;
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
			tamanho += REALLOCSIZE		;
			ptr = (unsigned int*) realloc((void*)ptr, tamanho*sizeof(unsigned int));
		}
		ptr[contador] = inteiro;
		contador++;
	}

	timespec_t tempo, aux;

	timeEnter(&tempo);
	QuickSort(0, contador-1, ptr);
	getTimeElapsed(&tempo, &aux);
	printTimeElapsed3("Tempo gasto ", &aux);

//	imprimeVetor(ptr, contador);
	
	return 0;
}
