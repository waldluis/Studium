class AlgoDatValue:
    """A class representing a value with statistics."""

    memory = 0
    read = 0
    write = 0
    compare = 0
    add_operation = 0
    sub_operation = 0
    mul_operation = 0
    div_operation = 0
    bit_operation = 0

    @staticmethod
    def summary():
        print(f"Memory: {AlgoDatValue.memory}")
        print(f"Read: {AlgoDatValue.read}")
        print(f"Write: {AlgoDatValue.write}")
        print(f"Compare: {AlgoDatValue.compare}")
        print(f"Add: {AlgoDatValue.add_operation}")
        print(f"Sub: {AlgoDatValue.sub_operation}")
        print(f"Mul: {AlgoDatValue.mul_operation}")
        print(f"Div: {AlgoDatValue.div_operation}")
        print(f"Bit: {AlgoDatValue.bit_operation}")

    @staticmethod
    def reset():
        AlgoDatValue.memory = 0
        AlgoDatValue.read = 0
        AlgoDatValue.write = 0
        AlgoDatValue.compare = 0
        AlgoDatValue.add_operation = 0
        AlgoDatValue.sub_operation = 0
        AlgoDatValue.mul_operation = 0
        AlgoDatValue.div_operation = 0
        AlgoDatValue.bit_operation = 0

    def __init__(self, value):
        AlgoDatValue.memory += 1
        AlgoDatValue.write += 1
        self.value = value

    def __str__(self):
        AlgoDatValue.read += 1
        return f"{self.value}"

    def __repr__(self):
        AlgoDatValue.read += 1
        return f"{self.value}"

    def __eq__(self, other):
        AlgoDatValue.compare += 1
        AlgoDatValue.read += 2
        if not isinstance(other, AlgoDatValue):
            return self.value == other
        return self.value == other.value

    def __lt__(self, other):
        AlgoDatValue.compare += 1
        AlgoDatValue.read += 2
        if not isinstance(other, AlgoDatValue):
            return self.value < other
        return self.value < other.value

    def __le__(self, other):
        AlgoDatValue.compare += 1
        AlgoDatValue.read += 2
        if not isinstance(other, AlgoDatValue):
            return self.value <= other
        return self.value <= other.value

    def __gt__(self, other):
        AlgoDatValue.compare += 1
        AlgoDatValue.read += 2
        if not isinstance(other, AlgoDatValue):
            return self.value > other
        return self.value > other.value

    def __ge__(self, other):
        AlgoDatValue.compare += 1
        AlgoDatValue.read += 2
        if not isinstance(other, AlgoDatValue):
            return self.value >= other
        return self.value >= other.value

    def __add__(self, other):
        AlgoDatValue.add_operation += 1
        AlgoDatValue.read += 2
        return self.value + other.value

    def __sub__(self, other):
        AlgoDatValue.sub_operation += 1
        AlgoDatValue.read += 2
        return self.value - other.value

    def __mul__(self, other):
        AlgoDatValue.mul_operation += 1
        AlgoDatValue.read += 2
        return self.value * other.value

    def __truediv__(self, other):
        AlgoDatValue.div_operation += 1
        AlgoDatValue.read += 2
        return self.value / other.value

    def __floordiv__(self, other):
        AlgoDatValue.div_operation += 1
        AlgoDatValue.read += 2
        return self.value // other.value

    def __mod__(self, other):
        AlgoDatValue.div_operation += 1
        AlgoDatValue.read += 2
        return self.value % other.value

    def __iadd__(self, other):
        AlgoDatValue.add_operation += 1
        AlgoDatValue.read += 1
        AlgoDatValue.write += 1
        self.value += other.value
        return self

    def __isub__(self, other):
        AlgoDatValue.sub_operation += 1
        AlgoDatValue.read += 1
        AlgoDatValue.write += 1
        self.value -= other.value
        return self

    def __imul__(self, other):
        AlgoDatValue.mul_operation += 1
        AlgoDatValue.read += 1
        AlgoDatValue.write += 1
        self.value *= other.value
        return self

    def __itruediv__(self, other):
        AlgoDatValue.div_operation += 1
        AlgoDatValue.read += 1
        AlgoDatValue.write += 1
        self.value /= other.value
        return self

    def __ifloordiv__(self, other):
        AlgoDatValue.div_operation += 1
        AlgoDatValue.read += 1
        AlgoDatValue.write += 1
        self.value //= other.value
        return self

    def __imod__(self, other):
        AlgoDatValue.div_operation += 1
        AlgoDatValue.read += 1
        AlgoDatValue.write += 1
        self.value %= other.value
        return self

    def __neg__(self):
        return -self.value

    def __pos__(self):
        return +self.value

    def __abs__(self):
        return abs(self.value)

    def __invert__(self):
        return ~self.value

    def __lshift__(self, other):
        AlgoDatValue.bit_operation += 1
        AlgoDatValue.read += 2
        return self.value << other.value

    def __rshift__(self, other):
        AlgoDatValue.bit_operation += 1
        AlgoDatValue.read += 2
        return self.value >> other.value

    def __and__(self, other):
        AlgoDatValue.bit_operation += 1
        AlgoDatValue.read += 2
        return self.value & other.value

    def __xor__(self, other):
        AlgoDatValue.bit_operation += 1
        AlgoDatValue.read += 2
        return self.value ^ other.value

    def __or__(self, other):
        AlgoDatValue.bit_operation += 1
        AlgoDatValue.read += 2
        return self.value | other.value

    def __ilshift__(self, other):
        AlgoDatValue.bit_operation += 1
        AlgoDatValue.read += 2
        AlgoDatValue.write += 1
        self.value <<= other.value
        return self

    def __irshift__(self, other):
        AlgoDatValue.bit_operation += 1
        AlgoDatValue.read += 2
        AlgoDatValue.write += 1
        self.value >>= other.value
        return self

    def __iand__(self, other):
        AlgoDatValue.bit_operation += 1
        AlgoDatValue.read += 2
        AlgoDatValue.write += 1
        self.value &= other.value
        return self

    def __ixor__(self, other):
        AlgoDatValue.bit_operation += 1
        AlgoDatValue.read += 2
        AlgoDatValue.write += 1
        self.value ^= other.value
        return self

    def __ior__(self, other):
        AlgoDatValue.bit_operation += 1
        AlgoDatValue.read += 2
        AlgoDatValue.write += 1
        self.value |= other.value
        return self

    def __int__(self):
        return int(self.value)

    def __float__(self):
        return float(self.value)

    def __complex__(self):
        return complex(self.value)

    def __round__(self, n=0):
        return round(self.value, n)

    def __setattr__(self, name, value):
        if name == "value":
            AlgoDatValue.write += 1
        self.__dict__[name] = value


class AlgoDatArray:
    """A class representing an array of AlgoDatValue objects."""

    def __init__(self, size):
        self.size = size
        self.array = [AlgoDatValue(None)] * size

    def set(self, index, value):
        assert isinstance(value, AlgoDatValue)
        assert isinstance(index, int)
        self.array[index] = value

    def get(self, index):
        assert isinstance(index, int)
        return self.array[index]

    def __str__(self):
        return str(self.array)

    def __len__(self):
        return len(self.array)

    def __iter__(self):
        return iter(self.array)

    def __getitem__(self, index):
        assert isinstance(index, int)
        return self.array[index]

    def __setitem__(self, index, value):
        assert isinstance(index, int)
        assert isinstance(value, AlgoDatValue)
        self.array[index] = value


class MinusInf:
    """A class representing negative infinity."""

    def __gt__(self, other):
        return False

    def __ge__(self):
        return False

    def __lt__(self, other):
        return True

    def __le__(self, other):
        return True

    def __eq__(self, other):
        return False


class Inf:
    """A class representing positive infinity."""

    def __gt__(self, other):
        return True

    def __ge__(self):
        return True

    def __lt__(self, other):
        return False

    def __le__(self, other):
        return False

    def __eq__(self, other):
        return False


def read_int_sequence(filename: str) -> AlgoDatArray:
    """Reads a sequence of integers from a file and returns an AlgoDatArray object."""
    with open(filename, "r") as file:
        l = list(map(int, file.read().split()))
    a = AlgoDatArray(len(l))
    for i in range(len(l)):
        a.set(i, AlgoDatValue(l[i]))
    return a
