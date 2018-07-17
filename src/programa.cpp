#include "programa.h"

Programa::Programa(){
    _rutinas = {};
}

void Programa::agregarInstruccion(rutina rut, Instruccion& instr){
  _rutinas.insert(rut);
  if(instruccionesPorRutina.count(rut) == 1){
    (get<1>(instruccionesPorRutina.at(rut))).push_back(instr);
  } else {
    vector<Instruccion> nuevo_vector;
    nuevo_vector.push_back(instr);
    instruccionesPorRutina[rut] = make_tuple(rut, nuevo_vector);
  }
}

int Programa::longitud(rutina rut){
  return (get<1>(instruccionesPorRutina[rut])).size();
}

set<rutina> Programa::rutinas(){
  return _rutinas;
}

Instruccion Programa::instruccion(rutina rut, int indice){
  return (get<1>(instruccionesPorRutina.at(rut)))[indice];
}

vector<Instruccion> Programa::instrucciones_de(rutina rut){
  return get<1>(instruccionesPorRutina.at(rut));
}
