const int TAM = 256;

template <typename T>
string_map<T>::Nodo::Nodo(){
  definicion = NULL;
  siguientes = new Nodo*[TAM];
  int i = 0;
  for(i=0; i<TAM; i++){
    siguientes[i] = NULL;
  }
}

template <typename T>
string_map<T>::string_map(){
    // COMPLETAR
    raiz = NULL;
    _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia. template <typename T>

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // COMPLETAR
    if(raiz != NULL){
      destructor_recursivo(raiz);
    }
    if(d.raiz == NULL){
      raiz = NULL;
      return *this;
    }else{
      raiz = new Nodo;
      iguales_recursivo(raiz, d.raiz);
    }
    return *this;
}

template<typename T>
void string_map<T>::iguales_recursivo( Nodo* p1, const Nodo* p2){
  if(p2->definicion){
    p1->definicion = new T;
    T apuntar = *(p2->definicion);
    *(p1->definicion) = apuntar;
  }
  int i = 0;
  for(i=0;i<TAM;i++){
      if(p2->siguientes[i] != NULL){
        p1->siguientes[i] = new Nodo;
        iguales_recursivo(p1->siguientes[i], p2->siguientes[i]);
      }
    }
}

template<typename T>
void string_map<T>::destructor_recursivo(Nodo* p ){
  int i = 0;
  for (i = 0; i < TAM ; i++) {
    if(p->siguientes[i] != NULL){
      destructor_recursivo(p->siguientes[i]);
    }
  }
  if(p->definicion){
    delete p->definicion;
  }
  delete[] p->siguientes;
  delete p;
}

template <typename T>
string_map<T>::~string_map(){
    // COMPLETAR
    if(raiz != NULL){
      destructor_recursivo(raiz);
    }else{
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
    if (raiz == NULL){
      raiz = new Nodo;
    }
    Nodo* buscador = raiz;
    for(int i=0; i<clave.size() ;i++) {
      if(buscador->siguientes[int(clave[i])] == NULL){
          buscador->siguientes[int(clave[i])] = new Nodo;
        }
      buscador = buscador->siguientes[int(clave[i])];
    }
    if(buscador->definicion == NULL ){
          buscador->definicion = new T;
          _size ++;
    }
    return *(buscador->definicion);
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    // COMPLETAR
    if (raiz == NULL){
      return 0;
    }
    Nodo* buscador = raiz;
    for(int i=0; i<clave.size() ;i++) {
    if(buscador->siguientes[int(clave[i])] == NULL){
        return 0;
      }
      buscador = buscador->siguientes[int(clave[i])];
    }
    if(buscador->definicion == NULL ){
          return 0;
    }
    return 1;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    // COMPLETAR
    /*if (raiz == NULL){
      return 0;
    }*/
    Nodo* buscador = raiz;
    for(int i=0; i<clave.size() ;i++) {
    /*if(buscador->siguientes[int(clave[i])] == NULL){
        return 0;
      }*/
      buscador = buscador->siguientes[int(clave[i])];
    }
    /*if(buscador->definicion == NULL ){
          return 0;
    }*/
    return *buscador->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    // COMPLETAR
    /*if (raiz == NULL){
      return 0;
    }*/
    Nodo* buscador = raiz;
    for(int i=0; i<clave.size() ;i++) {
    /*if(buscador->siguientes[int(clave[i])] == NULL){
        return 0;
      }*/
      buscador = buscador->siguientes[int(clave[i])];
    }
    /*if(buscador->definicion == NULL ){
          return 0;
    }*/
    return *buscador->definicion;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    // COMPLETAR
      if (raiz == NULL){
        return;
      }
      Nodo* buscador = raiz;
      Nodo* anterior = NULL;
      for(int i=0; i<clave.size() ;i++) {
          anterior = buscador;
          buscador = buscador->siguientes[int(clave[i])];
      }
      if(buscador->definicion != NULL ){
            bool tieneHijos = false;
            for(int i=0;i<TAM;i++){
              if(buscador->siguientes[i] != NULL){
                tieneHijos = true;
              }
            }
            delete buscador->definicion;
            buscador->definicion = NULL;
            _size --;
      }
      return;
}

template <typename T>
int string_map<T>::size() const{
    // COMPLETAR
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    // COMPLETAR
    return _size==0;
}

template <typename T>
bool string_map<T>::definida(string clave) const{
    // COMPLETAR
    return count(clave)==1;
}

template <typename T>
T* string_map<T>::definir(string clave, T significado){
    if (raiz == NULL){
      raiz = new Nodo;
    }
    Nodo* buscador = raiz;
    for(int i=0; i<clave.size() ;i++) {
      if(buscador->siguientes[int(clave[i])] == NULL){
          buscador->siguientes[int(clave[i])] = new Nodo;
        }
      buscador = buscador->siguientes[int(clave[i])];
    }
    if(buscador->definicion == NULL ){
          buscador->definicion = new T;
          _size ++;
    }
    *(buscador->definicion) = significado;
    return (buscador->definicion);
}

template <typename T>
Ventana<tuple<int, int>>* string_map<T>::definir_ventana(string clave, Ventana<tuple<int, int>> significado){
    if (raiz == NULL){
      raiz = new Nodo;
    }
    Nodo* buscador = raiz;
    for(int i=0; i<clave.size() ;i++) {
      if(buscador->siguientes[int(clave[i])] == NULL){
          buscador->siguientes[int(clave[i])] = new Nodo;
        }
      buscador = buscador->siguientes[int(clave[i])];
    }
    if(buscador->definicion == NULL ){
          buscador->definicion = new T(significado.tam());
          _size ++;
    }
    *(buscador->definicion) = significado;
    return (buscador->definicion);
}
