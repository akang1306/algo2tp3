#include "calculadora.h"

int busquedaBinaria(Ventana<tuple<int, int>>& ventana, int min, int max, int value){
    while(min < max){
      int mid = (min + ((max-min)/2));
      if(get<1>(ventana[mid]) < value){
        min = mid + 1;
      }else{
        max = mid;
      }
    }
    return min;
}

int busquedaLineal(Ventana<tuple<int, int>>& ventana, int min, int max, int value){
    for(int i=min;i<max;i++){
      if(get<1>(ventana[i]) == value){
        return i;
    }
  }
  return max-1;
}

calculadora::calculadora(){
    dirMemoriaActual = -1;

}
calculadora::calculadora(Programa& program, const rutina& rut, int w){
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
      // Nada
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
        tupla_variables* it_variable;
        if (!variables.definida(memoria[m].var)) {

          list<tuple<int, int>>* it_variable_vieja;
          Ventana<tuple<int, int>>* it_variable_reciente;

          std::list<tuple<int, int>> lista_viejos;
          Ventana<tuple<int, int>> ventana_recientes = Ventana<tuple<int, int>>(w);

          it_variable_reciente = valoresRecientes.definir_ventana(memoria[m].var, ventana_recientes);
          it_variable_vieja = valoresViejos.definir(memoria[m].var, lista_viejos);

          tupla_variables significado;
          significado.nombre = memoria[m].var;
          significado.valoresViejos = it_variable_vieja;
          significado.valoresRecientes = it_variable_reciente;
          it_variable = variables.definir(memoria[m].var, significado);

        }else{
          tupla_variables significado = variables[(*j).get_variable()];
          it_variable = &significado;
        }
          memoria[m].itVar = it_variable;
      }else if ((*j).get_operacion() == JUMP || (*j).get_operacion() == JUMPZ) {
        memoria[m].rut = (*j).get_rutina();
      }else{
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
            it_rutina  = &rutinas_calc[memoria[i].rut];
          }else{
            it_rutina = nullptr;
          }
	         memoria[i].itRut = it_rutina;
        }
      }
    }

void calculadora::ejecutar(){
  if(!finalizo()) {
      instr instr_a_ejecutar = memoria[dirMemoriaActual];
      indiceInstrActualEnRut++;
      if (indiceInstrActualEnRut == longitudRutinaActual) {
          dirMemoriaActual = -2;
      }
      dirMemoriaActual++;
      if (instr_a_ejecutar.op == JUMP) {

        /*
         * tupla_rutina *it_nueva_rutina = instr_a_ejecutar.itRut;
         * if(it_nueva_rutina){
         * }
         */

          if (rutinas_calc.definida(instr_a_ejecutar.rut) ) {
              tupla_rutina nueva_rutina = rutinas_calc.at(instr_a_ejecutar.rut);
              longitudRutinaActual = nueva_rutina.longitud;
              dirMemoriaActual = nueva_rutina.direccion;
              indiceInstrActualEnRut = 0;
              rutinaActual = nueva_rutina.nombre;
          }else{
              dirMemoriaActual = -1;
          }
      }
      if (instr_a_ejecutar.op == JUMPZ) {
          if(!pila.empty()){
              if(pila.top() != 0){
                  instanteActual++;
                  return;
              }
          }
          if (rutinas_calc.definida(instr_a_ejecutar.rut)) {
              tupla_rutina nueva_rutina = rutinas_calc.at(instr_a_ejecutar.rut);
              if (rutinas_calc.definida(nueva_rutina.nombre)) {
                  longitudRutinaActual = nueva_rutina.longitud;
                  dirMemoriaActual = nueva_rutina.direccion;
                  indiceInstrActualEnRut = 0;
                  rutinaActual = nueva_rutina.nombre;
              }
          /*
           *   tupla_rutina *it_nueva_rutina = instr_a_ejecutar.itRut;
           *   if (it_nueva_rutina) {
           *       dirMemoriaActual = it_nueva_rutina->direccion;
           *       longitudRutinaActual = it_nueva_rutina->longitud;
           *       indiceInstrActualEnRut = 0;
           *       rutinaActual = it_nueva_rutina->nombre;
           *   }
           */
          }else{
              dirMemoriaActual = -1;
          }
      }
      if (instr_a_ejecutar.op == READ) {

          /*
           * if (instr_a_ejecutar.itVar && variables.definida(instr_a_ejecutar.var)) {
           *    tupla_variables variable_a_leer = variables.at(instr_a_ejecutar.var);
           *    if(!(variable_a_leer.valoresRecientes)->tam()){
           *        tuple<int, int> tupla = make_tuple(0, instanteActual);
           *        (variable_a_leer.valoresViejos)->push_back(tupla);
           *        (*(variable_a_leer.valoresRecientes)).registrar(tupla);
           *    }
           *    tuple<int, int> new_tuple = (variable_a_leer.valoresViejos)->back();
           *    pila.push(get<0>(new_tuple));
           * }
           */

            if(instr_a_ejecutar.itVar){
              tupla_variables variable_a_leer = variables.at(instr_a_ejecutar.var);
              if (valoresViejos.at(instr_a_ejecutar.var).size() == 0) {
                  tuple<int, int> tupla = make_tuple(0, instanteActual);
                  asignarVariable(instr_a_ejecutar.var, 0);
              }
              pila.push(get<0>((valoresViejos.at(instr_a_ejecutar.var)).back()));
          }else{
              pila.push(0);

          }
      }
      if (instr_a_ejecutar.op == WRITE) {

          /* if (instr_a_ejecutar.itVar) {
           *    tupla_variables variable_a_escribir = *(instr_a_ejecutar.itVar);
           *    int valor_a_escribir;
           *    if (pila.empty()) {
           *        valor_a_escribir = 0;
           *    }else{
           *        valor_a_escribir = pila.top();
           *        pila.pop();
           *    }
           *    (variable_a_escribir.valoresViejos)->push_back(make_tuple(valor_a_escribir, instanteActual));
           *    (*(variable_a_escribir.valoresRecientes)).registrar(make_tuple(valor_a_escribir, instanteActual));
           * }
           */

          if(variables.definida(instr_a_ejecutar.var)){
            tupla_variables variable_a_escribir = variables.at(instr_a_ejecutar.var);
            int valor_a_escribir;
            if (pila.empty()) {
                valor_a_escribir = 0;
            }else{
                valor_a_escribir = pila.top();
                pila.pop();
            }
            asignarVariable(instr_a_ejecutar.var, valor_a_escribir);
          }
      }
      if (instr_a_ejecutar.op == MULT) {
          if (pila.size() < 2) {
              if (pila.size() == 1) {
                  int valor = pila.top();
                  pila.pop();
                  pila.push(0);
              }else{
                  pila.push(0);
              }
          }else{
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
              }else{
                  pila.push(0);
              }
          }else{
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
              }else{
                  pila.push(0);
              }
          }else{
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
  return  ( (dirMemoriaActual > memoria.size())|| (indiceInstrActualEnRut >= longitudRutinaActual) || (dirMemoriaActual < 0));
}

void calculadora::asignarVariable(variable variable_a_asignar, int valor_a_asignar){
  if(variables.definida(variable_a_asignar)){

     /*
      * tupla_variables nueva_tupla = variables.at(variable_a_asignar);
      * (nueva_tupla).valoresViejos->push_back(make_tuple(valor_a_asignar, instanteActual));
      * (*(nueva_tupla.valoresRecientes)).registrar(make_tuple(valor_a_asignar, instanteActual));
      */

      valoresViejos.at(variable_a_asignar).push_back(make_tuple(valor_a_asignar, instanteActual));
      (valoresRecientes.at(variable_a_asignar)).registrar(make_tuple(valor_a_asignar, instanteActual));
    }else{
      list<tuple<int, int>> nueva_lista;
      Ventana<tuple<int, int>> nueva_ventana = Ventana<tuple<int, int>>(1);

     /*
      * Si la variable es nueva, no necesito una ventana de largo W ya que
      * no esta en el codigo fuente, para evitar casos borde en los algoritmos
      * de ejecutar, la creo de largo 1, ya que me cuesta O(1).
      */

      Ventana<tuple<int, int>>* itVentana = valoresRecientes.definir_ventana(variable_a_asignar, nueva_ventana);
      list<tuple<int, int>>* itLista = valoresViejos.definir(variable_a_asignar, nueva_lista);

      tupla_variables nueva_tupla;
      nueva_tupla.nombre = variable_a_asignar;
      nueva_tupla.valoresViejos = itLista;
      nueva_tupla.valoresRecientes = itVentana;
      variables.definir(variable_a_asignar, nueva_tupla);

      asignarVariable(variable_a_asignar, valor_a_asignar);
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
    Ventana<tuple<int, int>> valores = valoresRecientes.at(variable_a_ver);
    if(valores.tam() == 0){
      return 0;
    }
    if((valoresViejos.at(variable_a_ver)).size() != 0){
      if((instanteActual - instante_a_ver) < valores.capacidad()){
        int indice_ventana = busquedaBinaria(valores, 0 , valores.tam() - 1, instante_a_ver);

         /*
          *     Busqueda binaria sobre los indices de la ventana y
          *     me quedo con el indice mas chico en el caso de que
          *     el indice que busco no este.
          */

        if(!(get<1>(valores[indice_ventana])>instante_a_ver)){
          return get<0>(valoresRecientes.at(variable_a_ver)[indice_ventana]);
        }
      }
        for(int i=0;i<valores.tam();i++){
        }

        list<tuple<int, int>> lista = valoresViejos.at(variable_a_ver);
        list<tuple<int, int>>::iterator iterador = lista.begin();
        int valor = get<0>(*(iterador));
        if(get<1>(*(iterador))>instante_a_ver){
            return 0;
        }
        iterador++;
        if(iterador == lista.end()){
            return valor;
        }
        int instante = get<1>(*(iterador));
        while(iterador!=lista.end() && instante_a_ver > instante){
          valor = get<0>(*(iterador));
          iterador++;
          instante = get<1>(*(iterador));
        }
        if(instante == instante_a_ver){
           valor = get<0>(*(iterador));
        }
        return valor;

    }else{
      return 0;
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
