#include "Proxy2.h"

// Completar ...
Proxy::Proxy(ConexionJugador **conn) : _conn(conn) {}

void Proxy::enviarMensaje(std::string msg) {
    (*_conn)->enviarMensaje(msg);
}