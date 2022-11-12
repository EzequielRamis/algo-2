#ifndef JUEGO_H
#define JUEGO_H

#include "Tipos.h"
#include "Fachada_Variante.h"
#include "Tablero.h"
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
     * Ubica una Ocurrencia o en el juego
     *
     * Complejidad: O(m)
     *   donde m es el numero de fichas que se ubican
     */
    void ubicar(const Ocurrencia &o);

    /**
     * Retorna el id del cliente al cual le toca jugar
     *
     * Complejidad: O(1)
     */
    IdCliente turno();

    /**
     * Retorna informacion sobre la variante del juego
     *
     * Complejidad: O(1)
     */
    const Variante &variante();

    /**
     * Determina si una jugada es valida o no
     *
     * Complejidad: O(Lmax ** 2)
     */
    bool jugadaValida(const Ocurrencia &o);

    /**
     * Retorna true sii la coordenada se encuentra ocupada.
     *
     * Complejidad: O(1)
     */
    bool hayLetra(Nat x, Nat y);

    /**
     * Obtiene el contenido del tablero en una coordenada.
     *
     * Complejidad: O(1)
     */
    Letra letra(Nat i, Nat j);

    /**
     * Retorna el puntaje del jugador id
     *
     * Complejidad: O(1 + m*Lmax)
     *   donde m es la cantidad de fichas que ubico el jugador desde la ultima vez que se preguntó por su puntaje.
     */
    Nat puntaje(IdCliente id);


    /**
     * Dado un jugador id y una letra l, retorna cuantas fichas tiene el jugador de dicha letra.
     *
     * Complejidad: O(1)
     */
    Nat cantFicha(IdCliente id, Letra l);

private:
    struct Jugador {
        Jugador();
        //Jugador(const Jugador &aCopiar);
        //Jugador &operator=(const Jugador &d);

        Nat _puntaje;
        list<tuple<Ocurrencia, Nat>> _historial;
        list<tuple<Ocurrencia, Nat>> _historialSinVacias;
        Nat _jugadasSinCalcularPuntaje;
        vector<Nat> _cantFichasPorLetra;
    };

    Tablero _tablero;
    vector<Jugador> _jugadores;
    Nat _tiempo;
    Repositorio _repositorio;
    Variante _variante;
};

#endif // JUEGO_H
