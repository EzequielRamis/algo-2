#include "gtest-1.8.1/gtest.h"
#include "../src/Libreta.h"
#include "../src/Truco.h"
#include <map>
#include <cmath>

using namespace std;

// Ejercicio 4
TEST(Aritmetica, suma) {
    EXPECT_EQ(15 + 7, 22);
}

// Ejercicio 5
TEST(Aritmetica, potencia) {
    EXPECT_EQ(pow(10, 2), 100);
}

// Ejercicios 6..9
TEST(Aritmetica, potencia_general) {
    EXPECT_EQ(pow(-5, 2), -5 * -5);
    EXPECT_EQ(pow(-4, 2), -4 * -4);
    EXPECT_EQ(pow(-3, 2), -3 * -3);
    EXPECT_EQ(pow(-2, 2), -2 * -2);
    EXPECT_EQ(pow(-1, 2), -1 * -1);
    EXPECT_EQ(pow(0, 2), 0 * 0);
    EXPECT_EQ(pow(1, 2), 1 * 1);
    EXPECT_EQ(pow(2, 2), 2 * 2);
    EXPECT_EQ(pow(3, 2), 3 * 3);
    EXPECT_EQ(pow(4, 2), 4 * 4);
    EXPECT_EQ(pow(5, 2), 5 * 5);
}

TEST(Diccionario, obtener) {
    map<int, int> dicc;
    dicc[1] = 2;
    EXPECT_EQ(dicc[1], 2);
}

TEST(Diccionario, definir) {
    map<int, int> dicc;
    EXPECT_FALSE(dicc.count(1) > 0);
    dicc[1] = 2;
    EXPECT_TRUE(dicc.count(1) > 0);
}

TEST(Truco, inicio) {
    Truco *t = new Truco();
    EXPECT_TRUE(t->puntaje_j1() == 0);
    EXPECT_TRUE(t->puntaje_j2() == 0);
}

TEST(Truco, buenas) {
    Truco *t = new Truco();
    EXPECT_FALSE(t->buenas(1));
    for (int i = 0; i < 15; i++)
        t->sumar_punto(1);
    EXPECT_FALSE(t->buenas(1));
    t->sumar_punto(1);
    EXPECT_TRUE(t->buenas(1));
    t->sumar_punto(1);
    t->sumar_punto(1);
    EXPECT_TRUE(t->buenas(1));
}