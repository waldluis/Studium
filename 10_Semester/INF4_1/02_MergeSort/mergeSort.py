from foundation import *
from time import perf_counter as pfc

def mergeSort(A :AlgoDatArray):

    if len(A) == 1:
        return

    middle = len(A) // 2

    left = AlgoDatArray(middle)
    right = AlgoDatArray(len(A) - middle)

    for i in range(middle):
        left[i] = A[i]
    
    for i in range(middle, len(A)):
        right[i - middle] = A[i]

    mergeSort(left)
    mergeSort(right)

    merge(left, right)


def merge(left, right):
    i, j = 0, 0
    leftLen = len(left)
    rightLen = len(right)
    B = AlgoDatArray(leftLen + rightLen)

    while i < leftLen and j < rightLen:
        if left[i] < right[j]:
            B[i+j] = left[i]
            i += 1
        else:
            B[i+j] = right[j]
            j += 1
    
    while i < leftLen:
        B[i+j] = left[i]
        i += 1

    while j < rightLen:
        B[i+j] = right[j]
        j += 1

    for i in range(len(B)):
        A[i] = B[i]


if __name__ == "__main__":
    
    file = "seq3.txt"

    print("Merge Sort GPT")
    A = read_int_sequence(file)
    start = pfc()
    mergeSort(A)
    end = pfc()
    print("Sorted sequence:")
    print(A)
    print("Elapsed time:", end - start, "seconds.")
    AlgoDatValue.summary()
