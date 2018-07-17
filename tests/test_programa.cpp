#include "gtest/gtest.h"

#include "../src/programa.h"
#include "../src/instruccion.h"

TEST(test_programa, longitudRutina) {
    Programa p = Programa();
    Instruccion push = Instruccion(PUSH, 2, "a", "a");
    Instruccion mult = Instruccion(MULT, 0, "a", "a");
    Instruccion push2 = Instruccion(PUSH, 3, "a", "a");
    p.agregarInstruccion("A", push);
    p.agregarInstruccion("A", mult);
    p.agregarInstruccion("B", push2);
    EXPECT_EQ(p.longitud("A"), 2);
    EXPECT_EQ(p.longitud("B"), 1);
    Instruccion sub = Instruccion(SUB, 0, "a", "a");
    p.agregarInstruccion("A", sub);
    EXPECT_EQ(p.longitud("A"), 3);
}

TEST(test_programa, rutinas) {
    Programa p;
    Instruccion push = Instruccion(PUSH, 2, "a", "a");
    Instruccion mult = Instruccion(MULT, 0, "a", "a");
    Instruccion push2 = Instruccion(PUSH, 3, "a", "a");
    p.agregarInstruccion("A", push);
    p.agregarInstruccion("A", mult);
    p.agregarInstruccion("B", push2);
    std::set<rutina> test = {"A", "B"};
//    EXPECT_EQ( p.rutinas(), test);
    std::set<rutina> test2 = {"A", "D", "B"};
    Instruccion jump = Instruccion(JUMP, 0, "a", "A");
    p.agregarInstruccion("D", jump);
//    EXPECT_EQ(p.rutinas(), test2);
}

TEST(test_programa, instruccion){
    Programa p;
    Instruccion push = Instruccion(PUSH, 2, "a", "a");
    p.agregarInstruccion("A", push);
    Instruccion i = Instruccion(MULT, 0, "a", "a");
    p.agregarInstruccion("A", i);
    EXPECT_EQ((p.instruccion("A", 1).get_operacion()), i.get_operacion());
}

TEST(test_programa, instrucciones_de){
    Programa p;
    Instruccion i = Instruccion(MULT, 0, "a", "a");
    Instruccion k = Instruccion(ADD, 0, "a", "a");
    Instruccion j = Instruccion(SUB, 0, "a", "a");
    p.agregarInstruccion("pepe", i);
    p.agregarInstruccion("pepe", k);
    p.agregarInstruccion("pepe", j);
    EXPECT_EQ((p.instrucciones_de("pepe")).size(), 3);
}
