#include "Juego.h"
#include "Letra.h"

Juego::Juego(Nat k, const Variante &v, const Repositorio &r) :
        _tablero(
                vector<vector<pair<Letra, Nat> *>>(v.tamanoTablero(),
                                                   vector<pair<Letra, Nat> *>(v.tamanoTablero(), nullptr))
        ),
        _variante(v),
        _repositorio(r),
        _tiempo(0),
        _jugadores(vector<Jugador>(k, Jugador())) {
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
        cantFichasPorLetra(vector<Nat>(TAMANIO_ALFABETO, 0)),
        historial(list<pair<Ocurrencia, Nat>>()),
        historialSinVacias(list<pair<Ocurrencia, Nat>>()) {}

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
    return _tiempo % _jugadores.size();
}

Nat Juego::tiempo() const {
    return _tiempo;
}

Nat Juego::puntaje(IdCliente id) {
    Jugador *jugador = &_jugadores[id];
    Nat *k = &jugador->jugadasSinCalcularPuntaje;
    auto histIt = jugador->historialSinVacias.rbegin();
    while (*k > 0) {
        pair<Ocurrencia, Nat> jugada = *histIt;
        Ocurrencia::iterator ocIt = jugada.first.begin();
        bool esHorizontal = true;
        tuple<Nat, Nat, Letra> ficha = *ocIt;
        ocIt++;
        if (ocIt != jugada.first.end())
            esHorizontal = get<0>(ficha) = get<0>(*ocIt);
        sumarPuntaje(*jugador, ficha, jugada.second, true, esHorizontal);
        for (auto fichaSecundaria: jugada.first)
            sumarPuntaje(*jugador, fichaSecundaria, jugada.second, false, !esHorizontal);
        histIt--;
        *k = *k - 1;
    }
    return jugador->puntaje;
}

void
Juego::sumarPuntaje(Jugador &jugador,
                    tuple<Nat, Nat, Letra> &ficha,
                    Nat tiempo,
                    bool esPrincipal,
                    bool esHorizontal) {
    Nat linea = esHorizontal ? get<0>(ficha) : get<1>(ficha);
    Nat i = esHorizontal ? get<1>(ficha) : get<0>(ficha) - (esPrincipal ? 0 : 1);
    Nat j = i + 1;
    sumarPuntajeEnDir(jugador, ficha, tiempo, linea, i, false, esHorizontal);
    sumarPuntajeEnDir(jugador, ficha, tiempo, linea, j, true, esHorizontal);
}

void Juego::sumarPuntajeEnDir(Jugador &jugador,
                              tuple<Nat, Nat, Letra> &ficha,
                              Nat tiempo,
                              Nat pos,
                              Nat desde,
                              bool adelante,
                              bool esHorizontal) {
    while (enTablero(pos, desde) &&
           hayLetra(pos, desde) &&
           fichaTiempo(pos, desde) <= tiempo) {
        if (esHorizontal)
            jugador.puntaje += _variante.puntajeLetra(this->ficha(pos, desde));
        else
            jugador.puntaje += _variante.puntajeLetra(this->ficha(desde, pos));
        if (adelante)
            desde++;
        else
            desde--;
    }
}

bool Juego::enTablero(Nat i, Nat j) {
    return i < _variante.tamanoTablero() && j < _variante.tamanoTablero();
}

bool Juego::hayLetra(Nat i, Nat j) {
    return _tablero[i][j] != nullptr;
}

Letra Juego::ficha(Nat i, Nat j) {
    return _tablero[i][j]->first;
}

Nat Juego::fichaTiempo(Nat i, Nat j) {
    return _tablero[i][j]->second;
}

Nat Juego::cantLetrasTieneJugador(Letra x, Nat i) {
    return _jugadores[i].cantFichasPorLetra[ord(x)];
}