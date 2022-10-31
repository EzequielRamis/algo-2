
template<class T>
Conjunto<T>::Conjunto(): _cardinal(0), _raiz(nullptr) {}

template<class T>
Conjunto<T>::~Conjunto() {
    borrarNodos(_raiz);
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
        Nodo *nuevo = new Nodo(clave);
        nuevo->padre = n;
        if (n->valor < clave)
            n->der = nuevo;
        else
            n->izq = nuevo;
        _cardinal++;
    }
}

template<class T>
void Conjunto<T>::remover(const T &clave) {
    Nodo *n = irANodo(_raiz, clave);
    if (n != nullptr && n->valor == clave) {
        if (n->izq == nullptr)
            moverNodo(n, n->der);
        else if (n->der == nullptr)
            moverNodo(n, n->izq);
        else {
            Nodo *inmediato = siguienteNodo(clave);
            if (inmediato->padre != n) {
                moverNodo(inmediato, inmediato->der);
                inmediato->der = n->der;
                inmediato->der->padre = inmediato;
            }
            moverNodo(n, inmediato);
            inmediato->izq = n->izq;
            inmediato->izq->padre = inmediato;
        }
        delete n;
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
void Conjunto<T>::moverNodo(Conjunto::Nodo *u, Conjunto::Nodo *v) {
    if (u->padre == nullptr)
        _raiz = v;
    else if (u == u->padre->izq)
        u->padre->izq = v;
    else
        u->padre->der = v;
    if (v != nullptr)
        v->padre = u->padre;
}

template<class T>
void Conjunto<T>::borrarNodos(Conjunto::Nodo *ab) {
    if (ab != nullptr) {
        if (ab->izq != nullptr)
            borrarNodos(ab->izq);
        if (ab->der != nullptr)
            borrarNodos(ab->der);
        delete ab;
    }
}

template<class T>
void Conjunto<T>::mostrar(std::ostream &os) const {
    os << "{";
    mostrarDesde(os, _raiz);
    os << "}";
}

template<class T>
void Conjunto<T>::mostrarDesde(std::ostream &os, Conjunto::Nodo *n) const {
    if (n != nullptr) {
        if (n->izq != nullptr) {
            mostrarDesde(os, n->izq);
            os << ", ";
        }
        os << n->valor;
        if (n->der != nullptr) {
            os << ", ";
            mostrarDesde(os, n->der);
        }
    }
}
