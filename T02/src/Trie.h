#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include "Tipos.h"

using namespace std;

class Trie {
public:
    Trie();

    void definir(Palabra p);

    bool definida(Palabra p) const;

private:
    vector<Trie *> _hijos;
    bool _fin;
};

#endif //TRIE_H
