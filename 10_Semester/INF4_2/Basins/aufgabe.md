## Aufgabe 29.04.2024 - Basins

Sei C die Menge der komplexen Zahlen.

Sei f(z) eine Funktion von C --> C, und N(z) = z - f(z)/f'(z) die (Newton-) Iteration zum Finden der Nullstelle von f.

Sei t = 5.
Für alle z mit -t <= Re(z) <= +t und -t <= Im(z) <= +t,
finde die Nullstelle, zu der ein (Pixel) z konvergiert.

Setze ein bailout m = 100 und berechne 
$ N^{[k]} (z) für k = 1...m $, wobei
N(z), N(N(z)) = $N^{[2]}(z)$, $N^{[3]}(z)$, bis $N^{[m]}(z)$.
Setze eps = 1e-3.
Setze die Wurzeln r1, r2, r3 von f wie folgt:
f(z) = (z-r1)*(z-r2)*(z-r3).
Wenn (für ein k) $abs(N^{[k]}(z) -r) < eps$, dann färbe den Pixel zu z mit der Farbe der Wurzel (r1 rot, r2 grün, r3 blau) und springe zum nächsten z.

Wenn für alle k <= m $abs(N^{[k]}(z) -r) > eps$, dann mach den Pixel weiß (alle weiß Färben und lassen).

Bsp: r1 = -1, r2 = +1, r3 = 1 + 2i

Skalieren vom Pixel- ins komplexe-Rechteck
```c
int main()
{
    std::cout << "P1\n";
    constexpr unsigned n_row = 400; // -> y
    constexpr unsigned n_col = 400; // -> x
    constexpr double t = 5.0;
    constexpr double eps = 1e-3;
    constexpr double x_min = -t;
    constexpr double x_max = +t;
    constexpr double y_min = -t;
    constexpr double y_max = +t;
    constexpr double Rx = (x_max - x_min) / n_col;
    constexpr double Ry = (y_max - y_min) / n_row;

    for (unsigned i = 0; i < n_row; ++i)
    {
        // x = xmin +( i - imin) * (xmax - xmin) / (imax - imin)
        const double y = y_max - i * Ry;
        for (unsigned j = 0; j < n_col; ++j)
        {
            double x = x_min + j * Rx;
            do_stuff(z);
            // ...
        }
    }
}
```

f(z) = (z-r1)*(z-r2)*(z-r3)
f'(z) = (z-r1)(z-r2)+(z-r2)(z-r3)+(z-r1)(z-r3)
f''(z) = 2*((z-r1)+(z-r2)+(z-r3))
f'''(z) = 6
