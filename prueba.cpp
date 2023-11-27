 #include <iostream>
#include <fstream>
#include <string>
#include <cstring>
 #include <dirent.h>

using namespace std;

// Función para leer el contenido de un archivo y almacenarlo en un string
 string leerArchivo(const  string& ruta) {
     ifstream archivoEntrada(ruta.c_str());
     string contenido;
    if (archivoEntrada.is_open()) {
         string linea;
        while ( getline(archivoEntrada, linea)) {
            contenido += linea + '\n';  // Agregar el contenido de la línea al string
        }
        archivoEntrada.close();
    }
    return contenido;
}

int main() {
     string carpeta = "./Pedidoszzz";  // Reemplaza con la ruta de tu carpeta
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
                 string contenido = leerArchivo(rutaCompleta);
                contenidoTotal += contenido;
            }
        }
        closedir(directorio);
    } else {
         cerr << "No se pudo abrir la carpeta." <<  endl;
        return 1;
    }

    // Ahora contenidoTotal contiene el contenido de todos los archivos .txt en la carpeta
     cout << "Contenido total de los archivos .txt:\n" << contenidoTotal <<  endl;

    return 0;
}

