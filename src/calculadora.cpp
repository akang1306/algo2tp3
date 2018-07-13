#include "calculadora.h"

int busquedaBinaria(Ventana<tuple<int, int>> ventana, int min, int max, int value){
    int tam = max - min;
    if(tam > 1){
      int mid = min + (tam / 2);
      if(get<1>(ventana[mid]) > value){
        busquedaBinaria(ventana, min, mid, value);
      }else{
        if(get<1>(ventana[mid]) < value){
          busquedaBinaria(ventana, mid, max, value);
        }else{
          return mid;
        }
      }
    }
    return min;
}

calculadora::calculadora(){
    dirMemoriaActual = -1;

}
calculadora::calculadora(Programa &program, const rutina &rut, int w){
  if(program.rutinas().empty()){
      dirMemoriaActual = -1;
  }
  int long_total = 0;
  set<rutina> rutinas = program.rutinas();
  typename std::set<rutina>::iterator i =  rutinas.begin();
  while(i != rutinas.end()){
    long_total = long_total + program.longitud(*i);
    i++;
  }
  rutinaActual = rut;
  indiceInstrActualEnRut = 0;
  instanteActual = 0;
  memoria = vector<instr>(long_total);
  int m = 0;
  i = rutinas.begin();
  while(i!=rutinas.end()) {
    vector<Instruccion> instrucciones(program.instrucciones_de(*i));
    if (instrucciones.size() == 0) {
      // nada
    }else{
    if (*i == rut) {
      instruccionActual.op = instrucciones[0].get_operacion();
      longitudRutinaActual = instrucciones.size();
      dirMemoriaActual = m;
    }
    typename std::vector<Instruccion>::iterator j = instrucciones.begin();
    while (j != instrucciones.end()) {
      if (j == instrucciones.begin()) {
        rutina clave = *i;
        tupla_rutina significado;
        significado.nombre = clave;
        significado.longitud = instrucciones.size();
        significado.direccion = m;
        rutinas_calc.definir(clave, significado);
      }
      memoria[m].op = (*j).get_operacion();
      if ((*j).get_operacion() == READ or (*j).get_operacion() == WRITE) {
        memoria[m].var = (*j).get_variable();
        tupla_variables *it_variable;
        if (!variables.definida((*j).get_variable())) {
          list<tuple<int, int>> *it_variable_vieja;
          Ventana<tuple<int, int>> *it_variable_reciente;
          list<tuple<int, int>> lista_viejos;
          Ventana<tuple<int, int>> ventana_recientes = Ventana<tuple<int, int>>(w);
          it_variable_reciente = valoresRecientes.definir_ventana((*j).get_variable(), ventana_recientes);
          it_variable_vieja = valoresViejos.definir((*j).get_variable(), lista_viejos);
          tupla_variables significado;
          significado.nombre = (*j).get_variable();
          significado.valoresViejos = it_variable_vieja;
          significado.valoresRecientes = it_variable_reciente;
          it_variable = variables.definir((*j).get_variable(), significado);
        } else {
          tupla_variables significado = variables[(*j).get_variable()];
          it_variable = &significado;
        }
        memoria[m].itVar = it_variable;
      } else if ((*j).get_operacion() == JUMP || (*j).get_operacion() == JUMPZ) {
        memoria[m].rut = *i;
      } else {
        memoria[m].cte = (*j).get_valor();
      }
      m++;
      j++;
    }
  }
      i++;
    }
      for(int i=0;i<m;i++){
        if(memoria[i].op == JUMP || memoria[i].op == JUMPZ){
          tupla_rutina* it_rutina;
          if(rutinas_calc.definida(memoria[i].rut)){
            tupla_rutina rutina  = rutinas_calc[memoria[i].rut];
            it_rutina  = &rutina;
          }else{
            it_rutina = nullptr;
          }
	         memoria[i].itRut = it_rutina;
        }
      }
    }

void calculadora::ejecutar(){
  if(!finalizo()) {
      assert(dirMemoriaActual >= 0);
      instr instr_a_ejecutar = memoria[dirMemoriaActual];
      indiceInstrActualEnRut++;
      if (indiceInstrActualEnRut == longitudRutinaActual) {
          dirMemoriaActual = -2;
      }
      dirMemoriaActual++;
      if (instr_a_ejecutar.op == JUMP) {
          tupla_rutina *it_nueva_rutina = instr_a_ejecutar.itRut;
          if (it_nueva_rutina) {
              dirMemoriaActual = it_nueva_rutina->direccion;
              longitudRutinaActual = it_nueva_rutina->longitud;
              indiceInstrActualEnRut = 0;
              rutinaActual = it_nueva_rutina->nombre;
          } else {
              dirMemoriaActual = -1;
          }
      }
      if (instr_a_ejecutar.op == JUMPZ && !pila.empty()) {
          if (pila.top() == 0) {
              tupla_rutina *it_nueva_rutina = instr_a_ejecutar.itRut;
              if (it_nueva_rutina) {
                  dirMemoriaActual = it_nueva_rutina->direccion;
                  longitudRutinaActual = it_nueva_rutina->longitud;
                  indiceInstrActualEnRut = 0;
                  rutinaActual = it_nueva_rutina->nombre;
              }
          }
      }
      if (instr_a_ejecutar.op == READ) {
          if (instr_a_ejecutar.itVar) {
              tupla_variables variable_a_leer = *(instr_a_ejecutar.itVar);
              if (!(*(variable_a_leer.valoresViejos)).empty()) {
                  tuple<int, int> tupla = make_tuple(0, instanteActual);
                  (*(variable_a_leer.valoresViejos)).push_back(tupla);
                  (*(variable_a_leer.valoresRecientes)).registrar(tupla);
              }
              tuple<int, int> new_tuple = (*(variable_a_leer.valoresViejos)).back();
              pila.push(get<0>(new_tuple));
          } else {
              pila.push(0);

          }
      }
      if (instr_a_ejecutar.op == WRITE) {
          if (instr_a_ejecutar.itVar) {
              tupla_variables variable_a_escribir = *(instr_a_ejecutar.itVar);
              int valor_a_escribir;
              if (pila.empty()) {
                  valor_a_escribir = 0;
              } else {
                  valor_a_escribir = pila.top();
                  pila.pop();
              }
              (*(variable_a_escribir.valoresViejos)).push_back(make_tuple(valor_a_escribir, instanteActual));
              (*(variable_a_escribir.valoresRecientes)).registrar(make_tuple(valor_a_escribir, instanteActual));
          }
      }
      if (instr_a_ejecutar.op == MULT) {
          if (pila.size() < 2) {
              if (pila.size() == 1) {
                  int valor = pila.top();
                  pila.pop();
                  pila.push(0);
              } else {
                  pila.push(0);
              }
          } else {
              int valor1 = pila.top();
              pila.pop();
              int valor2 = pila.top();
              pila.pop();
              pila.push(valor1 * valor2);
          }

      }
      if (instr_a_ejecutar.op == SUB) {
          if (pila.size() < 2) {
              if (pila.size() == 1) {
                  int valor = pila.top();
                  pila.pop();
                  pila.push(0 - valor);
              } else {
                  pila.push(0);
              }
          } else {
              int valor1 = pila.top();
              pila.pop();
              int valor2 = pila.top();
              pila.pop();
              pila.push(valor2 - valor1);
          }

      }
      if (instr_a_ejecutar.op == ADD) {
          if (pila.size() < 2) {
              if (pila.size() == 1) {
                  int valor = pila.top();
                  pila.pop();
                  pila.push(valor);
              } else {
                  pila.push(0);
              }
          } else {
              int valor1 = pila.top();
              pila.pop();
              int valor2 = pila.top();
              pila.pop();
              pila.push(valor1 + valor2);
          }
      }

      if (instr_a_ejecutar.op == PUSH) {
          pila.push(instr_a_ejecutar.cte);
      }
      instanteActual++;
  }
}

bool calculadora::finalizo() const{
  return  ((indiceInstrActualEnRut >= longitudRutinaActual) || (dirMemoriaActual < 0));
}

void calculadora::asignarVariable(variable variable_a_asignar, int valor_a_asignar){
  if(variables.definida(variable_a_asignar)){
    tupla_variables nueva_tupla =  variables[variable_a_asignar];
    (*(nueva_tupla).valoresViejos).push_back(make_tuple(valor_a_asignar, instanteActual));
    (*(nueva_tupla).valoresRecientes).registrar(make_tuple(valor_a_asignar, instanteActual));
  }else{
    list<tuple<int, int>> nueva_lista;
    Ventana<tuple<int, int>> nueva_ventana = Ventana<tuple<int, int>>(1);
     /*
      * Si la variable es nueva, no necesito una ventana de largo W ya que
      * no esta en el codigo fuente, para evitar casos borde en los algoritmos
      * de ejecutar, la creo de largo 1, ya que me cuesta O(1).
      */
    nueva_lista.push_back(make_tuple(valor_a_asignar, instanteActual));
    nueva_ventana.registrar(make_tuple(valor_a_asignar, instanteActual));
    Ventana<tuple<int, int>>* itVentana = valoresRecientes.definir_ventana(variable_a_asignar, nueva_ventana);
    list<tuple<int, int>>* itLista = valoresViejos.definir(variable_a_asignar, nueva_lista);
    tupla_variables nueva_tupla;
    nueva_tupla.nombre = variable_a_asignar;
    nueva_tupla.valoresViejos = itLista;
    nueva_tupla.valoresRecientes = itVentana;
    variables.definir(variable_a_asignar, nueva_tupla);
  }
}

int calculadora::instante_actual() const{
  return instanteActual;
}

rutina calculadora::nombreRutinaActual(){
  return rutinaActual;
}

int calculadora::indiceInstruccionActual(){
  return indiceInstrActualEnRut;
}

int calculadora::valorEnInstante(variable variable_a_ver, int instante_a_ver) const{
  if(variables. definida(variable_a_ver)){
    tupla_variables significado =  variables.at(variable_a_ver);
    if(instante_a_ver < (*(significado.valoresRecientes)).tam()){
      int indice_ventana = busquedaBinaria(*(significado.valoresRecientes), 0, (*(significado.valoresRecientes)).tam(), instante_a_ver);
       /*
        *     Busqueda binaria sobre los indices de la ventana y
        *     me quedo con el indice mas chico en el caso de que
        *     el indice que busco no este.
        */
      return get<0>((*(significado.valoresRecientes))[indice_ventana]);
    }else{
      list<tuple<int, int>> lista = *(significado.valoresViejos);
      list<tuple<int, int>>::iterator iterador = lista.begin();
      int instante = get<1>(*(iterador));
      int valor;
      while(iterador!=lista.end() && instante_a_ver < instante){
        valor = get<0>(*(iterador));
        iterador++;
        instante = get<1>(*(iterador));
      }
      if(instante_a_ver > instante){
        valor = get<0>(*(iterador));
      }
      return valor;
    }
  }else{

    return 0;
  }
}

int calculadora::topPila() const {
  if(!pila.empty()){
    return pila.top();
  }
  return 0;
}
