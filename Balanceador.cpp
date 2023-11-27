#include <iostream>
#include <string>
#include <cstdlib>
//#include "structPedidos.h"
#include "Robots.h"
//#include "Almacen.h"

using namespace std;

Producto* ComprometerCantidad(ListaProductos * ProductosActuales, ListaProductosAl *ProductosExistencias );
void BalanceadorF(ListaPedidos *PedidosAlmacen, ListaPedidos *PrioridadEspecial, ListaPedidos *Prioridad10, ListaPedidos *PrioridadBaja,ListaProductosAl *ProductosExistencias, ListaPedidos *ParaAlisto,ListaRobot *Robots );
string obtenerFechaYHora();

bool RobotDisponible (ListaPedidos * AlmacenP, ListaRobot * LosRobots, string categoria, bool _prioridad, Pedido *_pedido,Producto *_producto, int tiempoduracion, int CantidadFaltante, string CodigoProducto);
// Lo que falta es hacer una funcion para iterar sobre los robots y ver si estan disponibles

// A los robots se les pasa un pedido(para encolarlo luego en la colaAlmacen)
// un producto para que actualice la cantidad
// Y la cantidad de tiempo que se va a tener que dormir el robot para 

void BalanceadorF(ListaPedidos *PedidosAlmacen, ListaPedidos *PrioridadEspecial, ListaPedidos *Prioridad10, ListaPedidos *PrioridadBaja,ListaProductosAl *ProductosExistencias, ListaPedidos *ParaAlisto,ListaRobot *Robots ){
	
	
	if(PedidosAlmacen -> primerNodo != NULL){
		
		Pedido *PedidoActual = PedidosAlmacen -> Desencolar();
		PedidoActual -> registroBitacora = PedidoActual -> registroBitacora + "Balanceador : " + obtenerFechaYHora() + "\n";
		
		Producto *ProductoPendiente = ComprometerCantidad(PedidoActual -> Productos,ProductosExistencias);
		
		if (ProductoPendiente != NULL){
				
			//Aqui se manda para el robot pasandole el pedido actual y el producto que falta con la cantidad ya modificada de lo que falta
			ProductoAlmacen * _ProductoEnAlmacen = ProductosExistencias->BuscarProducto(ProductoPendiente->Pcodigo);
			
			int duracion = _ProductoEnAlmacen -> tiempo * ProductoPendiente -> cantidad;
			
			bool bandera = RobotDisponible(PedidosAlmacen,Robots,_ProductoEnAlmacen->categoria,true,PedidoActual,ProductoPendiente,duracion,ProductoPendiente -> cantidad, ProductoPendiente -> Pcodigo);
			if (bandera == false){
				PedidosAlmacen -> Encolar(PedidoActual);
			}
 			
		}else{
			//Se encola en alisto
			PedidoActual -> registroBitacora = PedidoActual -> registroBitacora + "A cola de 'Para Alisto' : " + obtenerFechaYHora() + "\n";  
			ParaAlisto -> registro = ParaAlisto -> registro + PedidoActual -> numero + "  " + PedidoActual -> Ccodigo + "\n";
			ParaAlisto -> Encolar(PedidoActual);
		}
		
	}else if(PrioridadEspecial -> primerNodo != NULL){
		
		Pedido *PedidoActual = PrioridadEspecial -> Desencolar();
		PedidoActual -> registroBitacora = PedidoActual -> registroBitacora + "Balanceador : " + obtenerFechaYHora() + "\n";
		
		Producto *ProductoPendiente = ComprometerCantidad(PedidoActual -> Productos,ProductosExistencias);
		
		if (ProductoPendiente != NULL){
			//Aqui se manda para el robot pasandole el pedido actual y el producto que falta con la cantidad ya modificada de lo que falta
			ProductoAlmacen * _ProductoEnAlmacen = ProductosExistencias->BuscarProducto(ProductoPendiente->Pcodigo);
			int duracion = _ProductoEnAlmacen -> tiempo * ProductoPendiente -> cantidad;
			
			bool bandera = RobotDisponible(PedidosAlmacen,Robots,_ProductoEnAlmacen->categoria,true,PedidoActual,ProductoPendiente,duracion,ProductoPendiente -> cantidad, ProductoPendiente -> Pcodigo);
			if (bandera == false){
				PedidosAlmacen -> Encolar(PedidoActual);
			}
			
		}else{
			//Se encola en alisto
			PedidoActual -> registroBitacora = PedidoActual -> registroBitacora + "A cola de 'Para Alisto' : " + obtenerFechaYHora() + "\n"; 
			ParaAlisto -> registro = ParaAlisto -> registro + PedidoActual -> numero + "  " + PedidoActual -> Ccodigo + "\n";
			ParaAlisto -> Encolar(PedidoActual);
		}
		
	}else if(Prioridad10 -> primerNodo != NULL){
		
		Pedido *PedidoActual = Prioridad10 -> Desencolar();
		PedidoActual -> registroBitacora = PedidoActual -> registroBitacora + "Balanceador : " + obtenerFechaYHora() + "\n";
		
		Producto *ProductoPendiente = ComprometerCantidad(PedidoActual -> Productos,ProductosExistencias);
		
		if (ProductoPendiente != NULL){
			//Aqui se manda para el robot pasandole el pedido actual y el producto que falta con la cantidad ya modificada de lo que falta
			ProductoAlmacen * _ProductoEnAlmacen = ProductosExistencias->BuscarProducto(ProductoPendiente->Pcodigo);
			int duracion = _ProductoEnAlmacen -> tiempo * ProductoPendiente -> cantidad;
			
			bool bandera = RobotDisponible(PedidosAlmacen,Robots,_ProductoEnAlmacen->categoria,true,PedidoActual,ProductoPendiente,duracion,ProductoPendiente -> cantidad, ProductoPendiente -> Pcodigo);
			if (bandera == false){
				PedidosAlmacen -> Encolar(PedidoActual);
			} 			
		}else{
			//Se encola en alisto
			PedidoActual -> registroBitacora = PedidoActual -> registroBitacora + "A cola de 'Para Alisto' : " + obtenerFechaYHora() + "\n"; 
			ParaAlisto -> registro = ParaAlisto -> registro + PedidoActual -> numero + "  " + PedidoActual -> Ccodigo + "\n";
			ParaAlisto -> Encolar(PedidoActual);
		}
		
	}else if(PrioridadBaja -> primerNodo != NULL){
		
		Pedido *PedidoActual = PrioridadBaja -> Desencolar();
		PedidoActual -> registroBitacora = PedidoActual -> registroBitacora + "Balanceador : " + obtenerFechaYHora() + "\n";
		
		Producto *ProductoPendiente = ComprometerCantidad(PedidoActual -> Productos,ProductosExistencias);
		
		if (ProductoPendiente != NULL){
			//Aqui se manda para el robot pasandole el pedido actual y el producto que falta con la cantidad ya modificada de lo que falta
			ProductoAlmacen * _ProductoEnAlmacen = ProductosExistencias->BuscarProducto(ProductoPendiente->Pcodigo);
			int duracion = _ProductoEnAlmacen -> tiempo * ProductoPendiente -> cantidad;
			
			bool bandera = RobotDisponible(PedidosAlmacen,Robots,_ProductoEnAlmacen->categoria,true,PedidoActual,ProductoPendiente,duracion,ProductoPendiente -> cantidad, ProductoPendiente -> Pcodigo);
			if (bandera == false){
				PedidosAlmacen -> Encolar(PedidoActual);
			} 			
		}else{
			//Se encola en alisto
			PedidoActual -> registroBitacora = PedidoActual -> registroBitacora + "A cola de 'Para Alisto' : " + obtenerFechaYHora() + "\n";
			ParaAlisto -> registro = ParaAlisto -> registro + PedidoActual -> numero + "  " + PedidoActual -> Ccodigo + "\n";
			ParaAlisto -> Encolar(PedidoActual);
		}
		
	}
	
	
}

Producto* ComprometerCantidad(ListaProductos * ProductosActuales, ListaProductosAl *ProductosExistencias ){
	
	Producto *ProductoActual = ProductosActuales -> primerNodo;
	
	while(ProductoActual != NULL){
		
		ProductoAlmacen * ProductoAl = ProductosExistencias->BuscarProducto(ProductoActual->Pcodigo);
		int cantidadAlmacen = ProductoAl -> Cantidad;
		
		if ((cantidadAlmacen - ProductoActual -> cantidad) >= 0){
			ProductoAl -> Cantidad = (cantidadAlmacen - ProductoActual -> cantidad);
			ProductoActual -> cantidad = 0;
			
			
		}else if ((cantidadAlmacen - ProductoActual -> cantidad) < 0){
			
			ProductoActual -> cantidad = (ProductoActual -> cantidad - cantidadAlmacen);
			ProductoAl -> Cantidad = 0;
			
			return ProductoActual;
			
		}
			
		ProductoActual = ProductoActual -> siguiente;			
	}
	
	return ProductoActual;
}

bool RobotDisponible (ListaPedidos * AlmacenP, ListaRobot * LosRobots, string categoria, bool _prioridad, Pedido *_pedido,Producto *_producto, int tiempoduracion, int CantidadFaltante, string CodigoProducto){
	
	Robot *temp = LosRobots -> primerNodo;
	
	while(temp != NULL){
		
		if (temp->estaApagado == false && (temp->tipo == categoria || temp -> tipo == "todas") && temp->estaLibre == true && (temp->prioridad == _prioridad  || (temp -> prioridad == false && _prioridad == true))){
			
			temp -> estaLibre = false;
			temp -> pedido = _pedido;
			temp -> producto = _producto;
			temp -> tiempo = tiempoduracion;
			temp -> almacen = AlmacenP;
			_pedido -> registroBitacora = _pedido -> registroBitacora + "A robot fabrica " + temp -> nombreR + " : " + " Faltaban " + to_string(CantidadFaltante) + " unidades" + "\nInicio : " + obtenerFechaYHora() + "\n"; 
			temp -> Reanudar();
			//cout << "El robot " << temp -> nombreR << "Esta trabajando el pedido -> " << _pedido -> numero << endl;
			return true;	
		}
					
		temp = temp -> siguiente;
	}
	
	return false;
}




