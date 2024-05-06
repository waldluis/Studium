# Parallelrechnen WS23/24 J. Arndt

## 06.10.23 Übersicht
---

Hardware:
- GPU
- Multicore-CPU
- Microcontroller
- Hyperthreading -> Kerne virtuell verdoppen **Böse-> Ausschalten**
- Cluster -> Rechenzentrum, mehrere PCs mit Memory Verbindung
- Spezialhardware -> Wafer mit Cores voll
- FPGA

Software:
- Multithreading -> OpenMP
- Multitasking -> Praktikum
  
<br>

## 27.10.23 Prozessor Cache
| Cache Level | Lantenzy [cycles] | Größe [Bytes] |
| --- | --- | --- |
|Core mit 16 Gerenal Purpose Register (im Normalfall ohne spez. wie Floating Point o. ä.) |  L = 0 | ? |
| Level 1 Cache am Prozessor (on Die) | L = 1 | 32k Data und 32k Instructions |
| Level 2 Cache | L ~ 5 | 512k |
| Level 3 Cache kann on Chip, muss aber nicht | L ~ 20 | xM |
| RAM | L ~ 100 (nicht genau messbar| mehrere G |)

<br>

## 17.11.23 Pipelining
---

```c 
constexpr unsigned long N = 1UL << 32;
double A[N];

double s = 0.0;
for(unsigned long j = 0, j < N; j++)
{
    s += A[j];
}

double s0 = 0.0, s1 = 0.0;
for (unsigned long j = 0; j < N; j+2)       // loop unrolling schneller
{
    s0 += A[j+0];
    s1 += A[j+1];
}
double s = s0 + s1;
```
<br>

**Pipeline** (skalare Architektur)
```mermaid
graph LR
    A[Read instr.]--> B[decode instr.]
    B --> C[Read Memory]
    C --> D[OP ALU/FPU]
    D --> E[Read/Write Memory]
```


<br>
<br>

conditional branch
```c
if(condFunc())
{
    // true instruction         
}
else
{
    // false instruction
}
```
Nicht klar welcher Branch ausgeführt wird, wenn falscher angenommen dann Branch Bubble -> langsam \
Lösung: Branch Prediction

| Operation | throughput [instr/cycle] | latency [cycles] |
| --- | --- | --- |
| add, sub, xor, and... | 4 | 1 |
| mul | 2 | 1-2 |
| div | 1/70 | 70 |
| exp, log, sin, cos | 1/120 | 120 |

-> latency nicht wirklich relevant, da nicht merkbar\
-> throughput wichtig

### Hidden logic
- Streng geheim von Herstellern gehalten
  - CPU bauen kann jeder -> schnelle nicht
- Zwei Pipelines
  - Beide Branches werden angelegt
  - Einer wird auf jeden Fall ausgeführt
  - keine Branch Bubbles, 
  - Probleme bei Zugriff auf Speicher
- Vier Pipelines
  - Infos dazu gibts nicht

<br>

**Register renaming:**\
Register (ABI): 16\
interne : 180

instr -> "großes Wunder" **out of order execution** -> ready\
Compiler wissen interne Dinge über CPU von Herstellern

<br>

**Code einfach halten Compiler macht den Rest**
```c	
const int n_r, n_c;
for(int r = 0; r < n; ++r)
{
    for(int c = 0; c < n; ++c)
    {
        A[r * n_c + c];
    }
}
```
<br>

## 24.11.2023 Complex parallelisieren
---

**LINUX**
- Bash Skript startet Farmer
- Farmer macht shared memory auf
- Farmer berechnet Zeilen und Parameter
- Bash Skript startet Worker
- Worker berechnet Zeilen
- Worker schreibt in shared memory
- Bash Skript schreibt shared memory in Datei


Übergabe an Worker: unsigned row_number unsigned n_x double re_min double re_max\

Aufruf in Bash zum umspeichern von Shared Memory in Datei
```bash
rm -rf set.pbm
echo 'P1' >> set.pbm
echo '1000 1000' >> set.pbm
parallel ...
cat /dev/shm/myshm >> set.pbm
rm /dev/shm/myshm
```

**Ergebnisse**
- alte Version: 
  - 1000x1000 mit 1000er Tiefe: ?
  - 10000x10000 mit 1000er Tiefe: ~1h 10m
- 1 Versuch mit memcpy für jede Zahl einzeln
  - 1000x1000 mit 1000er Tiefe: ~ 3,7s
  - 10000x10000 mit 1000er Tiefe: ~ 3m 5s
- 2 Versuch mit memcpy für jede Zeile
  - 1000x1000 mit 1000er Tiefe: ~ 3,5s
  - 10000x10000 mit 1000er Tiefe: ~ 3m 0s
<br>

## 15.12.2023 Strong und Weak Scaling
---

### Strong Scaling

$ Arbeit = 1 = s + p  $ ( serielle + parallele Rechenzeit)

Paralleles rechnen auf N cores (Anzahl der Worker):
Parallele Rechenzeit: $T_{p} = s + \frac{p}{N}$ -> $p = (T_{p} - s) * N$

---
**Aufgabe**:
  Für N = 10 Worker, wie groß darf der serielle Anteil s sein, damit die parallele Rechenzeit höchstens 1/2 beträgt?
  
---   
Lösung:

$$s + \frac{p}{N} \leq \frac{1}{2}$$

$$ p = 1 - s$$

$$ s + \frac{1-s}{10} \leq \frac{1}{2}$$

$$ 10s + 1 - s \leq 5$$

$$ 9s \leq 4$$

$$ s \leq \frac{4}{9}$$

---
**Aufgabe**:
Sei $s = \frac{1}{10}$, wieviele Worker (cores, N) braucht man mindestens, damit die parallele Rechenzeit $T_{p}$ höchstens $\frac{1}{5}$ ist?

---
Lösung: 
$$ T_{p} = s + \frac{p}{N} = \frac{1}{5}$$

$$ p = 1 - \frac{1}{10} = \frac{9}{10} $$

$$ T_{p} = \frac{1}{10} + \frac{\frac{9}{10}}{N} \leq \frac{1}{5}$$

$$ \frac{1}{10} + \frac{9}{10} * N \leq \frac{1}{5}$$

$$ \frac{9}{10} * N \leq \frac{1}{10}$$

$$ N \geq 9$$

---
### Weak scaling:
$$ Arbeit = s + p * N^\alpha$$ -> Arbeit steigt mit Workeranzahl ($\alpha$ = 0 -> strong scaling)

$$ parallele Rechenzeit: T_{p} = s + \frac{p*N^\alpha}{N} = s + p * N^{\alpha-1}$$

---
**Aufgabe**:
Für welche $\alpha$ steigt die parallele Rechenzeit mit der Anzahl der Worker/Cores N? (bzw. wann bleibt Rechenzeit konstant -> Grenzfall)

---
Lösung:
$$ T_{p} = s + p*N^{\alpha-1}$$

$$ N^{\alpha-1} = const = 1$$

$$ \alpha - 1 = 0$$

$$ \alpha = 1$$

<br>

## 12.01.2024 Rekursion in Iteration umwandeln
---

- Geht ist aber kompliziert
- Statemachine bauen
- Eigenen Stack bauen -> Array aus Stackframes
- In C Switch-Case relativ langsam deswegen verbotenes GoTo verwenden
- Also einfach rekursiv lassen

---
**Klausur**
- Strong Scaling
- Weak Scaling
- Nur das was wir gemacht haben