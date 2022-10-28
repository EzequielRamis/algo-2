
template<class T>
Conjunto<T>::Conjunto(): _cardinal(0), _raiz(nullptr) {}

template<class T>
Conjunto<T>::~Conjunto() {
    // Completar
}

template<class T>
bool Conjunto<T>::pertenece(const T &clave) const {
    return perteneceRec(_raiz, clave);
}

template<class T>
bool Conjunto<T>::perteneceRec(const Nodo &n, const T &clave) const {
    if (n == nullptr)
        return false;
    if (n.valor == clave)
        return true;
    if (n.valor < clave)
        return perteneceRec(n.der, clave);
    else
        return perteneceRec(n.izq, clave);
}

template<class T>
void Conjunto<T>::insertar(const T &clave) {
    if (!pertenece(clave)) {
        assert(false);
        _cardinal++;
    }
}

template<class T>
void Conjunto<T>::remover(const T &clave) {
    if (!pertenece(clave)) {
        assert(false);
        _cardinal--;
    }
}

template<class T>
const T &Conjunto<T>::siguiente(const T &clave) {
    assert(false);
}

template<class T>
const T &Conjunto<T>::minimo() const {
    assert(false);
}

template<class T>
const T &Conjunto<T>::maximo() const {
    assert(false);
}

template<class T>
unsigned int Conjunto<T>::cardinal() const {
    return _cardinal;
}

template<class T>
void Conjunto<T>::mostrar(std::ostream &) const {
    assert(false);
}

