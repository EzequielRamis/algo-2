
template<class T>
Conjunto<T>::Conjunto(): _cardinal(0), _raiz(nullptr) {}

template<class T>
Conjunto<T>::~Conjunto() {
    // Completar
}

template<class T>
bool Conjunto<T>::pertenece(const T &clave) const {
    Nodo *n = irHastaValor(_raiz, clave);
    if (n == nullptr)
        return false;
    return n->valor == clave;
}

template<class T>
void Conjunto<T>::insertar(const T &clave) {
    Nodo *n = irHastaValor(_raiz, clave);
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
    Nodo *n = irHastaValor(_raiz, clave);
    if (n != nullptr && n->valor == clave) {
        Nodo *padre = n->padre;
        // Caso 0: n es la raíz
        if (padre == nullptr) {
            _raiz = nullptr;
            delete n;
        } else {
            // Caso 1: n es una hoja
            if (n->izq == nullptr && n->der == nullptr) {
                if (padre != nullptr) {
                    if (padre->izq == n)
                        padre->izq == nullptr;
                    else
                        padre->der == nullptr;
                }
                delete n;
            }
                // Caso 2: n tiene un hijo
            else if ((n->izq == nullptr) != (n->der == nullptr)) {
                if (n->izq != nullptr)
                    padre->izq = n->izq;
                else
                    padre->der = n->der;
                delete n;
            }
                // Caso 3: n tiene dos hijos
            else {
                Nodo *inmediato = siguienteNodo(clave);
                n->valor = inmediato->valor;
                n->padre = inmediato->padre;
                inmediato->padre->izq = n;
                delete inmediato;
            }
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

// Devuelve el nodo con ese valor o su padre si no está.
template<class T>
typename Conjunto<T>::Nodo *Conjunto<T>::irHastaValor(Conjunto::Nodo *n, const T &elem) const {
    if (n == nullptr || n->valor == elem)
        return n;
    if (n->valor < elem) {
        if (n->der == nullptr)
            return n;
        return irHastaValor(n->der, elem);
    } else {
        if (n->izq == nullptr)
            return n;
        return irHastaValor(n->izq, elem);
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
    Nodo *n = irHastaValor(_raiz, clave);
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

