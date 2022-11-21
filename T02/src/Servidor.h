#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "Tipos.h"
#include "Notificacion.h"
#include "Fachada_Variante.h"
#include "Juego.h"


class Servidor {
public:
    /**
     * El constructor de Servidor debe inicializar un nuevo servidor, y todas sus dependencias (como el juego,
     * la variante, el tablero, etc)
     *
     * Complejidad: O(tamanoTab**2 + TAMANIO_ALFABETO*cantJugadores + cantFichas*cantJugadores)
     */
    Servidor(
            Nat cantJugadores,
            const Variante &variante,
            const Repositorio &r
    );

    /**
     * Conecta un cliente al servidor y retorna su id de cliente
     *
     * Complejidad: O(1)
     */
    IdCliente conectarCliente();

    /**
     * Recibe un mensaje o del cliente id
     *
     * Complejidad: No se impone una cota explícita. La complejidad no debe depender de
     * N ni de K. Puede depender de |Σ|, F, Lmáx y del número de fichas que el jugador pretenda ubicar al
     * enviar este mensaje.
     */
    void recibirMensaje(IdCliente id, const Ocurrencia &o);

    /**
     * Retorna la cantidad de jugadores necesarios para poder empezar el juego
     *
     * Complejidad: O(1)
     */
    Nat jugadoresEsperados();

    /**
     * Retorna la cantidad de jugadores necesarios para poder empezar el juego
     *
     * Complejidad: O(1)
     */
    Nat jugadoresConectados();

    /**
     * Consulta y vacia la cola de notificaciones del cliente id
     *
     * Complejidad: O(n*F)
     *   donde n es la cantidad de mensajes sin consultar de dicho cliente
     *   y F es la cantidad de fichas por jugador de la variante.
     */
    list<Notificacion> notificaciones(IdCliente id);

    bool empezo();

private:
    Juego _juego;
    Nat _jugadoresConectados;
    Nat _jugadoresEsperados;
    vector<list<Notificacion>> _notificaciones;
    // Sirve para el constructor Reponer del tipo Notificación
    vector<multiset<Letra>> _mazos;
};

#endif // SERVIDOR_H;
