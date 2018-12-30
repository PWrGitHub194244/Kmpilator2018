# Kompilator
Kompilator prostego języka napisany na laboratoria z kursu Języki Formalne i Techniki Translacji

Autor: **Piotr Bączkiewicz**

Nr indeksu: **194244**

### Pliki
- `Makefile` — plik służący do kompilacji projektu,
- `opt_compiler.y` — plik `BISON`a, zawierający jednocześnie wszystkie główne funckje w programie,
- `opt_compiler.l`— plik `FLEX`a.

### Użyte narzędzia
Projekt został przetestowany przy pomocy narzędzi w następujących wersjach:
- `gcc 6.3.0`
- `g++ 6.3.0`
- `flex 2.6.1`
- `bison (GNU Bison) 3.0.4`

### Sposób użycia

#### Kompilacja programu
W celu skompilowania projektu należy użyć polecenia 'make'.
Program wynikowy będzie znajdował się pod nazwą 'compiler'.

#### Uruchamianie programu
Kompilator uruchamia się komendą `./compiler`. Kod wejściowy przyjmowany jest na standardowe wejście, natomiast wynik działania programu wypisywany na standardowe wyjście lub do podanego jako argument pliku wyjściowego.

Aby odczytać kod z pliku wejśiowego `test` i zapisać wynik do pliku `out` można wywołać komendę:

```./compiler out < test```
