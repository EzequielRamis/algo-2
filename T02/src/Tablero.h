#ifndef TABLERO_H
#define TABLERO_H

#include "Tipos.h"
#include "Fachada_Variante.h"


class Tablero {
public:
    /**
     * Construye un tablero a partir de la cantidad de posiciones
     *
     * Complejidad: O(tamanoTab**2)
     */
    Tablero(Nat n);

    /**
     * Ubica una Ocurrencia o en el juego
     *
     * Complejidad: O(m)
     *   donde m es el numero de fichas que se ubican
     */
    void ubicar(const Ocurrencia& o);

    /**
     * Determina si una jugada es valida o no
     *
     * Complejidad: O(Lmax ** 2)
     */
    bool jugadaValida(const Ocurrencia& o);

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

private:
    vector<vector<*tuple<Letra,int>>> tablero;
};

#endif // TABLERO_H
