#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

template<class T>
class Conjunto {
public:

    // Constructor. Genera un conjunto vacío.
    Conjunto();

    // Destructor. Debe dejar limpia la memoria.
    ~Conjunto();

    // Inserta un elemento en el conjunto. Si este ya existe,
    // el conjunto no se modifica.
    void insertar(const T &);

    // Decide si un elemento pertenece al conjunto o no.
    bool pertenece(const T &) const;

    // Borra un elemento del conjunto. Si este no existe,
    // el conjunto no se modifica.
    void remover(const T &);

    // Siguiente elemento al recibido por párametro, en orden.
    // Pre: el elemento está en el conjunto y no es el máximo del conjunto.
    const T &siguiente(const T &elem);

    // Devuelve el mínimo elemento del conjunto según <.
    const T &minimo() const;

    // Devuelve el máximo elemento del conjunto según <.
    const T &maximo() const;

    // Devuelve la cantidad de elementos que tiene el conjunto.
    unsigned int cardinal() const;

    // Muestra el conjunto.
    void mostrar(std::ostream &) const;

private:

    /**
     * Completar con lo que sea necesario...
     **/

    unsigned int _cardinal;

    struct Nodo {
        // El constructor, toma el elemento al que representa el nodo.
        Nodo(const T &v) :
                valor(v), izq(nullptr), der(nullptr), padre(nullptr) {};

        // El elemento al que representa el nodo.
        T valor;
        // Puntero a la raíz del subárbol izquierdo.
        Nodo *izq;
        // Puntero a la raíz del subárbol derecho.
        Nodo *der;
        // Puntero al padre.
        Nodo *padre;
    };

    // Puntero a la raíz de nuestro árbol.
    Nodo *_raiz;

    // Devuelve el nodo con ese valor o su padre si no está.
    Nodo *irANodo(Nodo *n, const T &elem) const;

    Nodo *minimoDesde(Nodo *n) const;

    Nodo *maximoDesde(Nodo *n) const;

    Nodo *siguienteNodo(const T &elem);
};

template<class T>
std::ostream &operator<<(std::ostream &os, const Conjunto<T> &c) {
    c.mostrar(os);
    return os;
}

#include "Conjunto.hpp"

#endif // CONJUNTO_H_
