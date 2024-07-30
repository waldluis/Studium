typedef unsigned long ulong;

#include <assert.h>

ulong mul(ulong a, ulong b)
{
    if (a == 0 || b == 0)
    {
        return 0;
    }

    ulong r = 0;

    while (b != 0)
    {
        if (b & 1)
        {
            r += a;
        }
        b >>= 1;
        a <<= 1;
    }
    return r;
}

ulong mulMod(ulong a, ulong b, ulong m)
{
    assert(a < m);
    assert(b < m);

    ulong r = 0;

    while (b != 0)
    {
        if (b & 1)
        {
            r += a;
            if (r >= m)
                r -= m;
        }
        a <<= 1;
        if (a >= m)
        {
            a -= m;
        }
        b >>= 1;
    }
    return r;
}

#if 0
// compute a^e mod m
ulong exp_mod(ulong b, ulong e, ulong m)
{
    // to do
}
#endif

// compute a * b as polynomial over GF(2) with shift-add technique
ulong mul_gf2(ulong a, ulong b)
{
    if (a == 0 || b == 0)
    {
        return 0;
    }

    ulong r = 0;

    while (b != 0)
    {
        if (b & 1)
        {
            r ^= a;
        }
        b >>= 1;
        a <<= 1;
    }
    return r;
}

// compute a * b mod m as polynomial over GF(2) with shift-add technique
ulong mul_gf2_Mod(ulong a, ulong b, ulong m, ulong h)
{
    assert(a < h);
    assert(b < h);
    ulong r = 0;

    while (b != 0)
    {
        if (b & 1)
        {
            r ^= a;
            if ((r & h) != 0)
                r ^= m;
        }
        a <<= 1;
        if (0 != (r & h))
        {
            a ^= m;
        }
        b >>= 1;
    }
    return r;
}

// return the smallest primitive root mod m
// return 0 if n mpt prime
ulong primitive_root(ulong m)
{
    const ulong g = m - 1; // group order
    for (ulong r = 1; r < m; ++r)
    {
        ulong p = r, e = 1; // p == r^e (mod m)
        for (e = 1; e < g; ++e)
        {
            if (p == 1) // r is not a primitive root
            {
                // break;
                goto next;
            }
            p = mulMod(p, r, m);
        }
        if (p != 1)
        {
            return 0;          
        }
        return r;
        next: ;
    }
    return 0; // no primitive root mod m exists
}

#include <iostream>
int main()
{
    const ulong a = 16;
    const ulong b = 17;

    ulong c = mul(16, 17);
    std::cout << c << " =?= " << a * b << std::endl;

    const ulong m = 20;
    c = mulMod(16, 17, m);
    std::cout << c << " =?= " << (a * b) % m << std::endl;

    const ulong pa = 14, pb = 5;
    c = mul_gf2(pa, pb);
    std::cout << c << " =?= " << "54" << std::endl;

    const ulong pm = 37;      // == 100101 = x^5 + x^2 + 1
    const ulong h = 1UL << 5; // == highest_one(pm)
    c = mul_gf2_Mod(pa, pb, pm, h);
    std::cout << c << " =?= " << "19" << std::endl;

    for (ulong p = 2; p < 50; ++p)
    {
        ulong r = primitive_root(p);
        std::cout << "primitive root of " << p << " is " << r << std::endl;
    }
    return 0;
}