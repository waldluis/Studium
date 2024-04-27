from foundation import *
from time import perf_counter as pfc

def abschnittssumme_cubic(z: AlgoDatArray) -> (int, int, int):
    maxSum = AlgoDatValue(MinusInf())
    currentSum = AlgoDatValue(0)
    left = AlgoDatValue(0)
    right = AlgoDatValue(0)
    size = AlgoDatValue(z.size)

    for i in range(size.value):
        for j in range(i, size.value):
            currentSum.value = 0
            for k in range(i, j+1):
                currentSum += z.get(k)
            if currentSum > maxSum:
                maxSum.value = currentSum.value
                left.value = i
                right.value = j
    return maxSum.value, left.value, right.value


def abschnittssumme_square(z: AlgoDatArray) -> (int, int, int):
    maxSum = AlgoDatValue(MinusInf())
    currentSum = AlgoDatValue(0)
    left = AlgoDatValue(0)
    right = AlgoDatValue(0)
    size = AlgoDatValue(z.size)

    for i in range(size.value):
        currentSum.value = 0
        for j in range(i, size.value):
            currentSum += z.get(j)
            if currentSum > maxSum:
                maxSum.value = currentSum.value
                left.value = i
                right.value = j

    return maxSum.value, left.value, right.value


def abschnittssumme_linear(z: AlgoDatArray) -> (int, int, int):
    maxSum = AlgoDatValue(MinusInf())
    currentSum = AlgoDatValue(0)
    left = AlgoDatValue(0)
    right = AlgoDatValue(0)
    size = AlgoDatValue(z.size)
    currentLeft = AlgoDatValue(0)

    for i in range(size.value):
        currentSum += z.get(i)
        if currentSum > maxSum:
            maxSum.value = currentSum.value
            left.value = currentLeft.value
            right.value = i
        if currentSum < 0:
            currentSum.value = 0
            currentLeft.value = i + 1
    
    return maxSum.value, left.value, right.value


def abschnittssumme_recursive(z: AlgoDatArray, left: int, right: int) -> (int, int, int):  
    maxSum = AlgoDatValue(MinusInf())
    currentSum = AlgoDatValue(0)
    currentLeft = AlgoDatValue(0)


    if left == right:
        return z.get(left).value, left, right
    
    mid = (left + right) // 2

    leftSum, leftL, leftR = abschnittssumme_recursive(z, left, mid)
    rightSum, rightL, rightR = abschnittssumme_recursive(z, mid+1, right)
    midSum, midL, midR = findMid(z, left, mid, right)

    if leftSum >= rightSum and leftSum >= midSum:
        return leftSum, leftL, leftR
    
    if rightSum >= leftSum and rightSum >= midSum:
        return rightSum, rightL, rightR
    
    return midSum, midL, midR
    

def findMid(z: AlgoDatArray, left: int, mid: int, right: int) -> (int, int, int):
    leftSum = AlgoDatValue(MinusInf())
    currentSum = AlgoDatValue(0)
    leftIndex = AlgoDatValue(0)
    rightIndex = AlgoDatValue(0)

    for i in range(mid, left):
        currentSum += z.get(i)
        if currentSum > leftSum:
            leftSum.value = currentSum.value
            leftIndex.value = i

    rightSum = AlgoDatValue(MinusInf())
    currentSum = AlgoDatValue(0)

    for i in range(mid+1, right):
        currentSum += z.get(i)
        if currentSum > rightSum:
            rightSum.value = currentSum.value
            rightIndex.value = i

    return leftSum + rightSum, leftIndex.value, rightIndex.value

if __name__ == "__main__":

    file = "seq1.txt"

    print("Abschnittssumme Kubisch")
    z = read_int_sequence(file)
    start = pfc()
    print(abschnittssumme_cubic(z))
    print(f"Dauer: {pfc()-start:.4f} sec")
    AlgoDatValue.summary()
    AlgoDatValue.reset()

    print("Abschnittssumme Quadratisch")
    z = read_int_sequence(file)
    start = pfc()
    print(abschnittssumme_square(z))
    print(f"Dauer: {pfc()-start:.4f} sec")
    AlgoDatValue.summary()
    AlgoDatValue.reset()
    
    print("Abschnittssumme Linear")
    z = read_int_sequence(file)
    start = pfc()
    print(abschnittssumme_linear(z))
    print(f"Dauer: {pfc()-start:.4f} sec")
    AlgoDatValue.summary()
    AlgoDatValue.reset()

    print("Abschnittssumme Rekursiv")
    z = read_int_sequence(file)
    start = pfc()
    left = 0
    right = z.size - 1
    print(abschnittssumme_recursive(z, left, right))
    print(f"Dauer: {pfc()-start:.4f} sec")
    AlgoDatValue.summary()
    AlgoDatValue.reset()
