#include "Variante.h"

Variante::Variante(
        Nat tamanoTab,
        Nat cantFichas,
        const map<Letra, Nat> &puntajes,
        const set<vector<Letra>> &palabrasLegitimas
) : _tablero(tamanoTab),
    _fichas(cantFichas),
    _puntaje(new Nat[TAMANIO_ALFABETO]),
        /*_palabra(Trie constructor),*/
    _palabraMasLarga(0) {
    for (int i = 0; i < TAMANIO_ALFABETO; i++) {
        if (puntajes.count(inversaDeOrd(i)) > 0)
            _puntaje[i] = puntajes.at(inversaDeOrd(i));
        else
            _puntaje[i] = 1;
    }
    /*for (vector<Letra> pal : palabrasLegitimas){
        _palabra.insert(pal);
        if (pal.size() > _palabraMasLarga)
            _palabraMasLarga = pal.size();
    }*/
}

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
    //return _palabra.count(palabra) == 1;
    return true;
}