#include <iostream>
#include <list>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
            // ene, feb, mar, abr, may, jun
            31, 28, 31, 30, 31, 30,
            // jul, ago, sep, oct, nov, dic
            31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
public:
    Fecha(int mes, int dia);

    int mes() const;

    int dia() const;

    // Completar declaraciones funciones
#if EJ >= 9 // Para ejercicio 9

    bool operator==(Fecha o);

    bool operator<(const Fecha &o) const;

    void incrementar_dia();

#endif

private:
    //Completar miembros internos
    int _mes;
    int _dia;
};

Fecha::Fecha(int mes, int dia) : _mes(mes), _dia(dia) {};

int Fecha::mes() const {
    return _mes;
}

int Fecha::dia() const {
    return _dia;
}

ostream &operator<<(ostream &os, Fecha f) {
    os << f.dia() << "/" << f.mes();
    return os;
}

#if EJ >= 9

bool Fecha::operator==(Fecha o) {
    return _dia == o.dia() && _mes == o.mes();
}

bool Fecha::operator<(const Fecha &o) const {
    return this->mes() < o.mes() || this->dia() < o.dia();
}

void Fecha::incrementar_dia() {
    int diaSig = (_dia + 1) % (dias_en_mes(_mes) + 1);
    if (_dia > diaSig) {
        _mes++;
        _dia = 1;
    } else {
        _dia = diaSig;
    }
}

#endif

// Ejercicio 11, 12

// Clase Horario
class Horario {
public:
    Horario(uint hora, uint min);

    uint hora() const;

    uint min() const;

    bool operator==(Horario h);

    bool operator<(const Horario &h) const;

private:
    int _hora;
    int _min;
};

Horario::Horario(uint hora, uint min) : _hora(hora), _min(min) {};

uint Horario::hora() const {
    return _hora;
}

uint Horario::min() const {
    return _min;
}

ostream &operator<<(ostream &os, Horario f) {
    os << f.hora() << ":" << f.min();
    return os;
}

bool Horario::operator==(Horario h) {
    return _hora == h.hora() && _min == h.min();
}

bool Horario::operator<(const Horario &h) const {
    return _hora < h.hora() || _min < h.min();
}

// Ejercicio 13

// Clase Recordatorio
class Recordatorio {
public:
    Recordatorio(Fecha f, Horario h, string msj);

    Fecha fecha() const;

    Horario horario() const;

    string mensaje();

    bool operator<(const Recordatorio &r) const;

private:
    Fecha _f;
    Horario _h;
    string _msj;
};

Recordatorio::Recordatorio(Fecha f, Horario h, std::string msj) : _f(f), _h(h), _msj(msj) {};

Fecha Recordatorio::fecha() const {
    return _f;
}

Horario Recordatorio::horario() const {
    return _h;
}

string Recordatorio::mensaje() {
    return _msj;
}

ostream &operator<<(ostream &os, Recordatorio r) {
    os << r.mensaje() << " @ " << r.fecha() << " " << r.horario();
    return os;
}

bool Recordatorio::operator<(const Recordatorio &r) const {
    return this->fecha() < r.fecha() || this->horario() < r.horario();
}

// Ejercicio 14

// Clase Agenda
class Agenda {
public:
    Agenda(Fecha fecha_inicial);

    void agregar_recordatorio(Recordatorio rec);

    void incrementar_dia();

    list <Recordatorio> recordatorios_de_hoy();

    Fecha hoy();

private:
    Fecha _hoy;
    map<Fecha, list<Recordatorio>> _recs;
};

Agenda::Agenda(Fecha fecha_inicial) : _hoy(fecha_inicial) {};

void Agenda::agregar_recordatorio(Recordatorio rec) {
    _recs[rec.fecha()].push_back(rec);
    _recs[rec.fecha()].sort();
}

void Agenda::incrementar_dia() {
    _hoy.incrementar_dia();
}

list <Recordatorio> Agenda::recordatorios_de_hoy() {
    return _recs[_hoy];
}

Fecha Agenda::hoy() {
    return _hoy;
}

ostream &operator<<(ostream &os, Agenda a) {
    list <Recordatorio> hoy = a.recordatorios_de_hoy();
    os << a.hoy() << "\n=====\n";
    for (Recordatorio r: hoy) {
        os << r << "\n";
    }
    return os;
}