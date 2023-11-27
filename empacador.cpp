#include <iostream>
#include <string>
#include <cstdlib>
#include "Robots.h"
#include "empacador.h"

using namespace std;


bool empacadorDisponible (ListaPedidos * factura, Pedido *_pedido, int tiempoduracion,Empacador *_Lazo);
void empacadorF (ListaPedidos * Alistados, ListaPedidos *Factura,ContenedorEmpacador *CLazo);
bool Prendido(ContenedorEmpacador *Lazo);
void IniciarContenedorE(ContenedorEmpacador *Lazo);

void empacadorF (ListaPedidos * Alistados, ListaPedidos *Factura,ContenedorEmpacador *CLazo){
	int tiempo = 0;
	
	
	if(Alistados -> primerNodo != NULL){
		
		if (Prendido(CLazo)){
			
			Empacador * Lazo = CLazo -> primerNodo;
			Pedido *PedidoActual = Alistados -> Desencolar();	
			tiempo = PedidoActual -> Productos -> largo();
//			cout << "Estes es el tiempo: " << tiempo << endl;
//			cout << "Este es el lazo -> tiempo: " << Lazo -> tiempo  << endl;
//			Lazo -> tiempo = tiempo;
//			cout << Lazo -> tiempo << "Este es el lazo -> tiempo" << endl;
			bool bandera = empacadorDisponible(Factura,PedidoActual,tiempo,Lazo);
				if (bandera == false){
					Factura -> Encolar(PedidoActual);
					cout << "En teoria encolo." << endl;
				}
			}
 		
			
		}

}

void IniciarContenedorE(ContenedorEmpacador *Lazo){
	
	Lazo -> Encolar("EmpacadorOficial",true,false,1);
	//Lazo -> primerNodo -> imprimir();
	 	
}

bool Prendido(ContenedorEmpacador *Lazo){
	
	Empacador *tmp = Lazo -> primerNodo;
	
	if(tmp -> estaApagado == false && tmp -> estaLibre == true){
		return true;
	}else{
		return false;
	}
	
}

bool empacadorDisponible (ListaPedidos * factura, Pedido *_pedido, int tiempoduracion,Empacador *_Lazo){
	
//	cout << tiempoduracion << endl;
	if (_Lazo->estaApagado == false && _Lazo->estaLibre == true){
			
//			_Lazo -> imprimir();
//			cout << _Lazo -> tiempo << endl; //AQUI IMpRime un resultado negativo	
//			cout << _Lazo -> pedido << endl;
//			cout << _Lazo -> Factura << endl;
			_Lazo -> estaLibre = false;
			_pedido -> registroBitacora = _pedido -> registroBitacora + "En empacador : " + obtenerFechaYHora() + "\nDurara " + to_string(tiempoduracion) + " segs" + "\n";
//			cout << "Mmmzzzzzzzmm";
			_Lazo -> pedido = _pedido;
//			cout << "Mmmmssssssssssssm";
			_Lazo -> tiempo = tiempoduracion;
//			cout << "Mmffffffffffffmmm";
			_Lazo -> Factura = factura;
		//	cout << "El empacador esta trabajando el pedido numero " << _pedido -> numero << " durara estos segundos " << tiempoduracion << endl;
			_Lazo -> Reanudar();
			//cout << "aaa";
			return true;	
	}else{
		
		return false;
	
	}
	return false;

}
