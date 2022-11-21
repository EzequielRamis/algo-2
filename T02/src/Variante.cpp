#include "Variante.h"

Variante::Variante(
        Nat tamanoTab,
        Nat cantFichas,
        const map<Letra, Nat> &puntajes,
        const set<vector<Letra>> &palabrasLegitimas
) : _tamanoTab(tamanoTab),
    _cantFichas(cantFichas),
    _longPalabraMasLarga(0) {
    for (int i = 0; i < TAMANIO_ALFABETO; i++)
        if (puntajes.count(inversaDeOrd(i)) > 0)
            _puntajes[i] = puntajes.at(inversaDeOrd(i));
        else
            _puntajes[i] = 1;
    for (const Palabra &p: palabrasLegitimas) {
        _palabras.definir(p);
        if (p.size() > _longPalabraMasLarga)
            _longPalabraMasLarga = p.size();
    }
}

Nat Variante::tamanoTablero() const {
    return _tamanoTab;
}

Nat Variante::fichas() const {
    return _cantFichas;
}

Nat Variante::puntajeLetra(Letra l) const {
    return _puntajes[ord(l)];
}

bool Variante::palabraLegitima(const Palabra &palabra) const {
    return _palabras.definida(palabra);
}

Nat Variante::longPalabraMasLarga() const {
    return _longPalabraMasLarga;
}