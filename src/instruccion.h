#ifndef INSTRUCCION_H_
#define INSTRUCCION_H_

#include <iostream>
#include "utils.h"

using namespace std;

class Instruccion {
public:

	//   istream& operator>>(istream&, T&).
	// que lee un elemento de tipo T.

	Instruccion(int op, int val, string var, string rut);
  operacion get_operacion() const;
  int get_valor() const;
  variable get_variable() const;
  rutina get_rutina() const;

private:
    operacion _op;
    int _val;
    variable _var;
    rutina _rut;

};



#endif // INSTRUCCION_H_
