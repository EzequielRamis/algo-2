#include "Juego.h"
#include "Letra.h"

Juego::Juego(Nat k, const Variante &v, const Repositorio &r) :
        _tablero(
                vector<vector<pair<Letra, Nat> *>>(v.tamanoTablero(),
                                                   vector<pair<Letra, Nat> *>(v.tamanoTablero(), nullptr))
        ),
        _variante(v),
        _repositorio(r),
        _tiempo(0),
        _jugadores(vector<Jugador>(k, Jugador())) {
    for (int j = 0; j < k; j++)
        for (int i = 0; i < v.fichas(); i++) {
            auto ficha = *_repositorio.rbegin();
            _repositorio.pop_back();
            _jugadores[j].cantFichasPorLetra[ord(ficha)]++;
        }
}

Juego::Jugador::Jugador() :
        puntaje(0),
        jugadasSinCalcularPuntaje(0),
        cantFichasPorLetra(vector<Nat>(TAMANIO_ALFABETO, 0)),
        historial(list<pair<Ocurrencia, Nat>>()) {}

void Juego::ubicar(const Ocurrencia &o) {
    Jugador &j = _jugadores[turno()];
    ponerLetras(o);
    for (auto ficha: o) {
        j.cantFichasPorLetra[ord(get<2>(ficha))]--;
        auto nuevaFicha = *_repositorio.rbegin();
        _repositorio.pop_back();
        j.cantFichasPorLetra[ord(nuevaFicha)]++;
    }
    if (!o.empty()) {
        j.historial.push_back(make_pair(o, _tiempo));
        j.jugadasSinCalcularPuntaje++;
    }
    _tiempo++;
}

IdCliente Juego::turno() {
    return _tiempo % _jugadores.size();
}

const Variante &Juego::variante() {
    return _variante;
}

bool Juego::jugadaValida(const Ocurrencia &o) {
    if (o.size() > _variante.longPalabraMasLarga())
        return false;
    for (auto ficha: o)
        if (!enTablero(get<0>(ficha), get<1>(ficha))
            || hayLetra(get<0>(ficha), get<1>(ficha)))
            return false;

    bool horizontal = esHorizontal(o);

    if (haySuperpuestas(o) || !(horizontal || esVertical(o)))
        return false;
    ponerLetras(o);
    auto cualquierFicha = *o.begin();
    pair<Nat, Nat> rango = rangoDePalabra(cualquierFicha, horizontal);
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
        pair<Nat, Nat> rango = rangoDePalabra(cualquierFicha, !horizontal);
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
    for (auto ficha: o)
        _tablero[get<0>(ficha)][get<1>(ficha)] = new pair<Letra, Nat>{get<2>(ficha), _tiempo};
}

void Juego::sacarLetras(const Ocurrencia &o) {
    for (auto ficha: o) {
        delete _tablero[get<0>(ficha)][get<1>(ficha)];
        _tablero[get<0>(ficha)][get<1>(ficha)] = nullptr;
    }
}

pair<Nat, Nat> Juego::rangoDePalabra(const tuple<Nat, Nat, Letra> &ficha, bool horizontal) {
    Nat linea = horizontal ? get<0>(ficha) : get<1>(ficha);
    Nat i = horizontal ? get<1>(ficha) : get<0>(ficha);
    Nat j = i;
    if (horizontal) {
        while (enTablero(linea, i) && hayLetra(linea, i))
            i--;
        while (enTablero(linea, j) && hayLetra(linea, j))
            j++;
    } else {
        while (enTablero(i, linea) && hayLetra(i, linea))
            i--;
        while (enTablero(j, linea) && hayLetra(j, linea))
            j++;
    }
    return make_pair(i, j);
}

bool Juego::formaPalabraLegitima(const pair<Nat, Nat> &r, bool horizontal, Nat padding) {
    Nat i = r.first;
    Nat j = r.second;
    Palabra palabra(j - i);
    for (int k = i; k <= j; k++)
        palabra[k] = horizontal ? ficha(padding, k) : ficha(k, padding);
    return _variante.palabraLegitima(palabra);
}

Nat Juego::tiempo() const {
    return _tiempo;
}
Repositorio Juego::repositorio() const {
    return _repositorio;
}
Nat Juego::consultarPuntaje(IdCliente id) const {
    return _jugadores[id].puntaje;
}

Nat Juego::puntaje(IdCliente id) {
    Jugador *jugador = &_jugadores[id];
    Nat *k = &jugador->jugadasSinCalcularPuntaje;
    auto histIt = jugador->historial.rbegin();
    while (*k > 0) {
        pair<Ocurrencia, Nat> jugada = *histIt;
        auto ocIt = jugada.first.begin();
        bool esHorizontal = true;
        tuple<Nat, Nat, Letra> ficha = *ocIt;
        ocIt++;
        if (ocIt != jugada.first.end())
            esHorizontal = get<0>(ficha) = get<0>(*ocIt);
        sumarPuntaje(*jugador, ficha, jugada.second, true, esHorizontal);
        for (auto fichaSecundaria: jugada.first)
            sumarPuntaje(*jugador, fichaSecundaria, jugada.second, false, !esHorizontal);
        histIt--;
        *k = *k - 1;
    }
    return jugador->puntaje;
}

void
Juego::sumarPuntaje(Jugador &jugador,
                    tuple<Nat, Nat, Letra> &ficha,
                    Nat tiempo,
                    bool esPrincipal,
                    bool esHorizontal) {
    Nat linea = esHorizontal ? get<0>(ficha) : get<1>(ficha);
    Nat i = esHorizontal ? get<1>(ficha) : get<0>(ficha) - (esPrincipal ? 0 : 1);
    Nat j = i + 1;
    sumarPuntajeEnDir(jugador, ficha, tiempo, linea, i, false, esHorizontal);
    sumarPuntajeEnDir(jugador, ficha, tiempo, linea, j, true, esHorizontal);
}

void Juego::sumarPuntajeEnDir(Jugador &jugador,
                              tuple<Nat, Nat, Letra> &ficha,
                              Nat tiempo,
                              Nat pos,
                              Nat desde,
                              bool adelante,
                              bool esHorizontal) {
    while (enTablero(pos, desde) &&
           hayLetra(pos, desde) &&
           fichaTiempo(pos, desde) <= tiempo) {
        if (esHorizontal)
            jugador.puntaje += _variante.puntajeLetra(this->ficha(pos, desde));
        else
            jugador.puntaje += _variante.puntajeLetra(this->ficha(desde, pos));
        if (adelante)
            desde++;
        else
            desde--;
    }
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

Nat Juego::fichaTiempo(Nat i, Nat j) {
    return _tablero[i][j]->second;
}

Nat Juego::cantLetrasTieneJugador(Letra x, Nat i) {
    return _jugadores[i].cantFichasPorLetra[ord(x)];
}

bool Juego::haySuperpuestas(const Ocurrencia &o) const{
    vector<set<Nat>> ocurrencias = vector<set<Nat>>(_variante.tamanoTablero());
    for (auto ficha : o) {
        set<Nat> fila = ocurrencias[(get<0>(ficha))];
        if (fila.find(get<1>(ficha)) != fila.end()) {
            return true;
        }
        ocurrencias[get<0>(ficha)].insert(get<1>(ficha));
    }
    return false;
}

//Chequeamos que todos los primeros elementos de la tupla "o" sean iguales
bool Juego::esHorizontal(const Ocurrencia &o) const{
    auto itr = o.begin();
    Nat fila = get<0>(*itr);
    itr++;
    while (itr != o.end()){
        if (get<0>(*itr) != fila) {
            return false;
        }
        itr++;
    }
    return true;
}

//Chequeamos que todos los segundos elementos de la tupla "o" sean iguales
bool Juego::esVertical(const Ocurrencia &o) const{
    auto itr = o.begin();
    Nat col = get<1>(*itr);
    itr++;
    while (itr != o.end()){
        if (get<1>(*itr) != col) {
            return false;
        }
        itr++;
    }
    return true;
}
