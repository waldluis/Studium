#include <stdio.h>
#incude <stdlib.h>													//Pr�prozessorfehler, include falsch geschrieben

void test(int zahl)
{
	printf("Zahl: %d", zahl);
}

int main()
{
	int a = 6;

	printf("a= %d\n", a)											//Compilerfehler, Strichpunkt fehlt

	/*int b = 1;													//Laufzeitfehler b wird 0, Division durch 0
	b--;
	int c = a / b;
	printf("c = a/b = %d/%d = %d\n", a, b, c);*/

	tesT(a);														//Linkerfehler, Funktionsaufruf nicht m�glich, da falsch geschrieben
}

