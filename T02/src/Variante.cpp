#include "Variante.h"
#include "Letra.h"

Variante::Variante(
        Nat tamanoTab,
        Nat cantFichas,
        const map<Letra, Nat> &puntajes,
        const set<vector<Letra>> &palabrasLegitimas
) : _puntaje(vector<Nat>()), _fichas(cantFichas), _tablero(tamanoTab) {}

Nat Variante::tamanoTablero() const {
    return _tablero;
}

Nat Variante::fichas() const {
    return _fichas;
}

Nat Variante::puntajeLetra(Letra l) const {
    return _puntaje[ord(l)];
}

bool Variante::palabraLegitima(const Palabra &palabra) const {
    //return palabras.count(palabra) == 1;
    return true;
}