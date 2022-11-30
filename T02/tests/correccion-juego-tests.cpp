#include "gtest-1.8.1/gtest.h"
#include "../src/Fachada_Juego.h"

#include "utils/PalabrasComunes.h"

class CorreccionJuegoTests : public testing::Test {
protected:
    Nat tamanoTab = 10;
    Nat cantFichas = 3;

    map<Letra, Nat> puntajes;
    set<vector<Letra>> palabrasLegitimas;
    Repositorio repo;

    void SetUp() {
        puntajes = {{'a', 1},
                    {'q', 0},
                    {'x', 20},
                    {'z', 20}};

        palabrasLegitimas = set<vector<Letra>>(begin(palabrasComunes), end(palabrasComunes));
        repo = {'s', 'a', 'n', 's', 'e', 'r', 'l', 'r', 'e', 's', 'a', 'n', 's', 'e', 'r', 'l', 'r', 'e'};
    }
};

TEST_F(CorreccionJuegoTests, no_calcula_palabras_transversales) {
    Fachada_Variante v(tamanoTab, cantFichas, puntajes, palabrasLegitimas);

    Fachada_Juego juego(3, v, repo);

    EXPECT_TRUE(juego.jugadaValida({{0, 0, 's'},
                                    {0, 1, 'a'},
                                    {0, 2, 'n'}}));
    juego.ubicar({{0, 0, 's'},
                  {0, 1, 'a'},
                  {0, 2, 'n'}});
    EXPECT_EQ(6, juego.puntaje(0));

    EXPECT_TRUE(juego.jugadaValida({{1, 0, 'e'},
                                    {2, 0, 'r'}}));

    juego.ubicar({{1, 0, 'e'},
                  {2, 0, 'r'}});
    EXPECT_EQ(5, juego.puntaje(1));

    EXPECT_TRUE(juego.jugadaValida({{1, 1, 'l'}}));

    juego.ubicar({{1, 1, 'l'}});

    EXPECT_EQ(4, juego.puntaje(2));
};

TEST_F(CorreccionJuegoTests, no_funciona_con_muchos_ubicar_seguidos) {
    Fachada_Variante v(tamanoTab, cantFichas, puntajes, palabrasLegitimas);

    Fachada_Juego juego(2, v, repo);

    EXPECT_TRUE(juego.jugadaValida({{0, 0, 's'},
                                    {0, 1, 'a'},
                                    {0, 2, 'n'}}));
    juego.ubicar({{0, 0, 's'},
                  {0, 1, 'a'},
                  {0, 2, 'n'}});

    EXPECT_TRUE(juego.jugadaValida({{1, 0, 'e'},
                                    {2, 0, 'r'}}));

    juego.ubicar({{1, 0, 'e'},
                  {2, 0, 'r'}});
    EXPECT_EQ(5, juego.puntaje(1));

    EXPECT_TRUE(juego.jugadaValida({{1, 1, 'l'}}));

    juego.ubicar({{1, 1, 'l'}});

    EXPECT_EQ(10, juego.puntaje(0));
};


TEST_F(CorreccionJuegoTests, jugada_invalida_no_tiene_fichas) {
    Fachada_Variante v(tamanoTab, cantFichas, puntajes, palabrasLegitimas);

    Fachada_Juego juego(2, v, repo);

    EXPECT_FALSE(juego.jugadaValida({{0, 0, 'a'},
                                     {0, 1, 'n'},
                                     {0, 2, 'a'}}));
};