#include "Trie.h"

Trie::Trie() : _fin(false),
               _hijos{nullptr} {}

Trie::~Trie() {
    for (auto h: _hijos)
        borrarNodos(h);
}

void Trie::borrarNodos(Trie *t) {
    if (t != nullptr)
        for (auto h: t->_hijos)
            borrarNodos(h);
}

void Trie::definir(const Palabra &p) {
    auto pIt = p.begin();
    if (pIt == p.end()) {
        _fin = true;
        return;
    }
    Trie *nodo = this;
    while (nodo->_hijos[ord(*pIt)] != nullptr) {
        nodo = nodo->_hijos[ord(*pIt)];
        pIt++;
    }
    while (pIt != p.end()) {
        Letra letra = *pIt;
        nodo->_hijos[ord(letra)] = new Trie();
        nodo = nodo->_hijos[ord(letra)];
        pIt++;
    }
    nodo->_fin = true;
}

bool Trie::definida(const Palabra &p) const {
    auto pIt = p.begin();
    if (pIt == p.end())
        return _fin;
    const Trie *nodo = this;
    while (pIt != p.end() && nodo->_hijos[ord(*pIt)] != nullptr) {
        Letra letra = *pIt;
        nodo = nodo->_hijos[ord(letra)];
        pIt++;
    }
    return pIt == p.end() && nodo->_fin;
}
