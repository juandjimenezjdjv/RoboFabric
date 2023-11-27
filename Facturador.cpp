#include <iostream>
#include <string>
#include <cstdlib>
#include "Robots.h"
#include "Facturador.h"
#include <algorithm> 
#include <direct.h>  
#include <fstream>

using namespace std;

bool Prendido(ContenedorFacturador *Lazo);
bool facturadorDisponible (ListaPedidos * factura, Pedido *_pedido,Facturador *_Lazo);

string obtenerFechaYHora();

void FacturarF ( ListaPedidos *Factura,ContenedorFacturador *CLazo){
 
	
	
	if(Factura -> primerNodo != NULL){
		
		if (Prendido(CLazo)){
			
			Facturador * Lazo = CLazo -> primerNodo;
			Pedido *PedidoActual = Factura -> Desencolar();	
 			PedidoActual -> registroBitacora = PedidoActual -> registroBitacora + "En Factura : " + obtenerFechaYHora() + "\n";
//			cout << "Estes es el tiempo: " << tiempo << endl;
//			cout << "Este es el lazo -> tiempo: " << Lazo -> tiempo  << endl;
//			Lazo -> tiempo = tiempo;
//			cout << Lazo -> tiempo << "Este es el lazo -> tiempo" << endl;
			
			bool bandera = facturadorDisponible(Factura,PedidoActual,Lazo);
				if (bandera == false){
					Factura -> Encolar(PedidoActual);
//					cout << "No estaba disponible el facturador " << endl;
			}
		}	
	}

}

void IniciarFacturadorE(ContenedorFacturador *Lazo){
	
	Lazo -> Encolar("FacturadorOficial",true,false);
//	Lazo -> primerNodo -> imprimir();
	 	
}

bool Prendido(ContenedorFacturador *Lazo){
	
	Facturador *tmp = Lazo -> primerNodo;
	
	if(tmp -> estaApagado == false && tmp -> estaLibre == true){
		return true;
	}else{
		return false;
	}
	
}

bool facturadorDisponible (ListaPedidos * factura, Pedido *_pedido,Facturador *_Lazo){
	
 
	if (_Lazo->estaApagado == false && _Lazo->estaLibre == true){
			
//			_Lazo -> imprimir();
//			cout << _Lazo -> tiempo << endl; //AQUI IMpRime un resultado negativo	
//			cout << _Lazo -> pedido << endl;
//			cout << _Lazo -> Factura << endl;
			_Lazo -> estaLibre = false;
//			cout << "Mmmzzzzzzzmm";
			_Lazo -> pedido = _pedido;
//			cout << "Mmmmssssssssssssm";
//			_Lazo -> tiempo = tiempoduracion;
//			cout << "Mmffffffffffffmmm";
//			cout << "El empacador esta trabajando el pedido numero " << _pedido -> numero << " durara estos segundos " << tiempoduracion << endl;
//			cout << "Se mando a imprimir " << endl;
			_Lazo -> Reanudar();
//			cout << "aaa";
			return true;	
	}else{
		
		return false;
	
	}
	return false;

}


void crearArchivo(const std::string& carpeta, const std::string& nombreArchivo, const std::string& contenido) {
    // Combinar la carpeta y el nombre del archivo para obtener la ruta completa
    std::string rutaCompleta = carpeta + "/" + nombreArchivo;
//
//	_mkdir(rutaCompleta.c_str());

    // Crear un objeto de flujo de salida para escribir en el archivo
//    ofstream archivoSalida(nombreArchivo.c_str());
	ofstream archivo("ABitacora/"+nombreArchivo);

    // Verificar si el archivo se abrió correctamente
    if (archivo.is_open()) {
        // Escribir el contenido en el archivo
        archivo << contenido;

        // Cerrar el archivo
        archivo.close();

//        std::cout << "Archivo creado exitosamente en: " << rutaCompleta << std::endl;
    } else {
        std::cerr << "Error al abrir el archivo: " << rutaCompleta << std::endl;
    }
}

void BitacoraMovimiento(Pedido *_Pedido) {
    // Ejemplo de uso
     string carpeta = "ABitacora";
     string nombreArchivo = _Pedido->numero + "_" + _Pedido->Ccodigo + " " + obtenerFechaYHora() + ".txt";
//    replace_if(nombreArchivo.begin(), nombreArchivo.end(), [](char c) { return std::isspace(c) || c == ':'; }, '_');  // Reemplazar espacios y ':' por '_'
     string contenido = _Pedido->registroBitacora;
    
    crearArchivo(carpeta, nombreArchivo, contenido);
}


