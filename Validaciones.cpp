#include <cstdlib>
#include <iostream>
#include <string>
#include "Almacen.h"
#include "structPedidos.h"
#include "Clientes.h"

using namespace std;

bool ValidarCliente(string ClienteCodigo,ListaCliente * Clientes);
bool ValidarProducto(string ProductoCodigo, ListaProductosAl * ProductosExistencias);
void ValidarYEncolarP( ListaProductosAl * ProductosExistencias, ListaCliente * Clientes, ListaPedidos * _Pedidos, ListaPedidos * PedidosPrioridad10, ListaPedidos * PedidosNo10,ListaPedidos * PedidosError);
void EscribirError(Pedido* PedidoEx,string nombreCarpeta,string Ccliente, string Ccodigo);
int enteros();
int enteros2(string entero);
string obtenerFechaYHora();

//Valida que un producto exista 
bool ValidarProducto(string ProductoCodigo, ListaProductosAl * ProductosExistencias){
	
	ProductoAlmacen * tmp = ProductosExistencias -> primerNodo;
	bool Existe = false;
	
	while(tmp != NULL){
		
		if(tmp -> codigo == ProductoCodigo){
			Existe = true;
			break;
		}
		tmp = tmp -> siguiente;
	}
	return Existe;
	
}

// Valida que el cliente exista 
bool ValidarCliente(string ClienteCodigo,ListaCliente * Clientes){
	
	Cliente *tmp = Clientes -> primerNodo;
	bool Existe = false;
	
	while (tmp != NULL){
			
			if(tmp -> Ccodigo == ClienteCodigo){
				Existe = true;
				break;
			}
			tmp = tmp -> siguiente;
	}
	return Existe;
	
}


//Valida que exista el cliente
// Que existan todos los productos
// Lo agrega a las carpetas
//Lo hace con la cola entrante y da como resultado 3 colas de pedidos, una de prioridad otra normal y otra con errores

void ValidarYEncolarP( ListaProductosAl * ProductosExistencias, ListaCliente * Clientes, ListaPedidos * _Pedidos, ListaPedidos * PedidosPrioridad10, ListaPedidos * PedidosNo10,ListaPedidos * PedidosError){
	
	
	Pedido *tmp = _Pedidos -> primerNodo;
	bool ExisteC = false;
	bool ExistenP = false;
	int n = 0;
 
	
	while (tmp != NULL){
 
 		tmp = tmp -> siguiente;
		Pedido *nuevo = _Pedidos -> Desencolar();
		
		//DESENCOLARLO DE PEDIDOS PARA DEJARLO LISTO
		
		if (ValidarCliente(nuevo->Ccodigo,Clientes)){
			//cout << "exite el cliente";
			Producto *temp = nuevo -> Productos -> primerNodo;
			Cliente *Clientet = Clientes -> BuscarCliente(nuevo->Ccodigo);
			int tamano = nuevo -> Productos -> largo();
			int contador = 0;
			
			while (temp != NULL){
 
 				if(ValidarProducto(temp -> Pcodigo,ProductosExistencias) && temp -> cantidad >= 1 ){
					contador++;
				}
				temp = temp -> siguiente;
			}
			int _contador = contador;
			contador = 0;
			if(tamano == _contador ){//|| tamano != contador
				
				string Rtemp = "EL pedido " + nuevo -> numero + "  " + nuevo -> Ccodigo + "\n";
				
				if (Clientet -> prioridad >= 10){
					nuevo -> registroBitacora = nuevo -> registroBitacora + "Pedido : " + nuevo -> numero + "\n" + "Cliente : " + nuevo -> Ccodigo +"\n" +  "En cola : " + obtenerFechaYHora() + "\n" ;
					PedidosPrioridad10 -> registro = PedidosPrioridad10 -> registro + Rtemp;
					PedidosPrioridad10-> Encolar(nuevo);
					EscribirError(nuevo,"Procesados",Clientet->Cnombre,Clientet->Ccodigo);
					//cout << Clientet -> prioridad << "Entra";
 				}else if (Clientet -> prioridad >= 0){
 					nuevo -> registroBitacora = nuevo -> registroBitacora + "Pedido : " + nuevo -> numero + "\n" + "Cliente : " + nuevo -> Ccodigo +"\n" + "En cola : " + obtenerFechaYHora() + "\n";
 					PedidosNo10 -> registro = PedidosNo10 -> registro + Rtemp;
					PedidosNo10 -> Encolar(nuevo);
					EscribirError(nuevo,"Procesados",Clientet->Cnombre,Clientet->Ccodigo);
				}	 
			}else{
				//cout << "No existe algun o algunos pedidos" << _contador;
				nuevo -> registroBitacora = "\n Hubo un error con la existencia o la cantidad de algun o algunos productos\n";

				PedidosError -> Encolar(nuevo);
				EscribirError(nuevo,"Errores",Clientet -> Cnombre,Clientet -> Ccodigo);
				
				//nuevo -> imprimir();
			}
		}else{
				//cout << "No existe el cliente";
				
				nuevo -> registroBitacora = "\nHubo un error con la existencia del cliente\n";
				PedidosError -> Encolar(nuevo);
				EscribirError(nuevo,"Errores",nuevo->numero,nuevo->Ccodigo);
				//NO ENTRAAA Y SE BORRA DE LA CARPETA y entra a errores
		}	
	}		
}


//*******************************************************************************
//PASAN DE STRING A ENTEROS
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

