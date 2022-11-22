#include "Trie.h"

Trie::Trie() : _raiz(nullptr) {}

Trie::Nodo::Nodo() : fin(false),
                     hijos{nullptr} {}

Trie::~Trie() {
    borrarNodos(_raiz);
}

void Trie::borrarNodos(Nodo *n) {
    if (n == nullptr) return;
    for (auto &h: n->hijos)
        borrarNodos(h);
    delete n;
}

void Trie::definir(const Palabra &p) {
    Nodo *nodo;
    if (_raiz == nullptr)
        _raiz = new Nodo();
    nodo = _raiz;
    for (auto pIt: p) {
        Nat letra = ord(pIt);
        if (nodo->hijos[letra] == nullptr)
            nodo->hijos[letra] = new Nodo();
        nodo = nodo->hijos[letra];
    }
    nodo->fin = true;
}

bool Trie::definida(const Palabra &p) const {
    const Nodo *nodo = _raiz;
    auto pIt = p.begin();
    while (pIt != p.end() && nodo->hijos[ord(*pIt)] != nullptr) {
        nodo = nodo->hijos[ord(*pIt)];
        pIt++;
    }
    return pIt == p.end() && nodo->fin;
}
