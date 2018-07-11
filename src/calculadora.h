#ifndef CALCULADORA_H_
#define CALCULADORA_H_

#include <iostream>
#include "utils.h"
#include "Ventana.h"
#include "programa.h"
#include <stack>
#include <tuple>
#include <list>
#include <cassert>

using namespace std;

class calculadora {
public:

	calculadora();
	calculadora(Programa program, rutina rut, int w);
	/*  FUNCIONES DE PROGRAMA
	longitud(programa, rutina) -> int
	rutinas(programa) -> conj(rutina)
	instruccion(programa, rutina, int) -> instruccion
	*/

	void ejecutar();

	bool finalizo() const;

	void asignarVariable(variable variable_a_asignar, int valor_a_asignar);

	int instante_actual() const;

	rutina nombreRutinaActual();

	int indiceInstruccionActual();

	int valorEnInstante(variable variable_a_ver, int instante_a_ver) const;

	int topPila() const;

private:

struct tupla_variables{
	variable nombre;
	list<tuple<int, int>>* valoresViejos;
	Ventana<tuple<int, int>>* valoresRecientes;
};

struct tupla_rutina{
	rutina nombre;
	int longitud;
	int direccion;
};

struct instr{
		operacion op;
		variable var;
		rutina rut;
		int cte;
		tupla_variables* itVar;
		tupla_rutina* itRut;
};

vector<instr> memoria;
string_map<tupla_rutina> rutinas_calc;
string_map<tupla_variables> variables;
string_map<Ventana <tuple<int, int>>> valoresRecientes;
string_map<list <tuple<int, int>>> valoresViejos;
rutina rutinaActual;
instr instruccionActual;
int indiceInstrActualEnRut;
int longitudRutinaActual;
int instanteActual;
int dirMemoriaActual;
stack<int> pila;

};

#include "calculadora.hpp"

#endif // CALCULADORA_H_
