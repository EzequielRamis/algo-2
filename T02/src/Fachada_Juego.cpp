#include "Fachada_Juego.h"

Fachada_Juego::Fachada_Juego(Nat k, const Fachada_Variante &v, const Repositorio &r) :
        juego(k, v.variante(), r),
        fachadaVariante(v) {}

void Fachada_Juego::ubicar(const Ocurrencia &o) {
    juego.ubicar(o);
}

IdCliente Fachada_Juego::turno() {
    return juego.turno();
}

const Fachada_Variante &Fachada_Juego::variante() {
    return fachadaVariante;
}

bool Fachada_Juego::jugadaValida(const Ocurrencia &o) {
    return juego.jugadaValida(o);
}

bool Fachada_Juego::hayLetra(Nat x, Nat y) {
    return juego.hayLetra(x, y);
}

Letra Fachada_Juego::letra(Nat i, Nat j) {
    return juego.ficha(i, j);
}

Nat Fachada_Juego::puntaje(IdCliente id) {
    return juego.puntaje(id);
}

Nat Fachada_Juego::cantFicha(IdCliente id, Letra l) {
    return juego.cantLetrasTieneJugador(l, id);
}