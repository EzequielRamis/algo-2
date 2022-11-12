#ifndef TRIE_H_
#define TRIE_H_

#include "Letra.h"

using namespace std;

class trie {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    trie();

    /**
    DESTRUCTOR
    **/
    ~trie();

    /**
    INSERT 
    * Inserta una palabra legitima en el diccionario
    **/
    void insert(const Palabra& clave);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const Palabra& clave) const;

private:

    struct Nodo {
        Nodo* siguientes[TAMANIO_ALFABETO] = {};
        bool esLegitima;
        Nodo() : siguientes(), esLegitima(false){}
    };

    Nodo* raiz;

    void destruirNodos(Nodo* actual);
};

#endif // TRIE_H_
