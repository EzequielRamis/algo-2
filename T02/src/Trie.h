#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include "Tipos.h"
#include "Letra.h"

using namespace std;

class Trie {
public:
    Trie();

    ~Trie();

    void definir(const Palabra &p);

    bool definida(const Palabra &p) const;

private:
    Trie *_hijos[TAMANIO_ALFABETO];
    bool _fin;

    static void borrarNodos(Trie *t);
};

#endif //TRIE_H
