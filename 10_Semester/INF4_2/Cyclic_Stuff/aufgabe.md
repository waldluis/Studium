## Aufgabe 15.04.2024

Consider an array A[0...N-1] of length N.
Two such arrays are called equivalent if one is equal to the other, when cyclically shifted.

Example:
[1, 0, 0, 0, 1] and
[0, 1, 1, 0, 0] and 
[0, 0, 0, 1, 1] are equivalent.

[1, 1, 1, 0, 1] and
[1, 0, 0, 0, 1] are certainly not equivalent.

Of all cyclic rotations of an array, we call the lexicographic minimum the representative.

For example:
[0, 0, 1]
is the representative of
[0, 0, 1] and
[0, 1, 0] and
[1, 0, 0].

Allow array values 0,...,k.

Generate all representatives of all possible such ("k-ary) arrays for a given N.