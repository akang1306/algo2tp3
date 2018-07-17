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
    Instruccion push = Instruccion(PUSH, 5, "a", "a");
    Instruccion jumpz = Instruccion(JUMPZ, 0, "a", "J");
    p.agregarInstruccion("A", push);
    p.agregarInstruccion("A", jumpz);
    calculadora c(p, "A", 2);
    c.ejecutar();
    ASSERT_FALSE(c.finalizo());
    EXPECT_EQ(c.instante_actual(), 1);
    EXPECT_EQ(c.indiceInstruccionActual(), 1);
    c.ejecutar();
    EXPECT_EQ(c.indiceInstruccionActual(), 2);
    ASSERT_TRUE(c.finalizo());
    EXPECT_EQ(c.instante_actual(), 2);
}

TEST(test_calculadora, test_2){
    Programa q;
    Instruccion push = Instruccion(PUSH, 5, "a", "a");
    Instruccion write = Instruccion(WRITE, 0, "X", "a");
    Instruccion jump = Instruccion(JUMP, 0, "a", "rutina");
    Instruccion push2 = Instruccion(PUSH, 10, "a", "a");
    q.agregarInstruccion("algo", push);
    q.agregarInstruccion("algo", write);
    q.agregarInstruccion("algo", jump);
    q.agregarInstruccion("rutina", push2);
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
    EXPECT_EQ(c.indiceInstruccionActual(), 1);
    ASSERT_TRUE(c.finalizo());
}

TEST(test_calculadora, variable_no_inicializada){
    Programa p;
    Instruccion read = Instruccion(READ, 0, "variable", "a");
    Instruccion push = Instruccion(PUSH, 2, "a", "a");
    Instruccion jump = Instruccion(ADD, 0, "a", "a");
    p.agregarInstruccion("A", read);
    p.agregarInstruccion("A", push);
    p.agregarInstruccion("A", jump);
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
    Instruccion push = Instruccion(PUSH, 10, "a", "a");
    Instruccion write = Instruccion(WRITE, 0, "X", "a");
    Instruccion push2 = Instruccion(PUSH, 5, "a", "a");
    Instruccion push3 = Instruccion(PUSH, 1, "a", "a");
    Instruccion mult = Instruccion(MULT, 0, "a", "a");
    Instruccion read = Instruccion(READ, 0, "Z", "a");
    p.agregarInstruccion("A", push);
    p.agregarInstruccion("A", write);
    p.agregarInstruccion("A", push2);
    p.agregarInstruccion("A", push3);
    p.agregarInstruccion("A",  mult);
    p.agregarInstruccion("A", read);
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
