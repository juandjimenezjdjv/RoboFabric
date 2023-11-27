#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Almacen.h"


using namespace std;

int enteros2(string entero);

ListaProductosAl* LeerAlmacentxt(string nombreArchivo) {
	
    ListaProductosAl* ProductosAl = new ListaProductosAl();
    string codigo, cantidadStr, tiempoStr, categoriaStr, ubicacion;
    int cantidad, tiempo;
    char categoria;
    string respuesta;

    ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream stream(linea);
            
            getline(stream, codigo, '\t');
            getline(stream, cantidadStr, '\t');
            getline(stream, tiempoStr, '\t');
            getline(stream, categoriaStr, '\t');
            getline(stream, ubicacion, '\n');

            // Convierte las cadenas a los tipos de datos adecuados
            cantidad = enteros2(cantidadStr);
            tiempo =  enteros2( tiempoStr);
            categoria = categoriaStr[0];  // Solo toma el primer carácter

            //cout << "Dato 1: " << codigo << ", Dato 2: " << cantidad << ", Dato 3: " << tiempo
            //          << ", Dato 4: " << categoria << ", Dato 5: " << ubicacion << endl;
            
            if (categoria == 'A' || categoria == 'B' ||categoria == 'C' ){
            	if(cantidad >= 0){
            		ProductosAl->insertarAlInicio(codigo, cantidad, tiempo, categoria, ubicacion);
				}else{
					cerr << "No se agrego debido a las cantidad";	
				}
			}else {
				cerr << "No se agrego el Articulo con el codigo " << codigo << " debido a la categoria";
			}
            
        }

        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }

   return ProductosAl;
}

