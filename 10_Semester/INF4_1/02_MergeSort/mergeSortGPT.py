from foundation import *
from time import perf_counter as pfc

def mergeSortGPT(A):
    """Sorts the array A using the merge sort algorithm.

    Args:
        A (list): The array to be sorted.

    Returns:
        None: The function modifies the input array in-place.

    """
    # Check if the array has only one element
    if len(A) == 1:
        return

    # Initialize the auxiliary array
    B = AlgoDatArray(len(A))

    # Copy the elements of A to B
    # for i in range(len(A)):
    #     B[i] = A[i]
    
    # Call the recursive merge sort function
    mergeSortGPTRec(A, B, 0, len(A) - 1)

    # Copy the elements of B back to A
    # for i in range(len(A)):
    #     A[i] = B[i]



def mergeSortGPTRec(A, B, left, right):
    """
    Recursively sorts the array A using the merge sort algorithm.

    Parameters:
    A (list): The array to be sorted.
    B (list): An auxiliary array used for merging.
    left (int): The left index of the subarray to be sorted.
    right (int): The right index of the subarray to be sorted.
    """

    if left < right:
        # Determine the middle index
        middle = (left + right) // 2
        # Recursively sort the two halves
        mergeSortGPTRec(A, B, left, middle)
        mergeSortGPTRec(A, B, middle + 1, right)
        # Merge the two sorted halves
        mergeGPT(A, B, left, middle, right)


def mergeGPT(A, B, left, middle, right):
    """Merges the two sorted halves of array A.

    Args:
        A (list): The input array to be merged.
        B (list): An auxiliary array used for merging.
        left (int): The starting index of the left half.
        middle (int): The ending index of the left half.
        right (int): The ending index of the right half.

    Returns:
        None. The merged elements are copied back to A.

    """
    # Initialize the indices
    i = left
    j = middle + 1
    k = left
    # Merge the two halves
    while i <= middle and j <= right:
        if A[i] <= A[j]:
            B[k] = A[i]
            i += 1
        else:
            B[k] = A[j]
            j += 1
        k += 1
    # Copy the remaining elements of the left half
    while i <= middle:
        B[k] = A[i]
        i += 1
        k += 1
    # Copy the remaining elements of the right half
    while j <= right:
        B[k] = A[j]
        j += 1
        k += 1
    # Copy the merged elements back to A
    for i in range(left, right + 1):
        A[i] = B[i]


def testMergeSortGPT():
    """Tests the mergeSortGPT function."""
    # Initialize the array
    A = AlgoDatArray(10)
    A.set(0, AlgoDatValue(3))
    A.set(1, AlgoDatValue(1))
    A.set(2, AlgoDatValue(4))
    A.set(3, AlgoDatValue(1))
    A.set(4, AlgoDatValue(5))
    A.set(5, AlgoDatValue(9))
    A.set(6, AlgoDatValue(2))
    A.set(7, AlgoDatValue(6))
    A.set(8, AlgoDatValue(5))
    A.set(9, AlgoDatValue(3))
    # Sort the array
    mergeSortGPT(A)
    # Print the sorted array
    print(A)

if __name__ == "__main__":
    # testMergeSortGPT()
    
    file = "seq3.txt"

    print("Merge Sort GPT")
    A = read_int_sequence(file)
    start = pfc()
    mergeSortGPT(A)
    end = pfc()
    print("Sorted sequence:")
    print(A)
    print("Elapsed time:", end - start, "seconds.")
    AlgoDatValue.summary()

    