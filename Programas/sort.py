#!/usr/bin/python3

import sys
import timeit

def QuickSort(ini, fim, vetor):
	vetor.sort()

def imprimeVetor(ptr):
	for elemento in ptr:
		print(elemento, end = " ")
	
	print("")


arr = [int(x) for x in input().split()] 

print(timeit.timeit('QuickSort(0, len(arr)-1, arr)', number=1, globals=globals()), file=sys.stderr, end=" S\n")

#imprimeVetor(arr)
