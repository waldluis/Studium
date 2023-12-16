#include <stdio.h>
#include <stdlib.h>
#define PI 3.14159

int main()
{

    double r;   //Radius
    double u;   //Umfang
    double v;   //Volumen
    double o;   //Oberflaeche

    printf("Radius der Kugel eingeben:");
    scanf("%lf", &r);
    u= (2 * r * PI) ;
    v= (1.3333 * (r*r*r) * PI);
    o= (4 * PI * (r*r));
    printf("Radius der Kugel: %lf \n", r);
    printf("Umfang= %lf \n", u);
    printf("Volumen= %lf \n", v);
    printf("Oberflaeche= %lf \n", o);

    return 0;
}
