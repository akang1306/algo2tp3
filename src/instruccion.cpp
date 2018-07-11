#include "instruccion.h"
Instruccion::Instruccion(int op, int val, string var, string rut) {
  _op = op;
  _var = var;
  _val = val;
  _rut = rut;
}

int Instruccion::get_operacion() const{
  return _op;
}

int Instruccion::get_valor() const{
  return _val;
}

string Instruccion::get_variable() const{
  return _var;
}

string Instruccion::get_rutina() const{
  return _rut;
}
