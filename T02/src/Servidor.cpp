#include "Servidor.h"

Servidor::Servidor(
        Nat cantJugadores,
        const Variante &variante,
        const Repositorio &r
) : _jugadoresConectados(0), _jugadoresEsperados(cantJugadores), _juego(Juego(cantJugadores, variante, r)),
    _notificaciones(vector<list<Notificacion>>(cantJugadores)) {}

IdCliente Servidor::conectarCliente() {
    return 0;
}

void Servidor::recibirMensaje(IdCliente id, const Ocurrencia &o) {
}

Nat Servidor::jugadoresEsperados() {
    return _jugadoresEsperados;
}

Nat Servidor::jugadoresConectados() {
    return _jugadoresConectados;
}


list<Notificacion> Servidor::notificaciones(IdCliente id) {
    _notificaciones[id];
}