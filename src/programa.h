#ifndef PROGRAMA_H_
#define PROGRAMA_H_

#include <iostream>
#include "utils.h"
#include "instruccion.h"
#include "string_map.h"
#include<stack>
#include<tuple>

using namespace std;

class Programa {
public:

	Programa();
	void agregarInstruccion(rutina rut, Instruccion& instr);
	int longitud(rutina rut);
 	set<rutina> rutinas();
	Instruccion instruccion(rutina rut, int indice);
	vector<Instruccion> instrucciones_de(rutina rut);

private:

	set<rutina> _rutinas;
	string_map<tuple <rutina, vector<Instruccion>>> instruccionesPorRutina;
};


#endif // PROGRAMA_H_
