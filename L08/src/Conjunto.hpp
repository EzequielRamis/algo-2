
template<class T>
Conjunto<T>::Conjunto(): _cardinal(0), _raiz(nullptr) {}

template<class T>
Conjunto<T>::~Conjunto() {
    // Completar
}

template<class T>
bool Conjunto<T>::pertenece(const T &clave) const {
    Nodo *n = irANodo(_raiz, clave);
    if (n == nullptr)
        return false;
    return n->valor == clave;
}

template<class T>
void Conjunto<T>::insertar(const T &clave) {
    Nodo *n = irANodo(_raiz, clave);
    if (n == nullptr) {
        _raiz = new Nodo(clave);
        _cardinal++;
    } else if (n->valor != clave) {
        if (n->valor < clave) {
            n->der = new Nodo(clave);
            n->der->padre = n;
        } else {
            n->izq = new Nodo(clave);
            n->izq->padre = n;
        }
        _cardinal++;
    }
}

template<class T>
void Conjunto<T>::remover(const T &clave) {
    Nodo *n = irANodo(_raiz, clave);
    if (n != nullptr && n->valor == clave) {
        Nodo *padre = n->padre;
        // Caso 1: n es una hoja
        if (n->izq == nullptr && n->der == nullptr) {
            if (padre != nullptr) {
                if (padre->izq == n)
                    padre->izq == nullptr;
                else
                    padre->der == nullptr;
            } else
                _raiz = nullptr;
            delete n;
        }
            // Caso 2: n tiene un hijo
        else if ((n->izq == nullptr) != (n->der == nullptr)) {
            if (padre != nullptr) {
                if (n->izq != nullptr) {
                    n->izq->padre = padre;
                    if (padre->izq == n)
                        padre->izq = n->izq;
                    else
                        padre->der = n->izq;
                } else {
                    n->der->padre = padre;
                    if (padre->izq == n)
                        padre->izq = n->der;
                    else
                        padre->der = n->der;
                }
            } else {
                if (n->izq != nullptr) {
                    _raiz = n->izq;
                    n->izq->padre = nullptr;
                } else {
                    _raiz = n->der;
                    n->der->padre = nullptr;
                }
            }
            delete n;
        }
            // Caso 3: n tiene dos hijos
        else {
            Nodo *inmediato = siguienteNodo(clave);
            n->valor = inmediato->valor;
            /*// Caso 3.1: el inmediato es hoja
            if (inmediato->der == nullptr) {
                if (inmediato->padre == n) {
                    n->der = nullptr;
                } else {
                    inmediato->padre->izq = nullptr;
                }
            }
                // Caso 3.2: el inmediato tiene una hoja (derecha)
            else {
                if (inmediato->padre == n) {
                    n->der = inmediato->der;
                    inmediato->der->padre = n;
                } else {
                    inmediato->padre->izq = inmediato->der;
                    inmediato->der->padre = inmediato->padre;
                }
            }
            delete inmediato;*/
            /*Nodo *inmediatoPadre = inmediato->padre;
            // Caso 3.1: inmediato es una hoja
            if (inmediato->der == nullptr) {
                if (inmediatoPadre != nullptr) {
                    if (inmediatoPadre->izq == inmediato)
                        inmediatoPadre->izq == nullptr;
                    else
                        inmediatoPadre->der == nullptr;
                } else {
                    _raiz = n;
                    n->padre = nullptr;
                }

            }
                // Caso 3.2: inmediato tiene un hijo (derecho)
            else {
                if (inmediatoPadre != nullptr) {
                    inmediato->der->padre = inmediatoPadre;
                    if (inmediatoPadre->izq == inmediato)
                        inmediatoPadre->izq = inmediato->der;
                    else
                        inmediatoPadre->der = inmediato->der;
                } else {
                    _raiz = inmediato->der;
                    inmediato->der->padre = nullptr;
                    n->padre = inmediato->der;
                }
            }*/
            if (inmediato->padre != n) {
                inmediato->padre->izq = inmediato->der;
                if (inmediato->der != nullptr)
                    inmediato->der->padre = inmediato->padre;
            } else {
                n->der = inmediato->der;
            }
            delete inmediato;
        }
        _cardinal--;
    }
}

template<class T>
const T &Conjunto<T>::siguiente(const T &clave) {
    return siguienteNodo(clave)->valor;
}

template<class T>
const T &Conjunto<T>::minimo() const {
    return minimoDesde(_raiz)->valor;
}

template<class T>
const T &Conjunto<T>::maximo() const {
    return maximoDesde(_raiz)->valor;
}

template<class T>
unsigned int Conjunto<T>::cardinal() const {
    return _cardinal;
}

template<class T>
typename Conjunto<T>::Nodo *Conjunto<T>::irANodo(Conjunto::Nodo *n, const T &elem) const {
    if (n == nullptr || n->valor == elem)
        return n;
    if (n->valor < elem) {
        if (n->der == nullptr)
            return n;
        return irANodo(n->der, elem);
    } else {
        if (n->izq == nullptr)
            return n;
        return irANodo(n->izq, elem);
    }
}

template<class T>
typename Conjunto<T>::Nodo *Conjunto<T>::minimoDesde(Conjunto::Nodo *n) const {
    while (n->izq != nullptr)
        n = n->izq;
    return n;
}

template<class T>
typename Conjunto<T>::Nodo *Conjunto<T>::maximoDesde(Conjunto::Nodo *n) const {
    while (n->der != nullptr)
        n = n->der;
    return n;
}

template<class T>
typename Conjunto<T>::Nodo *Conjunto<T>::siguienteNodo(const T &clave) {
    Nodo *n = irANodo(_raiz, clave);
    if (n->der != nullptr)
        return minimoDesde(n->der);
    Nodo *m = n->padre;
    while (m != nullptr && n == m->der) {
        n = m;
        m = m->padre;
    }
    return m;
}

template<class T>
void Conjunto<T>::mostrar(std::ostream &) const {
    assert(false);
}

