#include "Fachada_Variante.h"

Fachada_Variante::Fachada_Variante(
        Nat tamanoTab,
        Nat cantFichas,
        const map<Letra, Nat> &puntajes,
        const set<vector<Letra>> &palabrasLegitimas
) : _variante(new Variante(tamanoTab, cantFichas, puntajes, palabrasLegitimas)) {}

Nat Fachada_Variante::tamanoTablero() const {
    return (*_variante).tamanoTablero();
}

Nat Fachada_Variante::fichas() const {
    return (*_variante).fichas();
}

Nat Fachada_Variante::puntajeLetra(Letra l) const {
    return (*_variante).puntajeLetra(l);
}

bool Fachada_Variante::palabraLegitima(const Palabra &palabra) const {
    return (*_variante).palabraLegitima(palabra);
}