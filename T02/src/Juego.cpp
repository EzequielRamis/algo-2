#include "Juego.h"
#include "Letra.h"

Juego::Juego(Nat k, const Variante &v, const Repositorio &r) :
        _tablero(
                v.tamanoTablero(),
                vector<pair<Letra, Nat> *>(v.tamanoTablero(), nullptr)
        ),
        _variante(v),
        _repositorio(r),
        _tiempo(0),
        _jugadores(k, Jugador()) {
    for (int j = 0; j < k; j++)
        for (int i = 0; i < v.fichas(); i++) {
            auto ficha = *_repositorio.begin();
            _repositorio.pop_front();
            _jugadores[j].cantFichasPorLetra[ord(ficha)]++;
        }
}

Juego::~Juego() {
    for (const auto &col: _tablero)
        for (auto ficha: col)
            delete ficha;
}

Juego::Jugador::Jugador() :
        puntaje(0),
        jugadasSinCalcularPuntaje(0),
        cantFichasPorLetra(TAMANIO_ALFABETO, 0) {}

multiset<Letra> Juego::ubicar(const Ocurrencia &o) {
    multiset<Letra> letrasRespuestas;
    Jugador &j = _jugadores[turno()];
    ponerLetras(o);
    for (auto ficha: o) {
        j.cantFichasPorLetra[ord(get<2>(ficha))]--;
        auto nuevaFicha = *_repositorio.begin();
        _repositorio.pop_front();
        j.cantFichasPorLetra[ord(nuevaFicha)]++;
        letrasRespuestas.insert(nuevaFicha);
    }
    if (!o.empty()) {
        j.historial.push_back(make_pair(o, _tiempo));
        j.jugadasSinCalcularPuntaje++;
    }
    _tiempo++;
    return letrasRespuestas;
}

IdCliente Juego::turno() {
    return _tiempo % _jugadores.size();
}

const Variante &Juego::variante() {
    return _variante;
}

bool Juego::jugadaValida(const Ocurrencia &o) {
    if (o.empty())
        return true;
    if (o.size() > _variante.longPalabraMasLarga())
        return false;
    for (auto ficha: o) {
        if (!enTablero(get<0>(ficha), get<1>(ficha))
            || hayLetra(get<0>(ficha), get<1>(ficha)))
            return false;

        if (_jugadores[turno()].cantFichasPorLetra[ord(get<2>(ficha))] == 0)
            return false;
        else
            _jugadores[turno()].cantFichasPorLetra[ord(get<2>(ficha))]--;

    }
    for (auto ficha: o)
        _jugadores[turno()].cantFichasPorLetra[ord(get<2>(ficha))]++;
    bool horizontal = esHorizontal(o);

    if (haySuperpuestas(o) || !(horizontal || esVertical(o)))
        return false;
    ponerLetras(o);
    auto cualquierFicha = *o.begin();
    pair<Nat, Nat> rango = rangoDePalabra(cualquierFicha, horizontal, _tiempo + 1);
    for (auto ficha: o)
        if (!(rango.first <= get<1>(ficha) && get<1>(ficha) <= rango.second)) {
            sacarLetras(o);
            return false;
        }
    if (!formaPalabraLegitima(rango, horizontal, horizontal ?
                                                 get<0>(cualquierFicha) :
                                                 get<1>(cualquierFicha))) {
        sacarLetras(o);
        return false;
    }

    for (auto ficha: o) {
        pair<Nat, Nat> rango = rangoDePalabra(cualquierFicha, !horizontal, _tiempo + 1);
        if (rango.first != rango.second &&
            !formaPalabraLegitima(rango, !horizontal, horizontal ?
                                                      get<1>(cualquierFicha) :
                                                      get<0>(cualquierFicha))) {
            sacarLetras(o);
            return false;
        }
    }
    sacarLetras(o);
    return true;
}

void Juego::ponerLetras(const Ocurrencia &o) {
    for (auto &ficha: o) {
        Letra letra = get<2>(ficha);
        pair<Letra, Nat> ubicado(letra, _tiempo);
        _tablero[get<0>(ficha)][get<1>(ficha)] = new pair<Letra, Nat>(ubicado);
    }
}

void Juego::sacarLetras(const Ocurrencia &o) {
    for (auto &ficha: o) {
        delete _tablero[get<0>(ficha)][get<1>(ficha)];
        _tablero[get<0>(ficha)][get<1>(ficha)] = nullptr;
    }
}

pair<Nat, Nat> Juego::rangoDePalabra(const tuple<Nat, Nat, Letra> &ficha, bool horizontal, Nat antesDeTiempo) {
    Nat linea = horizontal ? get<0>(ficha) : get<1>(ficha);
    Nat i = horizontal ? get<1>(ficha) : get<0>(ficha);
    Nat j = i;
    // Muy bueno, los invito a pensar como deshacerse del if (obviamente no necesario para la aprobacion)
    if (horizontal) {
        while (enTablero(linea, i - 1)
               && hayLetra(linea, i - 1)
               && _tablero[linea][i - 1]->second <= antesDeTiempo)
            i--;
        while (enTablero(linea, j + 1)
               && hayLetra(linea, j + 1)
               && _tablero[linea][j + 1]->second <= antesDeTiempo)
            j++;
    } else {
        while (enTablero(i - 1, linea)
               && hayLetra(i - 1, linea)
               && _tablero[i - 1][linea]->second <= antesDeTiempo)
            i--;
        while (enTablero(j + 1, linea)
               && hayLetra(j + 1, linea)
               && _tablero[j + 1][linea]->second <= antesDeTiempo)
            j++;
    }
    return make_pair(i, j);
}

bool Juego::formaPalabraLegitima(const pair<Nat, Nat> &r, bool horizontal, Nat padding) {
    Nat i = r.first;
    Nat j = r.second;
    Palabra palabra;
    for (Nat k = i; k <= j; k++) {
        Letra letra = horizontal ? ficha(padding, k) : ficha(k, padding);
        palabra.push_back(letra);
    }
    return _variante.palabraLegitima(palabra);
}

const Repositorio &Juego::repositorio() const {
    return _repositorio;
}

Nat Juego::puntaje(IdCliente id) {
    Nat k = _jugadores[id].jugadasSinCalcularPuntaje;
    auto histIt = _jugadores[id].historial.rbegin();
    while (k > 0) {
        pair<Ocurrencia, Nat> jugada = *histIt;
        Nat puntos = calcularPuntaje(jugada);
        _jugadores[id].puntaje += puntos;
        histIt++;
        k -= 1;
    }
    return _jugadores[id].puntaje;
}

Nat Juego::calcularPuntaje(const pair<Ocurrencia, Nat> &jugada) {
    Nat puntos = 0;
    auto ocurrencia = jugada.first;
    if (ocurrencia.empty())
        return puntos;
    bool horizontal = esHorizontal(ocurrencia);
    auto itr = ocurrencia.begin();
    auto cualquierFicha = *itr;
    while (itr != ocurrencia.end()) {
        puntos += calcularPuntajeEnRango(jugada, *itr, !horizontal);
        itr++;
    }
    puntos += calcularPuntajeEnRango(jugada, cualquierFicha, horizontal);
    return puntos;
}

Nat Juego::calcularPuntajeEnRango(const pair<Ocurrencia, Nat> &jugada,
                                  const tuple<Nat, Nat, Letra> &desdeFicha,
                                  bool horizontal) {
    Nat puntos = 0;
    auto rango = rangoDePalabra(desdeFicha, horizontal, jugada.second);
    for (Nat i = rango.first; i <= rango.second; i++)
        if (horizontal) {
            Nat linea = get<0>(desdeFicha);
            puntos += _variante.puntajeLetra(_tablero[linea][i]->first);
        } else {
            Nat linea = get<1>(desdeFicha);
            puntos += _variante.puntajeLetra(_tablero[i][linea]->first);
        }
    return puntos;
}

bool Juego::enTablero(Nat i, Nat j) {
    return i < _variante.tamanoTablero() && j < _variante.tamanoTablero();
}

bool Juego::hayLetra(Nat i, Nat j) {
    return _tablero[i][j] != nullptr;
}

Letra Juego::ficha(Nat i, Nat j) {
    return _tablero[i][j]->first;
}

Nat Juego::cantLetrasTieneJugador(Letra x, Nat i) {
    return _jugadores[i].cantFichasPorLetra[ord(x)];
}

bool Juego::haySuperpuestas(const Ocurrencia &o) const {
    vector<set<Nat>> ocurrencias = vector<set<Nat>>(_variante.tamanoTablero());
    for (auto ficha: o) {
        set<Nat> fila = ocurrencias[(get<0>(ficha))];
        if (fila.find(get<1>(ficha)) != fila.end())
            return true;
        ocurrencias[get<0>(ficha)].insert(get<1>(ficha));
    }
    return false;
}

//Chequeamos que todos los primeros elementos de la tupla "o" sean iguales
bool Juego::esHorizontal(const Ocurrencia &o) {
    return estaAlineada(o, true);
}

//Chequeamos que todos los segundos elementos de la tupla "o" sean iguales
bool Juego::esVertical(const Ocurrencia &o) {
    return estaAlineada(o, false);
}

bool Juego::estaAlineada(const Ocurrencia &o, bool horizontalmente) {
    auto itr = o.begin();
    Nat linea = horizontalmente ? get<0>(*itr) : get<1>(*itr);
    itr++;
    while (itr != o.end()) {
        Nat linea2 = horizontalmente ? get<0>(*itr) : get<1>(*itr);
        if (linea != linea2)
            return false;
        itr++;
    }
    return true;
}

// Me parece rara esta funcion, despues reviso su uso
multiset<Letra> Juego::mazoDeJugador(Nat i) {
    multiset<Letra> res;
    for (int l = 0; l < (int) _jugadores[i].cantFichasPorLetra.size(); l++) {
        Nat cant = _jugadores[i].cantFichasPorLetra[l];
        while (cant > 0) {
            res.insert(inversaDeOrd(l));
            cant--;
        }
    }
    return res;
}