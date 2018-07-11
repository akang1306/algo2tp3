#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include "utils.h"
#include "Ventana.h"

using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    operator[]
    * Acceso o definición de pares clave/valor
    **/

    T &operator[](const string &key);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string &key) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& at(const string& key) const;
    T& at(const string& key);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& key);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;

    T* definir(string palabra, T significado);
    Ventana<tuple<int, int>>* definir_ventana(string clave, Ventana<tuple<int, int>> significado);
    bool definida(string clave) const;


private:


    struct Nodo {
        Nodo** siguientes;
        T* definicion;
        Nodo();
    };
    Nodo* raiz;
    int _size;

    void destructor_recursivo(Nodo* p);
    void iguales_recursivo( Nodo* p1, const Nodo* p2);
};

#include "string_map.hpp"

#endif // STRING_MAP_H_
