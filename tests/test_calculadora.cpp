#include "gtest/gtest.h"

#include "../src/calculadora.h"

TEST(test_calculadora, programa_vacio){
    Programa p;
    calculadora c(p, "A", 6);
    c.ejecutar();
    ASSERT_TRUE(c.finalizo());
    EXPECT_EQ(c.instante_actual(), 0);
    EXPECT_EQ(c.topPila(), 0);
}

TEST(test_calculadora, ejecucion_finalizada){
    Programa p;
    p.agregarInstruccion("A", Instruccion(PUSH, 5, "a", "a"));
    p.agregarInstruccion("A", Instruccion(JUMP, 0, "a", "J"));
    calculadora c(p, "A", 2);
    c.ejecutar();
    ASSERT_TRUE(c.finalizo());
    EXPECT_EQ(c.instante_actual(), 2);

    p.agregarInstruccion("J", Instruccion(ADD, 0, "a", "a"));
    p.agregarInstruccion("J", Instruccion(JUMPZ, 0, "a", "A"));
    c.ejecutar();
    ASSERT_TRUE(c.finalizo());
    EXPECT_EQ(c.topPila(), 5);
    EXPECT_EQ(c.instante_actual(), 4);
}

TEST(test_calculadora, jumpz){
    Programa q;
    q.agregarInstruccion("algo", Instruccion(PUSH, 5, "a", "a"));
    q.agregarInstruccion("algo", Instruccion(WRITE, 0, "X", "a"));
    q.agregarInstruccion("algo", Instruccion(JUMPZ, 0, "a", "rutina"));
    q.agregarInstruccion("rutina", Instruccion(PUSH, 10, "a", "a"));
    calculadora c(q, "algo", 3);
    c.ejecutar();
    EXPECT_EQ(c.nombreRutinaActual(), "rutina");
    EXPECT_EQ(c.valorEnInstante("X", 3), 5);
}