#ifndef VARIANTE_H
#define VARIANTE_H

#include "Tipos.h"
#include "Letra.h"

class Variante {
public:
    /**
     * Construye una Fachada_Variante a partir de los parametros de las variantes
     */
    Variante(
            Nat tamanoTab,
            Nat cantFichas,
            const map<Letra, Nat> &puntajes,
            const set<vector<Letra>> &palabrasLegitimas
    );

    /**
     * Retorna el tamano del tablero de la variante
     */
    Nat tamanoTablero() const;

    /**
     * Retorna la cantidad de fichas que cada jugador deberia tener en su mano.
     */
    Nat fichas() const;

    /**
     * Retorna el puntaje de la letra l
     */
    Nat puntajeLetra(Letra l) const;

    /**
     * Indica si una palabra es legitima o no
     */
    bool palabraLegitima(const Palabra &palabra) const;

private:
    Nat _tablero;
    Nat _fichas;
    Nat *_puntaje;
    //Trie _palabras;
    Nat _palabraMasLarga;
};

#endif //VARIANTE_H
