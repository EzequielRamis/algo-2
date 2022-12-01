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
    _notificacionesParticulares[n.idCliente()].emplace_front(_cantMensajesRecibidos,
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
    // Preludio son las notificaciones antes de que empieze el juego.
    list<Notificacion> preludio;
    auto gIt = _notificacionesGlobales.begin();
    auto pIt = _notificacionesParticulares[id].begin();
    if (_indiceDeMensajesSinConsultar[id] == -1) {
        if (_notificacionesParticulares[id].size() > 0) {
            // IdCliente
            preludio.push_front(pIt->second);
            pIt++;
            // Mensajes inválidos
            while (pIt->second.tipoNotificacion() == TipoNotificacion::Mal) {
                preludio.push_front(pIt->second);
                pIt++;
            }
            if (empezo()) {
                // Empezar
                preludio.push_front(gIt->second);
                gIt++;
                // TurnoDe
                preludio.push_front(gIt->second);
                // Reponer
                preludio.push_front(pIt->second);
            }
        }
    }

    while (gIt != _notificacionesGlobales.end() &&
           gIt->first > _indiceDeMensajesSinConsultar[id]) {

        if (pIt->second.tipoNotificacion() == TipoNotificacion::Mal) {
            res.push_front(pIt->second);
            pIt++;
            _indiceDeMensajesSinConsultar[id]++;
            break;
        } else if (gIt->second.tipoNotificacion() == TipoNotificacion::TurnoDe) {
            res.push_front(gIt->second);
            gIt++;
            if (pIt->second.tipoNotificacion() == TipoNotificacion::Reponer) {
                res.push_front(pIt->second);
                pIt++;
            }
            res.push_front(gIt->second);
            gIt++;
            res.push_front(gIt->second);
            _indiceDeMensajesSinConsultar[id]++;
        } else
            break;

    }

    while (pIt != _notificacionesParticulares[id].end()) {
        if (empezo() &&
            pIt->second.tipoNotificacion() == TipoNotificacion::IdCliente)
            break;
        res.push_front(pIt->second);
        pIt++;
    }

    _notificacionesParticulares[id].clear();

    for (auto p: preludio)
        res.push_back(p);

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