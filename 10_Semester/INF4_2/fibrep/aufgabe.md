## Aufgabe 13.05.2024

Die Liste aller 7-Bit Worte, in denen keine zwei aufeinanderfolgenden Bits gesetzt sind, lexicographisch sortiert, ist:

```
0:  0000000     0
1:  0000001     1
2:  0000010     2
4:  0000100     3
5:  0000101     4
8:  0001000     5
9:  0001001     6
10: 0001010     7
16: 0010000     8
17: 0010001     9
18: 0010010     10
20: 0010100     11
21: 0010101     12
32: 0100000     13
33: 0100001     14
34: 0100010     15
36: 0100100     16
37: 0100101     17
40: 0101000     18
41: 0101001     19
42: 0101010     20
64: 1000000     21
65: 1000001     22
66: 1000010     23
68: 1000100     24
69: 1000101     25
72: 1001000     26
73: 1001001     27
74: 1001010     28
80: 1010000     29
81: 1010001     30
82: 1010010     31
84: 1010100     32
85: 1010101     33

```

Ein solches Wort sei in einem unsigned (long) integer gespeichert. Schreiben Sie eine Routine, die aus einem gegebenen Wort den Nachfolger errechnet.

Mit der Komplexität O(n) ist dies recht einfach
Es geht sogar mit O(1)!