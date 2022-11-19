#include "Servidor.h"

Servidor::Servidor(
        Nat cantJugadores,
        const Variante &variante,
        const Repositorio &r
) : _jugadoresConectados(0), _jugadoresEsperados(cantJugadores), _juego(Juego(cantJugadores, variante, r)),
    _notificaciones(vector<list<Notificacion>>(cantJugadores)) {}

IdCliente Servidor::conectarCliente() {
    _jugadoresConectados++;
    Notificacion n = Notificacion::nuevaIdCliente(_jugadoresConectados);
    _notificaciones[_jugadoresConectados].push_back(n);

    if (_jugadoresConectados == _jugadoresEsperados) {
        Notificacion empezar = Notificacion::nuevaEmpezar(_juego.variante().tamanoTablero());
        Notificacion turnoDe = Notificacion::nuevaTurnoDe(0);
        for (int i = 0; i < _notificaciones.size(); i++) {
            _notificaciones[i].push_back(empezar);
            _notificaciones[i].push_back(turnoDe);
        }
    }

    return _jugadoresConectados;
}

void Servidor::recibirMensaje(IdCliente id, const Ocurrencia &o) {
    if(_jugadoresConectados == _jugadoresEsperados && _juego.turno() == id && _juego.jugadaValida(o)) {

        Repositorio repo = _juego.repositorio();
        _juego.ubicar(o);
        Nat puntajeAnterior = _juego.consultarPuntaje(id);
        Nat puntajeNuevo = _juego.puntaje(id);

        Notificacion sumaPuntos = Notificacion::nuevaSumaPuntos(id, puntajeNuevo-puntajeAnterior);
        Notificacion ubicar = Notificacion::nuevaUbicar(id, o);
        Notificacion turnoDe = Notificacion::nuevaTurnoDe(_juego.turno());

        for (int i = 0; i < _notificaciones.size(); i++) {
            _notificaciones[i].push_back(ubicar);
            _notificaciones[i].push_back(sumaPuntos);
            _notificaciones[i].push_back(turnoDe);
        }

        multiset<Letra> letrasRepuestas;
        for (int i = 0; i < o.size(); i++) {
            letrasRepuestas.insert(*repo.rbegin());
            repo.pop_back();
        }

        Notificacion reponer = Notificacion::nuevaReponer(letrasRepuestas);
        _notificaciones[id].push_back(reponer);

    } else {
        Notificacion mal = Notificacion::nuevaMal();
        _notificaciones[id].push_back(mal);
    }
}

Nat Servidor::jugadoresEsperados() {
    return _jugadoresEsperados;
}

Nat Servidor::jugadoresConectados() {
    return _jugadoresConectados;
}


list<Notificacion> Servidor::notificaciones(IdCliente id) {
    return _notificaciones[id];
}
