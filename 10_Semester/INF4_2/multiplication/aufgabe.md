# Multiplication 

## Vorüberlegung

5 = 101 = x^2+1, 14 = 1110 = x^3+x^2+x

Multiplikation: 5*14 = 54 = 110110 = x^5+x^4+x^2+x = 54

$ GF(2^n) = F_{2^n} $

GF(p) erhalten wir mit "Rechnen modulo p" (p Primzahl)
$GF(p^n)$ erhalten wir mit Rechnen mit Polynomen über GF(p) modulo einem Polynom vom Grad n, die irreduzibel sind.
Ein Polynom nennt man irreduzibel, wenn es "nicht" faktorisiert (als P=Q*R mit deq(Q) != {0,n} und deq(R) != {0,n}).

$m = x^5+x^2+1 "=0", x^5 = -x^2-1 = x^2+1 $ &rarr; nur in GF(2^n) ist Subtraktion == Addition
über GF(2): (a+b)^2 = a^2+b^2

Literatur:
Lidl & Niederreiter: Introduction to Finite Fields and their Applications
Arndt: Matters Computational