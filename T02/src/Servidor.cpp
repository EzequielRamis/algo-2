#include "Servidor.h"

Servidor::Servidor(
        Nat cantJugadores,
        const Variante &variante,
        const Repositorio &r
) : _jugadoresConectados(0),
    _jugadoresEsperados(cantJugadores),
    _juego(cantJugadores, variante, r),
    _notificaciones(cantJugadores),
    _mazos(cantJugadores) {
    // O(F*K)
    for (int i = 0; i < cantJugadores; i++)
        _mazos[i] = _juego.mazoDeJugador(i);
}

IdCliente Servidor::conectarCliente() {
    Notificacion n = Notificacion::nuevaIdCliente(_jugadoresConectados);
    _notificaciones[_jugadoresConectados].push_back(n);
    _jugadoresConectados++;

    if (empezo()) {
        Notificacion empezar = Notificacion::nuevaEmpezar(_juego.variante().tamanoTablero());
        Notificacion turnoDe = Notificacion::nuevaTurnoDe(0);
        for (int i = 0; i < (int) _notificaciones.size(); i++) {
            _notificaciones[i].push_back(empezar);
            _notificaciones[i].push_back(turnoDe);
            _notificaciones[i].push_back(Notificacion::nuevaReponer(_mazos[i]));
        }
    }

    return n.idCliente();
}

list<Notificacion> Servidor::notificaciones(IdCliente id) {
    list<Notificacion> n = _notificaciones[id];
    _notificaciones[id] = list<Notificacion>();
    return n;
}

void Servidor::recibirMensaje(IdCliente id, const Ocurrencia &o) {
    if (empezo() && _juego.turno() == id && _juego.jugadaValida(o)) {
        auto *repoViejo = new Repositorio(_juego.repositorio());

        multiset<Letra> letrasRepuestas;
        for (int i = 0; i < o.size(); i++) {
            letrasRepuestas.insert(*repoViejo->begin());
            repoViejo->pop_front();
        }
        delete repoViejo;

        Nat puntajeViejo = _juego.puntaje(id);
        _juego.ubicar(o);
        Nat puntajeNuevo = _juego.puntaje(id);

        Notificacion sumaPuntos = Notificacion::nuevaSumaPuntos(id, puntajeNuevo - puntajeViejo);
        Notificacion ubicar = Notificacion::nuevaUbicar(id, o);
        Notificacion turnoDe = Notificacion::nuevaTurnoDe(_juego.turno());
        Notificacion reponer = Notificacion::nuevaReponer(letrasRepuestas);

        for (int i = 0; i < _notificaciones.size(); i++) {
            _notificaciones[i].push_back(ubicar);
            _notificaciones[i].push_back(sumaPuntos);
            if (i == id)
                _notificaciones[id].push_back(reponer);
            _notificaciones[i].push_back(turnoDe);
        }

        _mazos[id] = _juego.mazoDeJugador(id); // O(F)
    } else {
        Notificacion mal = Notificacion::nuevaMal();
        _notificaciones[id].push_back(mal);
    }
}

Nat Servidor::jugadoresEsperados() const {
    return _jugadoresEsperados;
}

Nat Servidor::jugadoresConectados() const {
    return _jugadoresConectados;
}

bool Servidor::empezo() const {
    return _jugadoresConectados == _jugadoresEsperados;
}