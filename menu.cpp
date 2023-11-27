#include <iostream>
#include <cstdlib>
#include <string>
#include "Balanceador.h"
#include "picking.h"
#include "empacador.h"
#include "Facturador.h"
//#include "Clientes.h"
//#include "structPedidos.h"
//#include "LeerPedidos.h"

using namespace std;

int enteros();
ListaCliente* leerClientes(string archivo);
void AddClientes(ListaCliente *ListaClientes);
ListaProductosAl* LeerAlmacentxt(string nombreArchivo);
int correr (ListaRobot *Robots);
void PrimerHilo( string carpeta, ListaProductosAl * ProductosExistencias, ListaCliente * Clientes, ListaPedidos * PedidosPrioridad10, ListaPedidos * PedidosNo10,ListaPedidos * PedidosError);
void IniciarRoboPicking(ListaPicking * RoboPicking6);
void FuncionBalanceadorPicking (ListaPicking *Picking6,ListaPedidos *ParaAlisto,ListaPedidos *Alistados,ListaProductosAl * ProductosExistencias);
void empacadorF (ListaPedidos * Alistados, ListaPedidos *Facturar,empacador *Lazo);
void IniciarContenedorE(ContenedorEmpacador *Lazo);
void IniciarFacturadorE(ContenedorFacturador *Lazo);

void robotEnceApa(ListaRobot * robots);
void robotdemas(ListaPicking * Pickings, ContenedorEmpacador *emp, ContenedorFacturador * fact);
int encendidobalan ();


void menu () {
	
	
	//ListaCliente *ListaClientes = leerClientes("Clientes.txt");
	int opcion= -1;
	int cont = 0;
	int apBala = 0;
	
	ContenedorFacturador *FLazo = new ContenedorFacturador();
    IniciarFacturadorE(FLazo);
	
	
	ListaRobot *robots = new ListaRobot();
    correr (robots);
    robots->iniciarRobots();
    
    ContenedorEmpacador *Lazo = new ContenedorEmpacador();
    IniciarContenedorE(Lazo);
	
	ListaPicking * Picking6 = new ListaPicking();
	IniciarRoboPicking(Picking6);
	
	ListaProductosAl * Productos = LeerAlmacentxt("Almacen.txt");
	ListaCliente *Clientes = leerClientes("Clientes.txt");
	
	ListaPedidos * PedidosAlmacen = new ListaPedidos();
	ListaPedidos * PrioridadEspecial = new ListaPedidos();
	ListaPedidos * PedidosPrioridad10 = new ListaPedidos(); // Pedidos de prioridad 10
	ListaPedidos * PedidosNo10 = new ListaPedidos();//Pedidos de prioridad menor a 10
	ListaPedidos * PedidosError = new ListaPedidos();
	
	ListaPedidos * ParaAlisto = new ListaPedidos();
	ListaPedidos * Alistados = new ListaPedidos();
	ListaPedidos * Factura = new ListaPedidos();
	
	Pedido *Postiso = new Pedido();
	

	
	MyThread HiloPedidos("Hilo Pedidos","./Pedidoszzz",Productos,Clientes,PedidosPrioridad10,PedidosNo10,PedidosError);
	HiloPedidos.Reanudar();
	
	BalanceadorH BalanceadorOficial("Hilo del Balanceador",Productos, PedidosAlmacen,PrioridadEspecial,PedidosPrioridad10,PedidosNo10,ParaAlisto,robots,"");
	BalanceadorOficial.Reanudar();
	
	BalanceadorPicking _BalanceadorP66("Hilo para coordinar los 6 picking robots",ParaAlisto,Alistados,Picking6,Productos);
	_BalanceadorP66.Reanudar();
	
	HiloEmpacador HiloEmpacadorOficial("Hilo del empacador",Alistados,Factura,Lazo);
	HiloEmpacadorOficial.Reanudar();

	HiloFacturador HiloFacturadorOficial("Hilo del Facturador",Factura,FLazo);
	HiloFacturadorOficial.Reanudar();
	
	//Lo que sigue es hacer las pruebas necesarias y ver si esta funcionando bien y aparte empezar con la matriz corregir linea 40
	
	do{
		cout << "ROBOFABRIC" << endl;
		cout << "\t.:Menu:." << endl;
		cout << "  1. Imprimir Clientes" << endl;
		cout << "  2. Agregar Cliente" << endl;
		cout << "  3. Imprimir Almacen" << endl;
		cout << "  4. Mostrar los registros de los robots fabricantes" << endl;
		cout << "  5. Mostrar los registros de los robots picking" << endl;
		cout << "  6. Mostrar registro del empacador" << endl;
		cout << "  7. Mostrar registro del facturador" << endl;
		cout << "  8. Registro de colas de Pedidos iniciales" << endl;
		cout << "  9. Registro de cola de Almacen" << endl;
		cout << "  10. Registro de cola de ParaAlisto" << endl;
		cout << "  11. Registro de cola de Alistados" << endl;
		
		
		cout << "  12. Manejo de Robots. " << endl;
		cout << "  13. Manejo de Picking, Facturador y Empacador. " << endl;
		cout << "  14. Manejo del Balanceador. " << endl;
		
		cout << "  15.  Mostrar informacion actual de colas." << endl;
		cout << "  16. Salir. " << endl;
		cout << "Digite la opcion deseada: ";

		opcion = enteros();
		if (opcion == -1) {
			cout << "Digite un numero correcto." << endl;
			system("pause");
		}
		
		switch(opcion){
			case 1:
				cout << "Los clientes en lista son:" << endl;
				Clientes->imprimir();
				cout<<"\n";
				system("pause");
				break;
				
			case 2:
				AddClientes(Clientes);
				cout<<"\n";
				system("pause");
				break;
				
			case 3:
				cout << "\nProductos\n";
				Productos -> imprimir();
				cout<<"\n";
				system("pause");
				break;

			case 4:
				robots -> MostrarRegisto();
				cout<<"\n";
				system("pause");
				break;
				
			case 5:
				Picking6 -> MostrarRegisto();
				cout<<"\n";
				system("pause");
				break;
				
			case 6:
				cout << Lazo -> primerNodo -> registro;
				cout<<"\n";
				system("pause");
				break;
				
			case 7:
				cout << FLazo -> primerNodo -> registro;
				cout<<"\n";
				system("pause");
				break;
				
			case 8://pedidos iniciales
				cout <<  "PEDIDOS PRIORIDAD NOMARL \n" << PedidosNo10-> registro;
				cout <<  "PEDIDOS PRIORIDAD 10 \n"<< PedidosPrioridad10 -> registro;
				cout <<  "PEDIDOS PRIORIDAD ESPECIAL \n"<< PrioridadEspecial -> registro;
				cout<<"\n";
				system("pause");
				break;
				
			case 9://alamcen
				cout << PedidosAlmacen -> registro;
				cout<<"\n";
				system("pause");
				break;
				
			case 10://para listo
				cout << ParaAlisto -> registro;
				cout<<"\n";
				system("pause");
				break;
			
			case 11://alistados
				cout << Alistados -> registro;
				cout<<"\n";
				system("pause");
				break;
				
			case 12:
				robotEnceApa(robots);
				cout<< "\n";
				
				system("pause");
				break;
				
			case 13:
				robotdemas(Picking6, Lazo, FLazo);
				cout<<"\n";
				system("pause");
				break;
		
			case 14:
				apBala = encendidobalan();
				if (BalanceadorOficial.pausado == false){
					if (apBala == 1){
						BalanceadorOficial.Pausar();
						cout << "Se pauso el balanceador." << endl;
					}else cout << "Ya esta encendido." << endl;;
				}else {
					if (apBala == 2){
						BalanceadorOficial.Reanudar();
						cout << "Se reanudo el balanceador." << endl;
					}else cout << "Ya esta apagado." << endl;;
				}
				cout<<"\n";
				system("pause");
				break;
		
			case 15:
					
				cout << "\nPEDIDOS CON ERRORES**** \n";
				PedidosError -> imprimir();			
				
				cout << "\nPEDIDOS PRIORIDAD NORMAL****\n";
				PedidosNo10 -> imprimir();
				
				cout << "\nPEDIDOS PRIORIDAD 10 *****\n";
				PedidosPrioridad10 -> imprimir();
				
				cout << "\nPEDIDOS PRIORIDAD ESPECIAL *****\n";
				PrioridadEspecial -> imprimir();
				
				cout << "\nPEDIDOS DEL ALMACEN****\n";
				PedidosAlmacen -> imprimir();
				
				cout << "\n PEDIDOS PARALISTO **** \n";
				ParaAlisto -> imprimir();
				
				cout << "\n PEDIDOS DE ALISTO ***** \n";
				Alistados -> imprimir();
				
				cout << "\n PEDIDOS PARA FACTURA ***** \n";
				Factura -> imprimir();
				
				cout<<"\n";
				system("pause");
				break;
				
			case 16:
				cout<<"\n";
				system("pause");
				break;
			
		}
		system("cls");
	}while(opcion != 16);
}
int encendidobalan (){
	bool ciclos = true;
	
	int interruptor = 0;
	cout << "Digite un numero para apagar(1) o encender(2): " << endl;
	interruptor = enteros();
	ciclos = true;
	while (ciclos){
		if (interruptor == 1 || interruptor == 2){
			ciclos = false;
		}else{
			cout << "Error" << endl;
			cout << "Digite un numero correcto para apagar(1) o encender(2): " << endl;
			interruptor = enteros();
		}
	}
	return interruptor;
}

