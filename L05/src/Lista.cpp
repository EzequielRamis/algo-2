#include "Lista.h"

Lista::Lista() : _pri(nullptr), _ult(nullptr) {}

Lista::Lista(const Lista &l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

void Lista::destruirNodos() {
    Nodo *actual = this->_pri;
    while (actual != nullptr) {
        Nodo *siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

Lista::~Lista() {
    destruirNodos();
}

Lista &Lista::operator=(const Lista &aCopiar) {
    destruirNodos();
    this->_pri = nullptr;
    this->_ult = nullptr;
    Nodo *actual = aCopiar._pri;
    while (actual != nullptr) {
        this->agregarAtras(actual->valor);
        actual = actual->siguiente;
    }
    return *this;
}

void Lista::agregarAdelante(const int &elem) {
    Nodo *nuevo = new Nodo(elem);
    nuevo->siguiente = this->_pri;
    if (this->longitud() == 0)
        this->_ult = nuevo;
    else
        this->_pri->anterior = nuevo;
    this->_pri = nuevo;
}

void Lista::agregarAtras(const int &elem) {
    Nodo *nuevo = new Nodo(elem);
    nuevo->anterior = this->_ult;
    if (this->longitud() == 0)
        this->_pri = nuevo;
    else
        this->_ult->siguiente = nuevo;
    this->_ult = nuevo;
}

void Lista::eliminar(Nat i) {
    Nodo *actual = this->_pri;
    for (int j = 0; j < i; j++)
        actual = actual->siguiente;
    if (actual->anterior == nullptr)
        this->_pri = actual->siguiente;
    else
        actual->anterior->siguiente = actual->siguiente;
    if (actual->siguiente == nullptr)
        this->_ult = actual->anterior;
    else
        actual->siguiente->anterior = actual->anterior;
    delete actual;
}

int Lista::longitud() const {
    int l = 0;
    Nodo *actual = this->_pri;
    while (actual != nullptr) {
        l++;
        actual = actual->siguiente;
    }
    return l;
}

const int &Lista::iesimo(Nat i) const {
    Nodo *actual = this->_pri;
    for (int j = 0; j < i; j++)
        actual = actual->siguiente;
    return actual->valor;
}

int &Lista::iesimo(Nat i) {
    Nodo *actual = this->_pri;
    for (int j = 0; j < i; j++)
        actual = actual->siguiente;
    return actual->valor;
}

void Lista::mostrar(ostream &o) {
    o << "[" << this->_pri;
    Nodo *actual = this->_pri->siguiente;
    while (actual != nullptr) {
        o << ", " << actual->valor;
        actual = actual->siguiente;
    }
    o << "]";
}
