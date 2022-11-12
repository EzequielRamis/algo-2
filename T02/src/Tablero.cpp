#include "Tablero.h"

Tablero::Tablero(int n): tablero(n) {}

void Tablero::ubicar(const Ocurrencia& o) {
}

bool Tablero::jugadaValida(const Ocurrencia& o) {
    return true;
}

bool Tablero::hayLetra(Nat x, Nat y) {
    return true;
}

Letra Tablero::letra(Nat i, Nat j) {
    assert(hayLetra(i,j));
    return 'a';
}