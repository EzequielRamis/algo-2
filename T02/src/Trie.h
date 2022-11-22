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
    struct Nodo {
        Nodo();

        vector<Nodo *> hijos;
        bool fin;
    };

    Nodo *_raiz;

    static void borrarNodos(Nodo *n);
};

#endif //TRIE_H
