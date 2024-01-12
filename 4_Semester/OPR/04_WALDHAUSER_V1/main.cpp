#include <iostream>
#include <cassert>
#include "Zahl.h"
#include "Vektor.h"
using namespace std;

void test01() {
    cout << "test01:\n-------\n";
    const Zahl z1{ 2 };
    cout << "z1=" << z1.wert() << endl;
    cout << "z1=" << z1.text() << endl;
    const Zahl z2 = 3;
    cout << "z2=" << z2.text() << endl;
    assert(z2.wert() == 3);
    const Zahl z3 = z1.add(z2);
    cout << "z3=" << z3.text() << endl;
    assert(z3.wert() == 5);
    const Zahl z4 = z2.sub(z3);
    cout << "z4=" << z4.text() << endl;
    assert(z4.wert() == -2);
    const Zahl z5 = z2.mul(z4);
    cout << "z5=" << z5.text() << endl;
    assert(z5.wert() == -6);
    const Zahl z6 = z5.div(z4);
    cout << "z6=" << z6.text() << endl;
    assert(z6.wert() == 3);
    const Zahl z7 = z6.mul(2);
    cout << "z7=" << z7.text() << endl << endl;
    assert(z7.wert() == 6);
    cout << "OK\n\n";
}

void test02() {
    cout << "test02:\n-------\n";
    Zahl z1 = 2;
    Zahl z2 = 3;
    z1.add(z2);
    assert(z1.wert() == 5);
    z1.mul(4);
    assert(z1.wert() == 20);
    z1.sub(z2);
    assert(z1.wert() == 17);
    z1.add(Zahl::Eins).div(2);
    assert(z1.wert() == 9);
    cout << "OK\n\n";
}

void test03() {
    cout << "test03:\n-------\n";
    assert(Zahl::anzahlObjekte() == 2);
    Zahl* z1 = new Zahl(2);
    assert(Zahl::anzahlObjekte() == 3);
    {
        Zahl z2(0);
        assert(Zahl::anzahlObjekte() == 4);
    }
    assert(Zahl::anzahlObjekte() == 3);
    delete z1;
    assert(Zahl::anzahlObjekte() == 2);
    cout << "OK\n\n";
}

void test04() {
    cout << "test04:\n-------\n";
    Zahl z = 2;
    z = z.add(Zahl::Eins);
    assert(z.wert() == 3);
    z = z.mul(Zahl::Null);
    assert(z.wert() == 0);
    cout << "OK\n\n";
}

void test05() {
    cout << "test05:\n-------\n";
    Zahl z1 = 1, z2 = 2, z3 = 3;
    Vektor v1{ z1,z2,z3 };
    cout << "v1 = " << v1.text() << ", Summe über Elemente = " << v1.summe() << endl;
    assert(v1.summe() == 6);
    Vektor v2{ 4,5,6 };
    cout << "v2 = " << v2.text() << endl;
    assert(v2.summe() == 15);
    Vektor v3 = v1;
    cout << "v3 = " << v3.text() << endl;
    v3.anhaengen(v2);                           
    cout << "v3 = " << v3.text() << endl;
    assert(v3.summe() == 21);
    v1.add(v2);
    cout << "v1 = " << v1.text() << endl;
    assert(v1.summe() == 21);
    v1.mul(2);
    cout << "v1 = " << v1.text() << endl;
    assert(v1.summe() == 42);
    v1.sub(v2);
    cout << "v1 = " << v1.text() << endl;
    assert(v1.summe() == 27);
    v1.div(3);
    cout << "v1 = " << v1.text() << endl;
    assert(v1.summe() == 9);
    cout << "OK\n\n";
}

void test06() {
    cout << "test06:\n-------\n";
    Vektor v1 = { 1,2 };
    Vektor v2 = { 3,4,5 };
    assert(v1.laenge() != v2.laenge());
    v1.add(v2);
    cout << "\nOK\n\n";
}

void test07() {
    cout << "test07:\n-------\n";
    Vektor v1 = { 3,1,4 };
    Vektor v2 = { -1,1,-1 };
    Vektor v3 = { -4,0,-2 };
    assert(7 == v1.mul(2).add(v2).sub(v3).div(3).summe());
    cout << "v1 = " << v1.text() << endl;
    cout << "OK\n\n";
}

void test08() {
    cout << "test08:\n-------\n";
    Vektor v = { 3,-1,4 };
    Zahl z{ v };
    assert(z.wert() == v.summe());
    cout << "OK\n\n";
}

int main() {
    test01();
    test02();
    test03();
    test04();
    test05();
    test06();
    test07();
    test08();
}