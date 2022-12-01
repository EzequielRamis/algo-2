#include "gtest-1.8.1/gtest.h"
#include "../src/Fachada_Servidor.h"

#include "utils/Repositorio.h"
#include "utils/Puntajes.h"
#include "utils/PalabrasComunes.h"
#include "utils/NotificacionesUtils.h"

class JuegoTrivialTest : public testing::Test {
protected:
    Nat cantJugadores = 4;
    Nat tamanoTab = 15;
    Nat cantFichas = 10;

    map<Letra, Nat> puntajes;
    set<vector<Letra> > palabrasLegitimas;
    Repositorio repo;

    Fachada_Variante variante;
    Fachada_Servidor fachada;

    JuegoTrivialTest() :
            puntajes(puntajesIngles),
            palabrasLegitimas({
                                      {'a'},
                                      {'a', 'a'},
                                      {'a', 'a', 'a'},
                                      {'a', 'a', 'a', 'a'},
                                      {'a', 'a', 'a', 'a', 'a'},
                                      {'b'},
                                      {'b', 'b'},
                                      {'b', 'b', 'b'},
                                      {'b', 'b', 'b', 'b'},
                                      {'b', 'b', 'b', 'b', 'b'},
                              }),
            repo(RepositorioGrande::repositorioAB()),
            variante(tamanoTab, cantFichas, puntajes, palabrasLegitimas),
            fachada(cantJugadores, variante, repo) {
        for (Nat i = 0; i < cantJugadores; i++) {
            fachada.conectarCliente();
        }
    }


};


TEST_F(JuegoTrivialTest, jugador_recibe_mal_ante_jugada_discontigua) {
    // limpiar notifs
    fachada.notificaciones(0);

    fachada.recibirMensaje(0, {{0, 0, 'a'},
                               {0, 2, 'a'}});

    compareNotificaciones(fachada.notificaciones(0), {
            Notificacion::nuevaMal()
    });
};

TEST_F(JuegoTrivialTest, jugador_recibe_mal_ante_jugada_diagonal) {
    // limpiar notifs
    fachada.notificaciones(0);

    fachada.recibirMensaje(0, {{0, 0, 'a'},
                               {1, 1, 'a'}});

    compareNotificaciones(fachada.notificaciones(0), {
            Notificacion::nuevaMal()
    });
};

TEST_F(JuegoTrivialTest, jugador_recibe_mal_ante_jugada_ilegitima) {
    /*
     * A B B
     * A
     * A
     */
    fachada.recibirMensaje(0, {{0, 0, 'a'},
                               {0, 1, 'a'},
                               {0, 2, 'a'}});

    // limpiar notifs
    fachada.notificaciones(1);

    Ocurrencia o = {{1, 0, 'b'},
                    {2, 0, 'b'}};
    fachada.recibirMensaje(1, o);

    compareNotificaciones(fachada.notificaciones(1), {
            Notificacion::nuevaMal()
    });
};

TEST_F(JuegoTrivialTest, jugadores_reciben_mal_ante_jugadas_ilegitimas) {
    /*
     * A B B
     * A
     * A
     */
    fachada.recibirMensaje(0, {{0, 0, 'a'},
                               {0, 1, 'a'},
                               {0, 2, 'a'}});

    // limpiar notifs
    fachada.notificaciones(1);
    fachada.notificaciones(2);

    Ocurrencia o = {{1, 0, 'b'},
                    {2, 0, 'b'}};
    fachada.recibirMensaje(1, o);
    fachada.recibirMensaje(2, o);

    compareNotificaciones(fachada.notificaciones(1), {
            Notificacion::nuevaMal()
    });
    compareNotificaciones(fachada.notificaciones(2), {
            Notificacion::nuevaMal()
    });
};

TEST_F(JuegoTrivialTest, jugador_recibe_mal_ante_jugada_ilegitima_sin_limpiar) {
    /*
     * A B B
     * A
     * A
     */
    fachada.recibirMensaje(0, {{0, 0, 'a'},
                               {0, 1, 'a'},
                               {0, 2, 'a'}});

    Ocurrencia o = {{1, 0, 'b'},
                    {2, 0, 'b'}};
    fachada.recibirMensaje(1, o);

    compareNotificaciones(fachada.notificaciones(1), {
            Notificacion::nuevaIdCliente(1),
            Notificacion::nuevaEmpezar(this->tamanoTab),
            Notificacion::nuevaTurnoDe(0),
            Notificacion::nuevaReponer({'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b'}),
            Notificacion::nuevaUbicar(0, {{0, 0, 'a'},
                                          {0, 1, 'a'},
                                          {0, 2, 'a'}}),
            Notificacion::nuevaSumaPuntos(0, 6),
            Notificacion::nuevaTurnoDe(1),
            Notificacion::nuevaMal()
    });
};
