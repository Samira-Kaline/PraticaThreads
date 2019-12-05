#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define     QUANTIDADE_NUMEROS      100 // Utilize no máximo 100000000
#define     MAXIMO_NUMERO           9999999
#define     NUMERO_LINHAS           1
#define     GABARITO                "OUT.txt"
#define     CRESCENTE               0
#define     DECRESCENTE             1
#define     ALEATORIO               2
#define     ORDENACAO               CRESCENTE

unsigned int encontra_pivo(unsigned int vetor[], unsigned int ini, unsigned int fim){
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

int main(int argc, char **argv){
    unsigned long n_numeros = QUANTIDADE_NUMEROS;
    unsigned int n_maximo = MAXIMO_NUMERO;
    unsigned int n_linhas = NUMERO_LINHAS;
    unsigned long numeros_na_linha;
    unsigned int i, j;
    unsigned int *vetor=(unsigned int*)malloc(sizeof(unsigned int)*QUANTIDADE_NUMEROS);
    char gabarito[255];
    FILE    *out;

    if(((argc>1)&&(!strcmp(argv[1],"-h"))) ||(argc>5)){
        printf("Use %s [numeros por linha] [maior numero] [numeros de linhas] [gabarito]\n", argv[0]);
        exit(1);
    }

    if(argc>1){
        n_numeros = atoi(argv[1]);
    }
    if(argc>2){
        n_maximo = atoi(argv[2]);
    }
    if(argc>3){
        n_linhas = atoi(argv[3]);
    }

    if(argc>4){
        strcpy(gabarito,argv[4]);
    }else{
        strcpy(gabarito, GABARITO);
    }

    out = fopen(gabarito, "w");

    for(i=0; i<n_linhas; i++){
        numeros_na_linha = n_numeros;//((unsigned int)((((float) n_numeros)) * ((float) rand()) / ((float) RAND_MAX)))+1;

        for(j=0; j<numeros_na_linha; j++){
            vetor[j] = ((unsigned int)((((float) n_maximo)) * ((float) rand()) / ((float) RAND_MAX)));
        }

	for(j=0;j<numeros_na_linha;j++){
            fprintf(stdout, "%u ", vetor[j]);
        }
        fprintf(stdout,"\n");

        QuickSort(0, numeros_na_linha-1, vetor);

        for(j=0;j<numeros_na_linha;j++){
            fprintf(out, "%u ", vetor[j]);
        }
        fprintf(out,"\n");
    }
    fclose(out);

    return 0;
}
