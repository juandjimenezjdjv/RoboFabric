#include <iostream>
#include <cstdlib>
#include <string>
#include "Clientes.h"

using namespace std;

int enteros(){
    string entrada;
    int numero;
    cin >> entrada;
    char* endptr;
    numero = strtol(entrada.c_str(), &endptr, 10);
    if (*endptr == '\0' && entrada != "") {
        return numero;
    } else {
        return -1;
    }
    return -1;
}

int enteros2(string entero){
     int numero;
     char* endptr;
    numero = strtol(entero.c_str(), &endptr, 10);
    if (*endptr == '\0' && entero != "") {
        return numero;
    } else {
        return -1;
    }
    return -1;
}
