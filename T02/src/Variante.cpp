#include "Variante.h"

Variante::Variante(
        Nat tamanoTab,
        Nat cantFichas,
        const map<Letra, Nat> &puntajes,
        const set<vector<Letra>> &palabrasLegitimas
) : _tablero(tamanoTab),
    _fichas(cantFichas),
    _puntaje(),
    _palabras(new trie()),
    _palabraMasLarga(0) {
    for (int i = 0; i < TAMANIO_ALFABETO; i++) {
        if (puntajes.count(inversaDeOrd(i)) > 0){
            Nat* nuevo = new Nat(puntajes.at(inversaDeOrd(i)));
            _puntaje[i] = nuevo;
        } else {
            Nat *nuevo = new Nat(1);
            _puntaje[i] = nuevo;
        }
    }
    for (vector<Letra> pal : palabrasLegitimas){
        (*_palabras).insert(pal);
        if (pal.size() > _palabraMasLarga) {
            _palabraMasLarga = pal.size();
        }
    }
}

Nat Variante::tamanoTablero() const {
    return _tablero;
}

Nat Variante::fichas() const {
    return _fichas;
}

Nat Variante::puntajeLetra(Letra l) const {
    return *_puntaje[ord(l)];
}

bool Variante::palabraLegitima(const Palabra &palabra) const {
    return (*_palabras).count(palabra) == 1;
}