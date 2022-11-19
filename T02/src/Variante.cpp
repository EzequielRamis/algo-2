#include "Variante.h"

Variante::Variante(
        Nat tamanoTab,
        Nat cantFichas,
        const map<Letra, Nat> &puntajes,
        const set<vector<Letra>> &palabrasLegitimas
) : _tamanoTab(tamanoTab), _cantFichas(cantFichas), _puntajes(puntajes), _palabrasLegitimas(palabrasLegitimas){}

Nat Variante::tamanoTablero() const {
    return _tamanoTab;
}

Nat Variante::fichas() const {
    return _cantFichas;
}

Nat Variante::puntajeLetra(Letra l) const {
    return _puntajes.at(l);
}

bool Variante::palabraLegitima(const Palabra &palabra) const {
    for (vector<Letra> palabraLegitima : _palabrasLegitimas) {
        if (palabra == palabraLegitima) {
            return true;
        }
    }
    return false;
}

Nat Variante::longPalabraMasLarga() {
    Nat palabraMasLarga = 0;
    for (vector<Letra> palabra : _palabrasLegitimas) {
        if (palabra.size() > palabraMasLarga) {
            palabraMasLarga = palabra.size();
        }
    }
    return palabraMasLarga;
}

map<Letra, Nat> Variante::puntajes() const {
    return _puntajes;
}

set<vector<Letra>> Variante::palabrasLegitimas() const {
    return _palabrasLegitimas;
}
