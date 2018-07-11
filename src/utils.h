#ifndef UTILS_H_
#define UTILS_H_

#include<vector>
#include<set>

using namespace std;

typedef int operacion;

const operacion PUSH = 1;
const operacion ADD = 2;
const operacion SUB = 3;
const operacion MULT = 4;
const operacion WRITE = 5;
const operacion READ = 6;
const operacion JUMP = 7;
const operacion JUMPZ = 8;

/*
template <typename T>
using set = typename set<T>;

template <typename T>
typedef T* T*;

template <typename T>
typedef string_map<T> string_map<T>;

template <typename T>
typedef vector<T> vector<T>;
*/

//typedef int operacion;

typedef string variable;

typedef string rutina;
#endif //UTILS_H_
