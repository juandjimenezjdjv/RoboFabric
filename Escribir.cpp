#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <direct.h> // Para _mkdir en sistemas Windows
#include "structPedidos.h"

using namespace std;


string convertirDatoAbstractoAString(Pedido* PedidoRR);
string obtenerNombreUnico();
void crearArchivoEnCarpeta(const string& nombreCarpeta, const string& contenido,string Cnombre,string Ccodigo);
void EscribirError(Pedido* PedidoEx,string nombreCarpeta,string Ccliente, string Ccodigo);


// Función para obtener un nombre de archivo único
//string obtenerNombreUnico() {
//    time_t tiempoActual = time(nullptr);
//    return to_string(tiempoActual);
//}

// Función para crear un archivo en una carpeta con un contenido dado
void crearArchivoEnCarpeta(const string& nombreCarpeta, const string& contenido,string Cnombre,string Ccodigo) {
    // Obtener la ruta completa de la carpeta
    string rutaCarpeta = "./" + nombreCarpeta;

    // Crear la carpeta si no existe
    _mkdir(rutaCarpeta.c_str());

    // Generar un nombre único para el archivo
    string nombreArchivo = rutaCarpeta + "/archivo_" + Cnombre + "_" + Ccodigo + ".txt";

    // Abrir el archivo en modo de escritura
    ofstream archivo(nombreArchivo.c_str());

    if (archivo.is_open()) {
        // Escribir el contenido en el archivo
        archivo << contenido;
        archivo.close();

        //cout << "Archivo creado exitosamente: " << nombreArchivo << endl;
    } else {
        cerr << "Error al abrir el archivo para escritura." << endl;
    }
}

void EscribirError(Pedido* PedidoEx,string nombreCarpeta,string Ccliente, string Ccodigo) {
    // Uso de la función
    //string nombreCarpeta = "Errores";
    string contenido = convertirDatoAbstractoAString(PedidoEx);

    crearArchivoEnCarpeta(nombreCarpeta, contenido,Ccliente,Ccodigo);
}

// Resto del código (convertirDatoAbstractoAString) sigue siendo el mismo




// Función para convertir un dato abstracto a un string formateado
string convertirDatoAbstractoAString(Pedido* PedidoRR) {
    ostringstream resultado;

    // Primera línea: número
    resultado << PedidoRR->numero << "\n";

    // Segunda línea: código
    resultado << PedidoRR->Ccodigo << "\n";

    // Resto de las líneas: código y cantidad de la sublista
    Producto* temp = PedidoRR -> Productos -> primerNodo;
    while (temp != NULL) {
        resultado << temp->Pcodigo << "\t" << temp->cantidad << "\n";
        temp = temp->siguiente;  // Supongo que 'siguiente' es el puntero al siguiente elemento en la sublista
    }

	resultado << PedidoRR -> registroBitacora;
	
    return resultado.str();
}


