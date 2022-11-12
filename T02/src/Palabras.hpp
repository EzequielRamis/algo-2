#include "Palabras.h"

trie::trie(): raiz(nullptr) {}

trie::~trie(){
    destruirNodos(raiz);
    raiz = nullptr;
}

void trie::destruirNodos(Nodo* actual){
    if (actual != nullptr){
        for (int i = 0; i < TAMANIO_ALFABETO; i++){
            destruirNodos(actual->siguientes[i]);
            delete[] actual->siguientes;
        }
    }
}

void trie::insert(const Palabra& clave){
    Nodo* actual = raiz;
    if (raiz == nullptr){
        actual = new Nodo();
        raiz = actual;
    }
    for (Letra l : clave){
        if (actual->siguientes[ord(l)] == nullptr) {
            actual->siguientes[ord(l)] = new Nodo();
        }
        actual = actual->siguientes[ord(l)];
    }
    actual->esLegitima = true;
}

int trie::count(const Palabra& clave) const{
    int res = 0;
    Nodo* actual = raiz;
    int i = 0;
    while (actual != nullptr && i < clave.size()){
        actual = actual->siguientes[ord(clave[i])];
        i++;
    }
    if (i == clave.size() && actual != nullptr && actual->esLegitima == true){
        res = 1;
    }
    return res;
}