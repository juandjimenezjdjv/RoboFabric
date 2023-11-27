#include <fstream>
#include <string>
#include <cstring>
#include <dirent.h>
#include <sstream>
#include "Robots.h"

using namespace std;


int enteros2(string entrada);

string Archivo(const  string& ruta, ListaRobot *Robots) {
     ifstream archivoEntrada(ruta.c_str());
     string contenido;
    if (archivoEntrada.is_open()) {
    	
    	string linea, nombreR, tipo;
		bool prioridad, estaLibre, estaApagado;
		int cantidad, tiempo;
        int contador = 0;
         
         
         
        while ( getline(archivoEntrada, linea)) {
			if (contador == 0)
				nombreR = linea;
			else if(contador == 1)
				tipo = linea;
			else if(contador == 2){
				if (linea == "false"){
					prioridad = false;
				}else{
					prioridad = true;
				}
			}
			else if(contador == 3){
				if (linea == "false"){
					estaLibre = false;
				}else{
					estaLibre = true;
				}
			}
			else if(contador == 4){
				if (linea == "false"){
					estaApagado = false;
				}else{
					estaApagado = true;
				}
			}
			else if(contador == 5)
				cantidad = enteros2(linea);
			else if(contador == 6)
				tiempo = enteros2(linea);
				
			contador++;
//	            contenido += linea + '\n';  // Agregar el contenido de la l?nea al string
        }
        
        
        
//        	cout << " |" << nombreR << "  " << tipo <<  "  "  << prioridad <<  "  "  << estaLibre <<  "  "  << cantidad << "  "  << tiempo << "|\n";
        Robots->insertarAlInicio(nombreR, tipo, prioridad, estaLibre, estaApagado, cantidad, tiempo);
        archivoEntrada.close();
    }
    return contenido;
}

int correr (ListaRobot *Robots) {
     string carpeta = "./Robots";   
     string contenidoTotal;

    DIR* directorio;
    struct dirent* archivoEntrada;

    if ((directorio = opendir(carpeta.c_str())) != NULL) {
        while ((archivoEntrada = readdir(directorio)) != NULL) {
             string nombreArchivo = archivoEntrada->d_name;
            if (nombreArchivo.size() >= 4 &&
                nombreArchivo.substr(nombreArchivo.size() - 4) == ".txt") {
                // Construye la ruta completa del archivo
                 string rutaCompleta = carpeta + "/" + nombreArchivo;
//	                 cout << nombreArchivo << endl;
                 string contenido = Archivo(rutaCompleta,Robots);
                 
                contenidoTotal += contenido;
            }
        }
        closedir(directorio);
    } else {
         cerr << "No se pudo abrir la carpeta." <<  endl;
        return 1;
    }
     
//     cout << "\n\n\n" << "Ahora se mostrara la lista de pedidos en memoria\n";
//     cout << "Aqui acaba la lista en memoria" << endl;
	return 0;
}

//void iniciarRobots(ListaRobot * robots){
//	Robot * tem = ListaRobot->primerNodo;
//	while (tem != NULL){
//		
//		
//		
//		
//		tem = tem->siguiente;
//	}
//}



