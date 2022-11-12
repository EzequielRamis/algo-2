#include "Fachada_Juego.h"

Fachada_Juego::Fachada_Juego(Nat k, const Fachada_Variante &v, const Repositorio &r) : juego(
        Juego(k, Variante(v.), r)) {}

void Fachada_Juego::ubicar(const Ocurrencia &o) {
    juego.ubicar(o);
}

IdCliente Fachada_Juego::turno() {
    return juego.turno();
}

const Fachada_Variante &Fachada_Juego::variante() {
    return juego.variante();
}

bool Fachada_Juego::jugadaValida(const Ocurrencia &o) {
    return juego.jugadaValida(o);
}

bool Fachada_Juego::hayLetra(Nat x, Nat y) {
    return juego.hayLetra(x, y);
}

Letra Fachada_Juego::letra(Nat i, Nat j) {
    return juego.letra(i, j);
}

Nat Fachada_Juego::puntaje(IdCliente id) {
    return juego.puntaje();
}

Nat Fachada_Juego::cantFicha(IdCliente id, Letra l) {
    return juego.cantFicha(id, l);
}