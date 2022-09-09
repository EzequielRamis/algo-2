#include "SistemaDeMensajes.h"

// Completar...
SistemaDeMensajes::SistemaDeMensajes() {
    for (int i = 0; i < 4; ++i)
        _conns[i] = nullptr;
}

void SistemaDeMensajes::registrarJugador(int id, std::string ip) {
    if (registrado(id))
        desregistrarJugador((id));
    _conns[id] = new ConexionJugador(ip);
}

bool SistemaDeMensajes::registrado(int id) const {
    return _conns[id] != nullptr;
}

void SistemaDeMensajes::enviarMensaje(int id, std::string mensaje) {
    _conns[id]->enviarMensaje(mensaje);
}

string SistemaDeMensajes::ipJugador(int id) const {
    return _conns[id]->ip();
}

SistemaDeMensajes::~SistemaDeMensajes() {
    for (ConexionJugador *c: _conns)
        delete c;
    for (Proxy *p: _proxys)
        delete p;
}

void SistemaDeMensajes::desregistrarJugador(int id) {
    delete _conns[id];
    _conns[id] = nullptr;
}

// Ejercicio 4
//Proxy *SistemaDeMensajes::obtenerProxy(int id) {
//    Proxy *p = new Proxy(_conns[id]);
//    _proxys.push_back(p);
//    return p;
//}

Proxy *SistemaDeMensajes::obtenerProxy(int id) {
    Proxy *p = new Proxy(&_conns[id]);
    _proxys.push_back(p);
    return p;
}
