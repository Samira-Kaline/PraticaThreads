#!/usr/local/bin/python3

import sys
import timeit

def encontra_pivo(vetor, ini, fim):
    meio = (ini+fim)//2

    if(((vetor[meio]>vetor[ini]) and (vetor[meio]<vetor[fim])) or ((vetor[meio]>vetor[fim]) and (vetor[meio]<vetor[ini]))):
            return meio
    elif(((vetor[ini]>vetor[meio]) and (vetor[ini]<vetor[fim])) or ((vetor[ini]>vetor[fim] ) and (vetor[ini]<vetor[meio]))):
            return ini
    else:
        return fim

def trocar(vetor, a, b):
    aux = vetor[a]
    vetor[a] = vetor[b]
    vetor[b] = aux

def QuickSort(ini, fim, vetor):
    if(fim - ini < 2):
        if(fim - ini == 1):
            if(vetor[ini]>vetor[fim]):
                trocar(vetor, ini, fim)
    else:
        pos_pivo = encontra_pivo(vetor, ini, fim)
        trocar(vetor, pos_pivo, fim)
        i = ini
        j = fim - 1
        while(j>=i):
            while((i<=j) and (vetor[i]<vetor[fim])):
                i = i + 1
            
            while((j>=i) and (vetor[j]>vetor[fim])):
                j = j - 1
            
            if(j>=i):
                trocar(vetor, i, j)
                i = i + 1
                j = j - 1
        trocar(vetor, i, fim)
        QuickSort(ini, i-1, vetor)
        QuickSort(i+1, fim, vetor)

def imprimeVetor(ptr):
	for elemento in ptr:
		print(elemento, end = " ")
	
	print("")


arr = [int(x) for x in input().split()] 

print(timeit.timeit('QuickSort(0, len(arr)-1, arr)', number=1, globals=globals()), file=sys.stderr, end=" S\n")

#imprimeVetor(arr)
