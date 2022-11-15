#ifndef JUEGO_H
#define JUEGO_H

#include "Tipos.h"
#include "Fachada_Variante.h"
#include "Variante.h"

class Juego {
public:
    /**
     * Construye un juego a partir de la cantidad de jugadores k, la variante v y el repositorio r
     *
     * Complejidad: O(tamanoTab**2 + ALPHABET_SIZE*cantJugadores + cantFichas*cantJugadores)
     */
    Juego(Nat k, const Variante &v, const Repositorio &r);

    /**
     * Determina si una jugada es valida o no
     *
     * Complejidad: O(Lmax ** 2)
     */
    bool jugadaValida(const Ocurrencia &o);

    /**
     * Ubica una Ocurrencia o en el juego
     *
     * Complejidad: O(m)
     *   donde m es el numero de fichas que se ubican
     */
    void ubicar(const Ocurrencia &o);

    /**
     * Retorna informacion sobre la variante del juego
     *
     * Complejidad: O(1)
     */
    const Variante &variante();

    /**
     * Retorna el id del cliente al cual le toca jugar
     *
     * Complejidad: O(1)
     */
    IdCliente turno();

    /**
     * Retorna el tiempo actual del juego
     *
     * Complejidad: O(1)
     */
    Nat tiempo() const;

    /**
     * Retorna el puntaje del jugador id
     *
     * Complejidad: O(1 + m*Lmax)
     *   donde m es la cantidad de fichas que ubico el jugador desde la ultima vez que se preguntó por su puntaje.
     */
    Nat puntaje(IdCliente id);

    /**
     * Retorna true sii la coordenada se encuentra ocupada.
     *
     * Complejidad: O(1)
     */
    bool hayLetra(Nat x, Nat y);

    /**
     * Determina si una coordenada (i,j) está en el rango del tablero
     *
     * Complejidad: O(1)
     */
    bool enTablero(Nat i, Nat j);

    /**
     * Obtiene el contenido del tablero en una coordenada.
     *
     * Complejidad: O(1)
     */
    Letra ficha(Nat i, Nat j);

    /**
     * Obtiene el momento en que una ficha del tablero fue puesta dada una coordenada (i, j).
     *
     * Complejidad: O(1)
     */
    Nat fichaTiempo(Nat i, Nat j);

    /**
     * Dada una cierta letra x del alfabeto, conocer cuántas fichas tiene un jugador de dicha letra.
     *
     * Complejidad: O(1)
     */
    Nat cantLetrasTieneJugador(Letra x, Nat i);

private:
    struct Jugador {
        Jugador();

        Nat puntaje;
        list<pair<Ocurrencia, Nat>> historial;
        list<pair<Ocurrencia, Nat>> historialSinVacias;
        Nat jugadasSinCalcularPuntaje;
        vector<Nat> cantFichasPorLetra;
    };

    vector<vector<pair<Letra, Nat> *>> _tablero;
    vector<Jugador> _jugadores;
    Nat _tiempo;
    Repositorio _repositorio;
    Variante _variante;

    void sumarPuntaje(Jugador &jugador,
                      tuple<Nat, Nat, Letra> &ficha,
                      Nat tiempo, bool esPrincipal,
                      bool esHorizontal);

    void sumarPuntajeEnDir(Jugador &jugador,
                           tuple<Nat, Nat, Letra> &ficha,
                           Nat tiempo,
                           Nat pos,
                           Nat desde,
                           bool adelante,
                           bool esHorizontal);

    void ponerLetras(const Ocurrencia &o);

    void sacarLetras(const Ocurrencia &o);

    pair<Nat, Nat> rangoDePalabra(const tuple<Nat, Nat, Letra> &ficha, bool horizontal);

    bool formaPalabraLegitima(const pair<Nat, Nat> &r, bool horizontal, Nat padding);
};

#endif // JUEGO_H
