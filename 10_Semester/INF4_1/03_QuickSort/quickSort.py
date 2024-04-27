import sys
sys.path.append('C:\Studium\10_Semester\INF4_1\Praktikum\GIT\AlgoDatSoSe24\SoSe24\algodat\foundation.py')

from foundation import *
from time import perf_counter as pfc

def quickSort(A :AlgoDatArray, left, right):
    if left < right:
        pivot = partition(A, left, right)
        quickSort(A, left, pivot - 1)
        quickSort(A, pivot + 1, right)


def quickSort2(A :AlgoDatArray, left, right):
    if left < right:
        pivot = partition2(A, left, right)
        quickSort2(A, left, pivot - 1)
        quickSort2(A, pivot + 1, right)


def partition(A :AlgoDatArray, left, right) -> int:
    pivot = A[right]
    i = left
    j = right - 1

    while i < j:
        while A[i] < pivot:
            i += 1
        while A[j] > pivot:
            j -= 1
        if i < j:
            A[i], A[j] = A[j], A[i]
            i += 1
            j -= 1
    
    if i == j and A[i] <= pivot:
        i += 1
    
    if A[i] != pivot:
        A[i], A[right] = A[right], A[i]

    return i


def partition2(A :AlgoDatArray, left, right) -> int:
    
    # find middle value of left, right and center
    valueLeft = A[left]
    valueRight = A[right]
    valueCenter = A[(left + right) // 2]

    if valueLeft < valueCenter < valueRight or valueRight < valueCenter < valueLeft:
        pivot = valueCenter
    elif valueCenter < valueLeft < valueRight or valueRight < valueLeft < valueCenter:
        pivot = valueLeft
    else:
        pivot = valueRight

    i = left
    j = right - 1

    while i < j:
        while A[i] < pivot:
            i += 1
        while A[j] > pivot:
            j -= 1
        if i < j:
            A[i], A[j] = A[j], A[i]
            i += 1
            j -= 1
    
    if i == j and A[i] <= pivot:
        i += 1
    
    if A[i] != pivot:
        A[i], A[right] = A[right], A[i]

    return i


if __name__ == "__main__":
    
    file = "seq3.txt"

    print("QuickSort pivot right:")
    A = read_int_sequence(file)
    start = pfc()
    quickSort(A, 0, len(A) - 1)
    end = pfc()
    print("Sorted sequence:")
    # print(A)
    print("Elapsed time:", end - start, "seconds.")
    AlgoDatValue.summary()
    AlgoDatValue.reset()

    print("\nQuickSort pivot middle:")
    A = read_int_sequence(file)
    start = pfc()
    quickSort2(A, 0, len(A) - 1)
    end = pfc()
    print("Sorted sequence:")
    # print(A)
    print("Elapsed time:", end - start, "seconds.")
    AlgoDatValue.summary()
    AlgoDatValue.reset()

    # Beide ungefähr gleich schnell
    # pivot middle benötigt mehr compare operations


