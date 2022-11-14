#include "Juego.h"
#include "Letra.h"

Juego::Juego(Nat k, const Variante &v, const Repositorio &r) :
        _tablero(
                new pair<Letra, Nat> **[v.tamanoTablero()]{
                        new pair<Letra, Nat> *[v.tamanoTablero()]{nullptr}
                }
        ),
        _variante(v),
        _repositorio(r),
        _tiempo(0),
        _jugadores(new Jugador[k]{Jugador()}) {
    for (int j = 0; j < v.tamanoTablero(); j++)
        for (int i = 0; i < v.fichas(); i++) {
            auto ficha = *_repositorio.rbegin();
            _repositorio.pop_back();
            _jugadores[j].cantFichasPorLetra[ord(ficha)]++;
        }
}


Juego::Jugador::Jugador() :
        puntaje(0),
        jugadasSinCalcularPuntaje(0),
        cantFichasPorLetra(new Nat[TAMANIO_ALFABETO]{0}),
        historial(list<tuple<Ocurrencia, Nat>>()),
        historialSinVacias(list<tuple<Ocurrencia, Nat>>()) {}

bool Juego::jugadaValida(const Ocurrencia &o) {
    assert(false);
}

void Juego::ubicar(const Ocurrencia &o) {
    auto j = _jugadores[turno()];
    for (auto ficha: o) {
        _tablero[get<0>(ficha)][get<1>(ficha)] = new pair<Letra, Nat>{get<2>(ficha), _tiempo};
        j.cantFichasPorLetra[ord(get<2>(ficha))]--;
        auto puesta = *_repositorio.rbegin();
        _repositorio.pop_back();
        j.cantFichasPorLetra[ord(puesta)]--;
    }
    if (!o.empty()) {
        j.historialSinVacias.push_back(make_pair(o, _tiempo));
        j.jugadasSinCalcularPuntaje++;
    }
    j.historial.push_back(make_pair(o, _tiempo));
    _tiempo++;
}

const Variante &Juego::variante() {
    return _variante;
}

IdCliente Juego::turno() {
    return _tiempo % (sizeof(_jugadores) / sizeof(Nat));
}

Nat Juego::tiempo() const {
    return _tiempo;
}

Nat Juego::puntaje(IdCliente id) {
    assert(false);
}

bool Juego::enTablero(Nat i, Nat j) {
    return i < _variante.tamanoTablero() && j < _variante.tamanoTablero();
}

bool Juego::hayLetra(Nat i, Nat j) {
    return _tablero[i][j] != nullptr;
}

Letra Juego::ficha(Nat i, Nat j) {
    return get<0>(*_tablero[x][y]);
}

Nat Juego::fichaTiempo(Nat i, Nat j) {
    return get<1>(*_tablero[x][y]);
}

Nat Juego::cantLetrasTieneJugador(Letra x, Nat i) {
    return _jugadores[i].cantFichasPorLetra[ord(x)];
}