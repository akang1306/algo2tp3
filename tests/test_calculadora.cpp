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

TEST(test_calculadora, test_1){
    Programa p;
    p.agregarInstruccion("A", Instruccion(PUSH, 5, "a", "a"));
    p.agregarInstruccion("A", Instruccion(JUMP, 0, "a", "J"));
    calculadora c(p, "A", 2);
    c.ejecutar();
    ASSERT_FALSE(c.finalizo());
    EXPECT_EQ(c.instante_actual(), 1);
    EXPECT_EQ(c.indiceInstruccionActual(), 0);
    c.ejecutar();
    EXPECT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_TRUE(c.finalizo());
    EXPECT_EQ(c.instante_actual(), 2);

    p.agregarInstruccion("J", Instruccion(ADD, 0, "a", "a"));
    p.agregarInstruccion("J", Instruccion(JUMPZ, 0, "a", "A"));
    c.ejecutar();
    ASSERT_FALSE(c.finalizo());
    EXPECT_EQ(c.topPila(), 5);
    EXPECT_EQ(c.instante_actual(), 3);
    c.ejecutar();
    EXPECT_EQ(c.instante_actual(), 4);
    ASSERT_TRUE(c.finalizo());
}

TEST(test_calculadora, test_2){
    Programa q;
    q.agregarInstruccion("algo", Instruccion(PUSH, 5, "a", "a"));
    q.agregarInstruccion("algo", Instruccion(WRITE, 0, "X", "a"));
    q.agregarInstruccion("algo", Instruccion(JUMPZ, 0, "a", "rutina"));
    q.agregarInstruccion("rutina", Instruccion(PUSH, 10, "a", "a"));
    calculadora c(q, "algo", 3);
    c.ejecutar();
    EXPECT_EQ(c.nombreRutinaActual(), "algo");
    EXPECT_EQ(c.topPila(), 5);
    EXPECT_EQ(c.instante_actual(), 1);
    c.ejecutar();
    EXPECT_EQ(c.instante_actual(), 2);
    EXPECT_EQ(c.valorEnInstante("X", 2), 5);
    EXPECT_EQ(c.topPila(), 0);
    c.ejecutar();
    EXPECT_EQ(c.instante_actual(), 3);
    ASSERT_FALSE(c.finalizo());
    EXPECT_EQ(c.nombreRutinaActual(), "rutina");
    EXPECT_EQ(c.indiceInstruccionActual(), 0);
    c.ejecutar();
    EXPECT_EQ(c.nombreRutinaActual(), "rutina");
    //EXPECT_EQ(c.indiceInstruccionActual(), 0); acá debería ser 0 o 1?
    ASSERT_TRUE(c.finalizo());
}

TEST(test_calculadora, variable_no_inicializada){
    Programa p;
    p.agregarInstruccion("A", Instruccion(READ, 0, "variable", "a"));
    p.agregarInstruccion("A", Instruccion(PUSH, 2, "a", "a"));
    p.agregarInstruccion("A", Instruccion(ADD, 0, "a", "a"));
    calculadora c(p, "A", 148);
    c.ejecutar();
    EXPECT_EQ(c.instante_actual(), 1);
    EXPECT_EQ(c.topPila(), 0);
    c.ejecutar();
    c.ejecutar();
    EXPECT_EQ(c.topPila(), 2);
    EXPECT_EQ(c.instante_actual(), 3);
    ASSERT_TRUE(c.finalizo());
}

TEST(test_calculadora, valores_variables){
    Programa p;
    p.agregarInstruccion("A", Instruccion(PUSH, 10, "a", "a"));
    p.agregarInstruccion("A", Instruccion(WRITE, 0, "X", "a"));
    p.agregarInstruccion("A", Instruccion(PUSH, 5, "a", "a"));
    p.agregarInstruccion("A", Instruccion(PUSH, 1, "a", "a"));
    p.agregarInstruccion("A", Instruccion(MULT, 0, "a", "a"));
    p.agregarInstruccion("A", Instruccion(READ, 0, "Z", "a"));
    calculadora c(p, "A", 2);

    for(int i = 1; i < 7; i++){
        c.ejecutar();
        EXPECT_EQ(c.instante_actual(), i);
    }

    EXPECT_EQ(c.topPila(), 0);
    //la variable no está en la ventana
    EXPECT_EQ(c.valorEnInstante("X", 4), 10);
    c.asignarVariable("Y", 8);
    EXPECT_EQ(c.valorEnInstante("Y", 6), 8);
    //variable no definida
    ASSERT_FALSE(c.valorEnInstante("sfkjd", 5) == 2);

}