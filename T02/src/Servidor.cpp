#include "Servidor.h"

Servidor::Servidor(
        Nat cantJugadores,
        const Variante &variante,
        const Repositorio &r
) : _jugadoresConectados(0),
    _jugadoresEsperados(cantJugadores),
    _juego(cantJugadores, variante, r),
    _notificacionesParticulares(cantJugadores),
    _indiceDeMensajesSinConsultar(cantJugadores, -1),
    _cantMensajesRecibidos(0),
    _mazos(cantJugadores) {
    // O(F*K)
    for (int i = 0; i < cantJugadores; i++)
        _mazos[i] = _juego.mazoDeJugador(i);
}

IdCliente Servidor::conectarCliente() {
    Notificacion n = Notificacion::nuevaIdCliente(_jugadoresConectados);
    _notificacionesParticulares[n.idCliente()].emplace_front(-1,
                                                             n);
    _jugadoresConectados++;

    if (empezo()) {
        Notificacion empezar = Notificacion::nuevaEmpezar(_juego.variante().tamanoTablero());
        Notificacion turnoDe = Notificacion::nuevaTurnoDe(0);
        _notificacionesGlobales.emplace_front(_cantMensajesRecibidos,
                                              empezar);
        _notificacionesGlobales.emplace_front(_cantMensajesRecibidos,
                                              turnoDe);
        for (int i = 0; i < (int) _notificacionesParticulares.size(); i++) {
            _notificacionesParticulares[i]
                    .emplace_front(_cantMensajesRecibidos,
                                   Notificacion::nuevaReponer(_mazos[i]));
        }
    }

    return n.idCliente();
}

list<Notificacion> Servidor::notificaciones(IdCliente id) {
    list<Notificacion> res;
    auto gIt = _notificacionesGlobales.begin();
    auto pIt = _notificacionesParticulares[id].begin();

    while ((gIt != _notificacionesGlobales.end() &&
            gIt->first >= _indiceDeMensajesSinConsultar[id]
           ) ||
           pIt != _notificacionesParticulares[id].end()) {

        if (pIt->second.tipoNotificacion() == TipoNotificacion::Mal ||
            pIt->second.tipoNotificacion() == TipoNotificacion::IdCliente) {
            res.push_front(pIt->second);
            pIt++;
        } else if (gIt->second.tipoNotificacion() == TipoNotificacion::TurnoDe) {
            if (next(gIt)->second.tipoNotificacion() == TipoNotificacion::Empezar) {
                if (pIt->second.tipoNotificacion() == TipoNotificacion::Reponer &&
                    //                    true) {
                    gIt->first == pIt->first) {
                    res.push_front(pIt->second);
                    pIt++;
                }
                res.push_front(gIt->second);
                gIt++;
                res.push_front(gIt->second);
                gIt++;
            } else {
                res.push_front(gIt->second);
                gIt++;
                res.push_front(gIt->second);
                gIt++;
                if (pIt->second.tipoNotificacion() == TipoNotificacion::Reponer &&
                    //                    true) {
                    gIt->first == pIt->first) {
                    res.push_front(pIt->second);
                    pIt++;
                }
                res.push_front(gIt->second);
                gIt++;
            }
        } else {
            res.push_front(gIt->second);
            gIt++;
        }
        _indiceDeMensajesSinConsultar[id]++;
    }

    _notificacionesParticulares[id].clear();

    return res;
}

void Servidor::recibirMensaje(IdCliente id, const Ocurrencia &o) {
    _cantMensajesRecibidos++;
    _indiceDeMensajesSinConsultar[id]++;
    if (empezo() && _juego.turno() == id && _juego.jugadaValida(o)) {
        Nat puntajeViejo = _juego.puntaje(id);
        multiset<Letra> letrasRepuestas = _juego.ubicar(o);
        Nat puntajeNuevo = _juego.puntaje(id);

        Notificacion sumaPuntos = Notificacion::nuevaSumaPuntos(id, puntajeNuevo - puntajeViejo);
        Notificacion ubicar = Notificacion::nuevaUbicar(id, o);
        Notificacion turnoDe = Notificacion::nuevaTurnoDe(_juego.tiempo());
        Notificacion reponer = Notificacion::nuevaReponer(letrasRepuestas);

        _notificacionesGlobales.emplace_front(_cantMensajesRecibidos, ubicar);
        _notificacionesGlobales.emplace_front(_cantMensajesRecibidos, sumaPuntos);
        _notificacionesGlobales.emplace_front(_cantMensajesRecibidos, turnoDe);

        _notificacionesParticulares[id].emplace_front(_cantMensajesRecibidos, reponer);

        _mazos[id] = _juego.mazoDeJugador(id); // O(F)
    } else {
        Notificacion mal = Notificacion::nuevaMal();
        _notificacionesParticulares[id].emplace_front(_cantMensajesRecibidos, mal);
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