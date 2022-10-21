#include "Diccionario.hpp"

template<class T>
class Multiconjunto {
public:
    Multiconjunto();

    void agregar(T x);

    int ocurrencias(T x) const;

    // Ejercicio 9
    bool operator<=(Multiconjunto<T> otro) const;

private:
    Diccionario<T, int> _mconj;
};

template<class T>
Multiconjunto<T>::Multiconjunto() {}

template<class T>
void Multiconjunto<T>::agregar(T x) {
    if (_mconj.def(x))
        _mconj.definir(x, _mconj.obtener(x) + 1);
    else
        _mconj.definir(x, 1);
    return;
}

template<class T>
int Multiconjunto<T>::ocurrencias(T x) const {
    if (_mconj.def(x))
        return _mconj.obtener(x);
    else return 0;
}

template<class T>
bool Multiconjunto<T>::operator<=(Multiconjunto<T> otro) const {
    for (T c: _mconj.claves())
        if (ocurrencias(c) > otro.ocurrencias(c))
            return false;
    return true;
}