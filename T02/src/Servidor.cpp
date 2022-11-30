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
                                                             -1,
                                                             n);
    _jugadoresConectados++;

    if (empezo()) {
        Notificacion empezar = Notificacion::nuevaEmpezar(_juego.variante().tamanoTablero());
        Notificacion turnoDe = Notificacion::nuevaTurnoDe(0);
        _notificacionesGlobales.emplace_front(_cantMensajesRecibidos,
                                              -1,
                                              empezar);
        _notificacionesGlobales.emplace_front(_cantMensajesRecibidos,
                                              -1,
                                              turnoDe);
        for (int i = 0; i < (int) _notificacionesParticulares.size(); i++) {
            _notificacionesParticulares[i]
                    .emplace_front(_cantMensajesRecibidos,
                                   -1,
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
    // Preludio son las notificaciones antes de que empieze el juego.
    list<Notificacion> preludio;
    auto comienzoGlobal = _notificacionesGlobales.begin();
    auto comienzoParticular = _notificacionesParticulares[id].begin();
    if (_indiceDeMensajesSinConsultar[id] == -1) {
        if (_notificacionesParticulares[id].size() > 0) {
            // IdCliente
            preludio.push_front(get<2>(*comienzoParticular));
            comienzoParticular++;
            // Mensajes inválidos
            while (get<2>(*comienzoParticular).tipoNotificacion() == TipoNotificacion::Mal) {
                preludio.push_front(get<2>(*comienzoParticular));
                comienzoParticular++;
            }
            if (empezo()) {
                // Empezar
                preludio.push_front(get<2>(*comienzoGlobal));
                comienzoGlobal++;
                // TurnoDe
                preludio.push_front(get<2>(*comienzoGlobal));
                // Reponer
                preludio.push_front(get<2>(*comienzoParticular));
//                _indiceDeMensajesSinConsultar[id]++;
            }
        }
    }
    // Mientras |global| > 0 y
    //   Agrego notifs globales hasta TurnoDe id + 1
    //   Agrego notifs particulares
    //
    auto gIt = comienzoGlobal;
    auto pIt = comienzoParticular;

    while (gIt != _notificacionesGlobales.end() &&
           //           _indiceDeMensajesSinConsultar[id] < _cantMensajesRecibidos) {
           get<1>(*gIt) >= _indiceDeMensajesSinConsultar[id]) {

        auto primer = gIt;
        if (pIt != _notificacionesParticulares[id].end() &&
            get<1>(*pIt) >= get<1>(*gIt) &&
            get<2>(*pIt).tipoNotificacion() == TipoNotificacion::Mal) {
            primer = pIt;
        }

        Notificacion primerNotif = get<2>(*primer);

        switch (primerNotif.tipoNotificacion()) {
            case TipoNotificacion::Mal:
                res.push_front(primerNotif);
                break;
            case TipoNotificacion::TurnoDe:
                res.push_front(primerNotif);
                primer++;
                res.push_front(get<2>(*primer));
                primer++;
                if (get<2>(*primer).tipoNotificacion() == TipoNotificacion::Reponer)
                    res.push_front(get<2>(*primer));
                primer++;
                res.push_front(get<2>(*primer));
                primer++;
                res.push_front(get<2>(*primer));
                break;
        }


//        if (pIt != _notificacionesParticulares[id].end() &&
//            get<1>(*pIt) >= get<1>(*gIt)) {
//            if (get<2>(*gIt).tipoNotificacion() == TipoNotificacion::TurnoDe) {
////                    if (get<2>(*gIt).tipoNotificacion() == TipoNotificacion::TurnoDe &&
////                        (get<1>(*gIt) - 1) % jugadoresEsperados() == id) {
//                res.push_front(get<2>(*gIt));
//                gIt++;
//            }
////            if (get<2>(*pIt).tipoNotificacion() == TipoNotificacion::IdCliente) {
////                break;
////            }
//            res.push_front(get<2>(*pIt));
//            pIt++;
//        } else {
//            res.push_front(get<2>(*gIt));
//            gIt++;
//        }
        _indiceDeMensajesSinConsultar[id]++;
    }

    while (pIt != _notificacionesParticulares[id].end()) {
//        if (get<2>(*pIt).tipoNotificacion() == TipoNotificacion::IdCliente) {
//            break;
//        }
        res.push_front(get<2>(*pIt));
        pIt++;
    }

//    _indiceDeMensajesSinConsultar[id] = _cantMensajesRecibidos;
    _notificacionesParticulares[id].clear();

    for (auto p: preludio)
        res.push_back(p);

    // Hay IdCliente duplicados
    if (res.size() > 1) {
        auto idCheck = res.begin();
        auto idCheck2 = next(idCheck);
        if (idCheck->tipoNotificacion() == TipoNotificacion::IdCliente &&
            idCheck->tipoNotificacion() == idCheck2->tipoNotificacion())
            res.pop_front();
    }

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

        _notificacionesGlobales.emplace_front(_cantMensajesRecibidos, _juego.tiempo(), ubicar);
        _notificacionesGlobales.emplace_front(_cantMensajesRecibidos, _juego.tiempo(), sumaPuntos);
        _notificacionesGlobales.emplace_front(_cantMensajesRecibidos, _juego.tiempo(), turnoDe);

        _notificacionesParticulares[id].emplace_front(_cantMensajesRecibidos, _juego.tiempo(), reponer);

        _mazos[id] = _juego.mazoDeJugador(id); // O(F)
    } else {
        Notificacion mal = Notificacion::nuevaMal();
        _notificacionesParticulares[id].emplace_front(_cantMensajesRecibidos, _juego.tiempo(), mal);
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