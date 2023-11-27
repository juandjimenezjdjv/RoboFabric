#include <iostream>
#include <string>//
#include <cstdlib>
#include "Clientes.h"
#include "structPedidos.h"
#include "Almacen.h"

using namespace std;

void ValidarYEncolarP( ListaProductosAl * ProductosExistencias, ListaCliente * Clientes, ListaPedidos * _Pedidos, ListaPedidos * PedidosPrioridad10, ListaPedidos * PedidosNo10,ListaPedidos * PedidosError);
ListaPedidos* ejecutar(string carpeta);
void PrimerHilo( string carpeta, ListaProductosAl * ProductosExistencias, ListaCliente * Clientes, ListaPedidos * PedidosPrioridad10, ListaPedidos * PedidosNo10,ListaPedidos * PedidosError);


void PrimerHilo( string carpeta, ListaProductosAl * ProductosExistencias, ListaCliente * Clientes, ListaPedidos * PedidosPrioridad10, ListaPedidos * PedidosNo10,ListaPedidos * PedidosError){

	ListaPedidos *Pedidostmp = ejecutar(carpeta);
	ValidarYEncolarP(ProductosExistencias,Clientes,Pedidostmp,PedidosPrioridad10,PedidosNo10,PedidosError);
	
}
