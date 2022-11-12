#include "Juego.h"
#include "Letra.h"

Juego::Juego(Nat k, const Variante &v, const Repositorio &r) : _tablero(k), _variante(v), _repositorio(r),
                                                               _tiempo(1), _jugadores(vector<Jugador>()) {}


Juego::Jugador::Jugador() : _puntaje(0), _jugadasSinCalcularPuntaje(0), _cantFichasPorLetra(vector<Nat>()),
                            _historial(list<tuple<Ocurrencia, Nat>>()),
                            _historialSinVacias(list<tuple<Ocurrencia, Nat>>()) {}

void Juego::ubicar(const Ocurrencia &o) {
    _tablero.ubicar(o);
}

IdCliente Juego::turno() {
    return 1;
}

const Variante &Juego::variante() {
    return _variante;
}

bool Juego::jugadaValida(const Ocurrencia &o) {
    return _tablero.jugadaValida(o);
}

bool Juego::hayLetra(Nat x, Nat y) {
    return _tablero.hayLetra(x, y);
}

Letra Juego::letra(Nat i, Nat j) {
    return _tablero.letra(i, j);
}

Nat Juego::puntaje(IdCliente id) {
    return _jugadores[id]._puntaje;
}

Nat Juego::cantFicha(IdCliente id, Letra l) {
    return _jugadores[id]._cantFichasPorLetra[ord(l)];
}