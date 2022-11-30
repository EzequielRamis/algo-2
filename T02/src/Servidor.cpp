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
    _notificacionesParticulares[n.idCliente()].push_back(make_tuple(_cantMensajesRecibidos, _juego.tiempo(), n));
    _jugadoresConectados++;

    if (empezo()) {
        Notificacion empezar = Notificacion::nuevaEmpezar(_juego.variante().tamanoTablero());
        Notificacion turnoDe = Notificacion::nuevaTurnoDe(0);
        _notificacionesGlobales.emplace_back(_cantMensajesRecibidos,
                                             _juego.tiempo(),
                                             empezar);
        _notificacionesGlobales.emplace_back(_cantMensajesRecibidos,
                                             _juego.tiempo(),
                                             turnoDe);
        for (int i = 0; i < (int) _notificacionesParticulares.size(); i++) {
            _notificacionesParticulares[i]
                    .emplace_back(_cantMensajesRecibidos,
                                  _juego.tiempo(),
                                  Notificacion::nuevaReponer(_mazos[i]));
        }
    }

    return n.idCliente();
}

// Hay dos listas de notifs, una global y otra personal.
// Ambas tienen el tipo <Indice de mensaje recibido, Notificacion>.
// Despues hay un vector de cantidad de mensajes sin consultar por id.
// En "notificaciones" recorro con un while y hago un pseudo two-fingers sort.

list<Notificacion> Servidor::notificaciones(IdCliente id) {
    list<Notificacion> res;
    auto nIt = _notificacionesGlobales.rbegin();
    auto rIt = _notificacionesParticulares[id].rbegin();

    while ((nIt != _notificacionesGlobales.rend() &&
            get<0>(*nIt) >= _indiceDeMensajesSinConsultar[id]) ||
           (rIt != _notificacionesParticulares[id].rend())
            ) {
//        if (nIt != _notificacionesGlobales.rend() &&
//            get<2>(*nIt).tipoNotificacion() == TipoNotificacion::TurnoDe &&
//            get<1>(*nIt) % jugadoresEsperados() == id) {
//            res.push_front(get<2>(*nIt));
//            res.push_front(get<2>(*rIt));
//            rIt++;
//            nIt++;
//            continue;
//        }
        if (nIt != _notificacionesGlobales.rend() &&
            get<0>(*nIt) >= get<0>(*rIt)) {
            res.push_front(get<2>(*nIt));
            nIt++;
        } else {
            res.push_front(get<2>(*rIt));
            rIt++;
        }
    }


//    for (int i = 0; i < _cantNotifsSinConsultar[id]; i++) {
//        if (rIt->second.tipoNotificacion() == TipoNotificacion::IdCliente &&
//            rIt->second.idCliente() == id)
//            res.push_front(rIt->second);
//        if (nIt != _notificacionesGlobales.rend()) {
//            res.push_front(nIt->second);
//
//            if ((nIt->second.tipoNotificacion() == TipoNotificacion::TurnoDe &&
//                 nIt->first % jugadoresEsperados() == id + 1)) {
//                res.push_front(rIt->second);
//                rIt++;
//            }
//
//            nIt++;
//        }
//    }

    _indiceDeMensajesSinConsultar[id] = _cantMensajesRecibidos;
    _notificacionesParticulares[id].clear();

    return res;
}

// La complejidad de recibirMensaje depende de la cantidad de jugadores, que no sigue el enunciado
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

        _notificacionesGlobales.emplace_back(_cantMensajesRecibidos, _juego.tiempo(), ubicar);
        _notificacionesGlobales.emplace_back(_cantMensajesRecibidos, _juego.tiempo(), sumaPuntos);
        _notificacionesGlobales.emplace_back(_cantMensajesRecibidos, _juego.tiempo(), turnoDe);

        _notificacionesParticulares[id].emplace_back(_cantMensajesRecibidos, _juego.tiempo(), reponer);

        _mazos[id] = _juego.mazoDeJugador(id); // O(F)
    } else {
        Notificacion mal = Notificacion::nuevaMal();
        _notificacionesParticulares[id].emplace_back(_cantMensajesRecibidos, _juego.tiempo(), mal);
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