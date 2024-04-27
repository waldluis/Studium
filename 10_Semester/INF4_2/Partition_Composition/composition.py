def print_compositions(n, prefix=""):
    if n == 0:
        print(prefix[:-1])  # Remove the trailing "+" sign
        return
    for i in range(1, n + 1):
        print_compositions(n - i, prefix + str(i) + "+")

# Example usage
number = 5
print(f"Compositions of {number}:")
print_compositions(number)