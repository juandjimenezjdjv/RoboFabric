#include "Robots.h"
#include "picking.h"

using namespace std;

int enteros2(string entero);
void PrimerHilo( string carpeta, ListaProductosAl * ProductosExistencias, ListaCliente * Clientes, ListaPedidos * PedidosPrioridad10, ListaPedidos * PedidosNo10,ListaPedidos * PedidosError);


void FuncionBalanceadorPicking (ListaPicking *Picking6,ListaPedidos *ParaAlisto,ListaPedidos *Alisto,ListaProductosAl * ProductosExistencias);
bool PickingPrendidos(ListaPicking * Picking6);
bool PickingDisponible(ListaPicking *Picking6, int TiempoDuracion, Pedido *_Pedido,ListaPedidos *_Alisto);
int TotalPorPedido(Pedido *PedidoActual,ListaProductosAl * ProductosExistencias );
void IniciarRoboPicking(ListaPicking * RoboPicking6);
int PickingFuction(string UbicacionAlmacen);

void FuncionBalanceadorPicking (ListaPicking *Picking6,ListaPedidos *ParaAlisto,ListaPedidos *Alistados,ListaProductosAl * ProductosExistencias){
	
	if (ParaAlisto -> primerNodo != NULL){
		
		bool bandera = false;
		
		if(PickingPrendidos(Picking6)){
		
			
			Pedido *PedidoActual = ParaAlisto -> Desencolar();
			
			int duracion = TotalPorPedido(PedidoActual,ProductosExistencias);
			
			bandera = PickingDisponible(Picking6,duracion,PedidoActual,Alistados);
			
			if (bandera == false){
				ParaAlisto -> Encolar(PedidoActual);
			}
					
		}
		
	}
		
}


bool PickingPrendidos(ListaPicking * Picking6){
	
	Picking *tmp = Picking6 -> primerNodo;
	
	while(tmp != NULL){
		
	if (tmp -> estaLibre == true && tmp -> estaApagado == false){
		
		return true;	
		
		}
		tmp = tmp -> siguiente;
	}

	return false;

}



bool PickingDisponible(ListaPicking *Picking6, int TiempoDuracion, Pedido *_Pedido,ListaPedidos *_Alisto){
	
	Picking *tmp = Picking6 -> primerNodo;
	
	while(tmp != NULL){
		
		if (tmp -> estaLibre == true && tmp -> estaApagado == false){
			
			//cout << "El robot de paking con el ID " << tmp -> id << " esta trabajando el pedido con el numero " << _Pedido -> numero << " y va a tener un tiempo de duracion aproximado a " << TiempoDuracion << endl;
			tmp -> estaLibre = false;
			tmp -> tiempo = TiempoDuracion;
			tmp -> pedido = _Pedido;
			tmp -> Alistados = _Alisto;
			_Pedido -> registroBitacora = _Pedido -> registroBitacora + "El robot de picking con el ID " + tmp -> id + " se encargara del pedido " + _Pedido -> numero + "\nInicio : " + obtenerFechaYHora() + "\n";
			tmp -> Reanudar();
			
			return true;
		}
		
		tmp = tmp -> siguiente;
	}
	return false;
}




int TotalPorPedido(Pedido *PedidoActual,ListaProductosAl * ProductosExistencias ){
	
	
	Producto *Productos = PedidoActual -> Productos -> primerNodo;
	int tiempototal = 0;
	int numerador = 1;
	if (Productos != NULL){
		
		PedidoActual -> registroBitacora = PedidoActual -> registroBitacora + "Calculando el tiempo por producto para el picking : \n" ; 
			
		while (Productos != NULL){
		
//		cout << "Se esta atendiendo el pedido con el numero " << PedidoActual -> numero << " especificamente el producto numero " << numerador << endl;
		ProductoAlmacen * ProductoEnAlmacen = ProductosExistencias -> BuscarProducto(Productos->Pcodigo);
		
// 		cout << "Y esta es la direcccion  del producto en el almacen " << ProductoEnAlmacen -> Ubicacion << endl;
		
		int ttt = PickingFuction(ProductoEnAlmacen -> Ubicacion);
		tiempototal += ttt;
		PedidoActual -> registroBitacora = PedidoActual -> registroBitacora + "Producto codigo : " + Productos -> Pcodigo + " esta en la ubicacion : " + ProductoEnAlmacen -> Ubicacion +"  " + to_string(ttt) + "segs\n";
		ttt = 0;
		numerador++;
		Productos = Productos -> siguiente;
	}
	
	}

	return tiempototal;
	
}

void IniciarRoboPicking(ListaPicking * RoboPicking6){
	
	for (int i = 1; i <= 6 ; i++){
	
		string tmp = to_string(i);
		RoboPicking6 -> Encolar(new Picking(tmp,true,false,1));	
	
	}
	
}



int PickingFuction(string UbicacionAlmacen){
	
	
	string Abecedario = "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";
//	string prueba = "M07";
	
	char letra = UbicacionAlmacen[0];
	char enterochar = UbicacionAlmacen[2];
	
//	char letra = prueba[0];
//	char enterochar = prueba[2];
	
	int numero = 1;
	int numeroABC = 0;
	bool bandera = true;

	int tiempo = 0;
	
	
//	cout << "La letra es " << letra << " y el numero es " << enterochar << endl;

	while (bandera){
		
		if ((enterochar - '0') == 0){
			
//			cout << "PRRR" << endl;
//			cout << "duro " << 10 << " segundos " << endl;
			tiempo = tiempo + 10;
			bandera = false;
			
		}else if (numero == (enterochar - '0')){
			
//			cout << "Entra" << endl;
//			cout << "duro " << numero << " segundos " << endl;
			tiempo = tiempo + numero;
			bandera = false;
			
		}
		numero++;
		
	}
	
	bandera = true;
	
	while (bandera){
		
		
		if (letra == Abecedario[numeroABC]){
			
			//cout << "Entro y tuvo concidencia con la letra " << letra << " con el abecedario en la letra " << Abecedario[numeroABC] << endl;
			tiempo = tiempo + numeroABC+1;
			bandera = false;
		}
		numeroABC++;
		
	}
	
	tiempo = tiempo * 2;
	//cout << "Duro unos " << tiempo << " segundos";
	
	return tiempo;
	
}
