#!/usr/bin/env python3

from random import randint
import threading
import sys
import timeit

def qsort(a, l, r):
    #print("thread {} is sorting {}".format(threading.current_thread(), a[l:r]))

    i = l
    j = r
    pivo = a[(l + r) // 2]
    temp = 0
    while i <= j:
        while pivo > a[i]:
            i += 1
        while pivo < a[j]:
            j -= 1
        if i <= j:
            temp = a[i]
            a[i] = a[j]
            a[j] = temp
            i += 1
            j -= 1

    lthread = None
    rthread = None

    if l < j:
        lthread = threading.Thread(target=qsort, args=(a, l, j))
        lthread.start()

    if i < r:
        rthread = threading.Thread(target=qsort, args=(a, i, r))
        rthread.start()

    if lthread is not None:
        lthread.join()
    if rthread is not None:
        rthread.join()
    return a



#O ERRO TA AQUI
arr = [int(x) for x in input().split()]
print(timeit.timeit('qsort(arr, 0, len(arr)-1)', number=1, globals=globals()), file=sys.stderr, end=" S\n")
