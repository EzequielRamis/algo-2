#ifndef VARIANTE_H
#define VARIANTE_H

#include "Tipos.h"
#include "Letra.h"
#include "Trie.h"

class Variante {
public:
    /**
     * Construye una Variante a partir de los parametros de las variantes
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

    /**
     * Retorna la longitud de la palabra definida más larga
     */
    Nat longPalabraMasLarga() const;

private:
    Nat _tamanoTab;
    Nat _cantFichas;
    Nat _puntajes[TAMANIO_ALFABETO];
    Trie _palabras;
    Nat _longPalabraMasLarga;
};

#endif //VARIANTE_H
