#include "Variante.h"

Variante::Variante(
        Nat tamanoTab,
        Nat cantFichas,
        const map<Letra, Nat> &puntajes,
        const set<vector<Letra>> &palabrasLegitimas
) : _tamanoTab(tamanoTab),
    _cantFichas(cantFichas),
    _puntajes(puntajes),
    _palabras(),
    _longPalabraMasLarga(0) {
    for (Palabra p: palabrasLegitimas) {
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
    if (_puntajes.count(l) > 0)
        return _puntajes.at(l);
    return 1;
}

bool Variante::palabraLegitima(const Palabra &palabra) const {
    return _palabras.definida(palabra);
}

Nat Variante::longPalabraMasLarga() {
    return _longPalabraMasLarga;
}

map<Letra, Nat> Variante::puntajes() const {
    return _puntajes;
}