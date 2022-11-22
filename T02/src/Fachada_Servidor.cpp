#include "Fachada_Servidor.h"

Fachada_Servidor::Fachada_Servidor(
        Nat cantJugadores,
        const Fachada_Variante &variante,
        const Repositorio &r
) : servidor(cantJugadores,
             variante.variante(),
             r) {}

IdCliente Fachada_Servidor::conectarCliente() {
    return servidor.conectarCliente();
}

void Fachada_Servidor::recibirMensaje(IdCliente id, const Ocurrencia &o) {
    servidor.recibirMensaje(id, o);
}

Nat Fachada_Servidor::jugadoresEsperados() {
    return servidor.jugadoresEsperados();
}

Nat Fachada_Servidor::jugadoresConectados() {
    return servidor.jugadoresConectados();
}

std::list<Notificacion> Fachada_Servidor::notificaciones(IdCliente id) {
    return servidor.notificaciones(id);
}