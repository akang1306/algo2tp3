#include "Driver.h"

Driver::Driver() {
    // COMPLETAR
    _programa = Programa();
    calculadora();
}

Driver::~Driver() {
    // COMPLETAR
}

// Operaciones para agregar instrucciones

void Driver::begin(string rutina) {
    // COMPLETAR
    rutina_actual = rutina;
}

void Driver::end(string rutina) {
    //
}

void Driver::push(int n) {
    // COMPLETAR
    Instruccion push = Instruccion(PUSH, n, "", "");
    _programa.agregarInstruccion(rutina_actual, push);
}

void Driver::add() {
    // COMPLETAR
    Instruccion push = Instruccion(ADD, 0, "", "");
    _programa.agregarInstruccion(rutina_actual, push);
}

void Driver::sub() {
    // COMPLETAR
    Instruccion push = Instruccion(SUB, 0, "", "");
    _programa.agregarInstruccion(rutina_actual, push);
}

void Driver::mul() {
    // COMPLETAR
    Instruccion push = Instruccion(MULT, 0, "", "");
    _programa.agregarInstruccion(rutina_actual, push);
}

void Driver::read(string variable) {
    // COMPLETAR
    Instruccion push = Instruccion(READ, 0, variable, "");
    _programa.agregarInstruccion(rutina_actual, push);
}

void Driver::write(string variable) {
    // COMPLETAR
    Instruccion push = Instruccion(WRITE, 0, variable, "");
    _programa.agregarInstruccion(rutina_actual, push);
}

void Driver::jump(string rutina) {
    // COMPLETAR
    Instruccion push = Instruccion(JUMP, 0, "", rutina);
    _programa.agregarInstruccion(rutina_actual, push);
}

void Driver::jumpz(string rutina) {
    // COMPLETAR
    Instruccion push = Instruccion(JUMPZ, 0, "", rutina);
    _programa.agregarInstruccion(rutina_actual, push);
}

// Operaciones para ejecutar programas

void Driver::comenzarEjecucion(string rutina, int capacidadVentana) {
    // COMPLETAR

    _calculadora = calculadora(_programa, rutina, capacidadVentana);
}

void Driver::asignarVariable(string x, int valor) {
    // COMPLETAR
    _calculadora.asignarVariable(x, valor);
}

bool Driver::ejecucionFinalizada() const {
    // COMPLETAR
    return _calculadora.finalizo();
}

void Driver::ejecutarInstruccionActual() {
    // COMPLETAR
    _calculadora.ejecutar();
}

int Driver::topePila() const {
    // COMPLETAR
    return _calculadora.topPila();
}

int Driver::valorVariable(string x) const {
    // COMPLETAR
    return _calculadora.valorEnInstante(x, _calculadora.instante_actual());
}

int Driver::valorHistoricoVariable(string x, int t) const {
    // COMPLETAR
    return _calculadora.valorEnInstante(x, t);
}

int Driver::instanteActual() const {
    // COMPLETAR
    return _calculadora.instante_actual();
}
