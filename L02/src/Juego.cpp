#include <utility>
#include <list>

using namespace std;

// Ejercicio 15

// Juego

using Pos = pair<int, int>;

const char ARRIBA = '^';
const char ABAJO = 'v';
const char DERECHA = '<';
const char IZQUIERDA = '>';

class Juego {
    // Completar
public:
    Juego(uint casilleros, Pos pos_inicial);

    Pos posicion_jugador();

    uint turno_actual();

    void mover_jugador(char dir);

    void ingerir_pocion(uint movimientos, uint turnos);

private:
    uint _turno;
    Pos _pos;
    uint _n;
    list <pair<uint, uint>> _pociones;

    uint _movimientos_extra;

    void aplicar_efectos();

    void diluir_efectos();
};

Juego::Juego(uint casilleros, Pos pos_inicial) : _n(casilleros), _pos(pos_inicial), _turno(0), _pociones({}),
                                                 _movimientos_extra(0) {};

Pos Juego::posicion_jugador() {
    return _pos;
}

uint Juego::turno_actual() {
    return _turno;
}

void Juego::ingerir_pocion(uint movimientos, uint turnos) {
    _pociones.push_back(make_pair(movimientos, turnos));
    _movimientos_extra += movimientos;
}

void Juego::aplicar_efectos() {
    int res = 0;
    for (auto p: _pociones)
        res += p.first;
    _movimientos_extra = res;
}

void Juego::diluir_efectos() {
    list <pair<uint, uint>> diluidos;
    for (auto p: _pociones)
        if (p.second > 1)
            diluidos.push_back(make_pair(p.first, p.second - 1));
    _pociones = diluidos;
}

void Juego::mover_jugador(char dir) {
    switch (dir) {
        case ARRIBA:
            _pos.first = max(0, _pos.first - 1);
            break;
        case ABAJO:
            _pos.first = min((int) _n, _pos.first + 1);
            break;
        case IZQUIERDA:
            _pos.second = max(0, _pos.second - 1);
            break;
        case DERECHA:
            _pos.second = min((int) _n, _pos.second + 1);
            break;
    }
    _movimientos_extra -= _movimientos_extra <= 0 ? 0 : 1;
    if (_movimientos_extra <= 0) {
        _turno++;
        diluir_efectos();
        aplicar_efectos();
    }
}