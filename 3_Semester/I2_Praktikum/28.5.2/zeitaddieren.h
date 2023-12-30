#ifndef KOMMALIB_H_INCLUDED
#define KOMMALIB_H_INCLUDED

typedef struct zeit
{
    int tag;
    int stunde;
    int minute;
    int sekunde;
} Zeit;

unsigned long zeit_in_sek(Zeit z);
Zeit sek_in_zeit(unsigned long zeit_in_sek);
Zeit zeitEinlesen(int n);
int eingabeRichtig(Zeit z);

#endif // KOMMALIB_H_INCLUDED

