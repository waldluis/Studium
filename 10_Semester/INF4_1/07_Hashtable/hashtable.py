from foundation import *
import math

def h(x:int, m:int) -> int:
    A = (math.sqrt(5) - 1) / 2
    return int((x * A - int(x * A)) * m)


def f(x:int, m:int, i:int) -> int:
    h_new = h(x, m)
    return (h_new + i + 14 * i*i) % m


class HashTable:
    def __init__(self, m):
        self.m = m
        self.table = self.m * [None]
        for i in range(m):
            self.table[i] = "None"

    def insert(self, x) -> bool:
        for i in range(self.m):
            j = f(x, self.m, i)
            if self.table[j] == "None":
                self.table[j] = AlgoDatValue(x)
                return True
        return False
    
    def search(self, x:AlgoDatValue) -> bool:
        for i in range(self.m):
            j = f(x.value, self.m, i)
            if self.table[j] == x:
                return True
            if self.table[j] == "None":
                return False
            if self.table[j] == "Deleted":
                continue

        return False
    
    def delete(self, x:AlgoDatValue) -> bool:
        for i in range(self.m):
            j = f(x.value, self.m, i)
            if self.table[j] == x:
                self.table[j] = "Deleted"
                return True
            if self.table[j] == "None":
                return False
        return False
    
    def __str__(self) -> str:
        s = ""
        for i in range(self.m):
            s += str(i) + ": " + str(self.table[i]) + "\n"
        return s
    
    def alpha(self) -> float:
        n = 0
        for i in range(self.m):
            if self.table[i] != "None" and self.table[i] != "Deleted":
                n += 1
        return n / self.m



if __name__ == '__main__':

    file = 'C:\\Studium\\10_Semester\\INF4_1\\Praktikum\\GIT\\AlgoDatSoSe24\\seq0.txt'

    m = 31

    ht = HashTable(m)

    A = read_int_sequence(file)

    for i in A:
        result = ht.insert(i.value)
        if result == False:
            print(f"Insert {i} failed")
            print("Table is full")
            break

    print(ht)

    print(f"alpha = {ht.alpha()}")

    delete = 58
    print(f"Delete {delete}")
    ht.delete(AlgoDatValue(delete))

    print(ht)
    print(f"alpha = {ht.alpha()}")
