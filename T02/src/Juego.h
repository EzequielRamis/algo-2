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
    Juego(Nat k, const Variante &v, Repositorio r);

    ~Juego();

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
    Letra ficha(Nat i, Nat j);

    /**
     * Calcula y retorna el puntaje del jugador id
     *
     * Complejidad: O(1 + m*Lmax)
     *   donde m es la cantidad de fichas que ubico el jugador desde la ultima vez que se preguntó por su puntaje.
     */
    Nat puntaje(IdCliente id);

    /**
     * Retorna el repositorio
     *
     * Complejidad: O(1)
     */
    Repositorio repositorio() const;

    /**
     * Dada una cierta letra x del alfabeto, conocer cuántas fichas tiene un jugador de dicha letra.
     *
     * Complejidad: O(1)
     */
    Nat cantLetrasTieneJugador(Letra x, Nat i);

    /**
     * Obtiene el mazo de letras del jugador i (Sirve para el constructor Reponer del tipo Notificación)
     *
     * Complejidad: O(F)
     */
    multiset<Letra> mazoDeJugador(Nat i);

    /**
     * Determina si una coordenada (i,j) está en el rango del tablero
     *
     * Complejidad: O(1)
     */
    bool enTablero(Nat i, Nat j);

    /**
     * Obtiene el momento en que una ficha del tablero fue puesta dada una coordenada (i, j).
     *
     * Complejidad: O(1)
     */
    Nat fichaTiempo(Nat i, Nat j);

    /**
     * Retorna el tiempo actual del juego
     *
     * Complejidad: O(1)
     */
    Nat tiempo() const;

private:
    struct Jugador {
        Jugador();

        Nat puntaje;
        list<pair<Ocurrencia, Nat>> historial;
        Nat jugadasSinCalcularPuntaje;
        vector<Nat> cantFichasPorLetra;
    };

    vector<vector<pair<Letra, Nat> *>> _tablero;
    vector<Jugador> _jugadores;
    Nat _tiempo;
    Repositorio _repositorio;
    const Variante &_variante;

    Nat calcularPuntaje(const pair<Ocurrencia, Nat> &jugada);

    void ponerLetras(const Ocurrencia &o);

    void sacarLetras(const Ocurrencia &o);

    pair<Nat, Nat> rangoDePalabra(const tuple<Nat, Nat, Letra> &ficha, bool horizontal, Nat antesDeTiempo);

    bool formaPalabraLegitima(const pair<Nat, Nat> &r, bool horizontal, Nat padding);

    bool haySuperpuestas(const Ocurrencia &o) const;

    static bool esHorizontal(const Ocurrencia &o);

    static bool esVertical(const Ocurrencia &o);

};

#endif // JUEGO_H
