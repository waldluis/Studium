#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned short x=0x12ab;
    printf("Urspruengliche Zahl: %x \n", x);
    x= (x >> 8) | (x << 8);
    printf("Zahl mit vertauschten Bytes: %x", x);
    return 0;
}
