#ifndef ALGO2_LABO_CLASE5_ALGORITMOS_H
#define ALGO2_LABO_CLASE5_ALGORITMOS_H

#include <utility>
#include <iterator>
#include <vector>

// Completar con las funciones del enunciado
// Ej 1
template<class Contenedor>
typename Contenedor::value_type minimo(const Contenedor &c) {
    auto min = c.begin();
    auto it = c.begin();
    while (it != c.end()) {
        if (*it < *min)
            min = it;
        it++;
    }
    return *min;
}

// Ej 2
template<class Contenedor>
typename Contenedor::value_type promedio(const Contenedor &c) {
    typename Contenedor::value_type sum = 0;
    typename Contenedor::value_type cant = 0;
    auto it = c.begin();
    while (it != c.end()) {
        sum += *it;
        cant++;
        it++;
    }
    return sum / cant;
}

// Ej 3
template<class Iterator>
typename Iterator::value_type minimoIter(const Iterator &desde, const Iterator &hasta) {
    auto min = desde;
    auto it = desde;
    while (it != hasta) {
        if (*it < *min)
            min = it;
        it++;
    }
    return *min;
}

template<class Iterator>
typename Iterator::value_type promedioIter(const Iterator &desde, const Iterator &hasta) {
    typename Iterator::value_type sum = 0;
    typename Iterator::value_type cant = 0;
    auto it = desde;
    while (it != hasta) {
        sum += *it;
        cant++;
        it++;
    }
    return sum / cant;
}

// Ej 4
template<class Contenedor>
void filtrar(Contenedor &c, const typename Contenedor::value_type &elem) {
    auto it = c.begin();
    while (it != c.end()) {
        if (*it == elem)
            it = c.erase(it);
        else
            it++;
    }
}

// Ej 5
template<class Contenedor>
bool ordenado(Contenedor &c) {
    auto fst = c.begin();
    auto snd = c.begin();
    snd++;
    while (snd != c.end()) {
        if (*fst > *snd)
            return false;
        fst++;
        snd++;
    }
    return true;
}

// Ej 6
template<class Contenedor>
std::pair<Contenedor, Contenedor> split(const Contenedor &c,
                                        const typename Contenedor::value_type &elem) {
    Contenedor *less = new Contenedor();
    Contenedor *greater = new Contenedor();
    auto lit = less->begin();
    auto git = greater->begin();
    auto it = c.begin();
    while (it != c.end()) {
        if (*it < elem) {
            lit = less->insert(lit, *it);
            lit++;
        } else {
            git = greater->insert(git, *it);
            git++;
        }
        it++;
    }
    return std::make_pair(*less, *greater);
}

// Ej 7
template<class Contenedor>
void merge(const Contenedor &c1, const Contenedor &c2, Contenedor &res) {
    auto it1 = c1.begin();
    auto it2 = c2.begin();
    auto itr = res.end();
    while (it1 != c1.end() && it2 != c2.end()) {
        if (*it1 < *it2) {
            itr = res.insert(itr, *it1);
            it1++;
        } else {
            itr = res.insert(itr, *it2);
            it2++;
        }
        itr++;
    }
    while (it1 != c1.end()) {
        itr = res.insert(itr, *it1);
        itr++;
        it1++;
    }
    while (it2 != c2.end()) {
        itr = res.insert(itr, *it2);
        itr++;
        it2++;
    }
}

// Ej 8
// Igual al Ej 1

#endif //ALGO2_LABO_CLASE5_ALGORITMOS_H
