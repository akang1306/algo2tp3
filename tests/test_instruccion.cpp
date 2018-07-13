#include "gtest/gtest.h"

#include "../src/instruccion.h"

TEST(test_instruccion, general){
    Instruccion i = Instruccion(PUSH, 4, "a", "a");
    Instruccion j = Instruccion(ADD, 0, "a", "a");
    Instruccion k = Instruccion(READ, 0, "X", "a");
    Instruccion q = Instruccion(JUMP, 0, "a", "pepe");
    EXPECT_EQ(i.get_operacion(), PUSH);
    EXPECT_EQ(i.get_valor(), 4);
    EXPECT_EQ(i.get_variable(), "a");
    EXPECT_EQ(i.get_rutina(), "a");
    EXPECT_EQ(j.get_operacion(), ADD);
    EXPECT_EQ(j.get_variable(), "a");
    EXPECT_EQ(j.get_rutina(), "a");
    EXPECT_EQ(k.get_operacion(), READ);
    EXPECT_EQ(k.get_variable(), "X");
    EXPECT_EQ(k.get_rutina(), "a");
    EXPECT_EQ(q.get_operacion(), JUMP);
    EXPECT_EQ(q.get_rutina(), "pepe");
    EXPECT_FALSE(q.get_variable() != "a");
}