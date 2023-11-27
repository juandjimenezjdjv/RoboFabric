#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <dirent.h>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include "Clientes.h"
#include "LeerPedidos.h"


 

using namespace std;

struct Robot;
struct ListaRobot;
string obtenerFechaYHora();

struct Robot{
	std::thread thread;
	std::string mensaje;
	std::atomic<bool> pausado;
	std::atomic<bool> terminar;
	std::mutex mutex;
	
	string nombreR;
	string tipo;//A,B,C o Todas
	bool prioridad;//Prioridad
	bool estaLibre;
	bool estaApagado;
	int cantidad;
	int tiempo;
	Robot* siguiente = NULL;
	
	Pedido *pedido;
	Producto *producto;
	ListaPedidos *almacen;
	
	string registro;
	
	Robot (string _nombreR, string _tipo, bool _prioridad, bool _estaLibre, bool _estaApagado, int _cantidad, int _tiempo)
	{
		nombreR = _nombreR;
		tipo = _tipo;
		prioridad = _prioridad; 
		estaLibre = _estaLibre;
		estaApagado = _estaApagado;
		cantidad = _cantidad;
		tiempo = _tiempo;
		string registro = "";
		
		Pedido *pedido = new Pedido();
		Producto *producto = new Producto();
		ListaPedidos *almacen = new ListaPedidos();
		
		pausado = true;
		thread = std::thread(&Robot::MiFuncion, this);
		terminar = false;
	}
//	
	
	void imprimir ()
	{
		cout <<" |" << nombreR << "  " << "  " << pedido -> numero << "  " << pedido -> Ccodigo <<  "|\n";
	}
	
//	Robot (const std::string& msg, Pedido *pedido,	Producto *producto,	ListaPedidos *almacen)//bool _estaLibre, 
//	: mensaje(msg), pedido (pedido), producto(producto), almacen(almacen), pausado(false), terminar(false){
//        // Iniciar el thread en el constructor
//        thread = std::thread(&Robot::MiFuncion, this);//-----------------------------------------
//    }
	
	
//	Robot (const std::string& msg, Pedido *pedido,	Producto *producto,	ListaPedidos *almacen)//bool _estaLibre, 
//	: mensaje(msg), pedido (pedido), producto(producto), almacen(almacen), pausado(false), terminar(false){
//        // Iniciar el thread en el constructor
//        thread = std::thread(&Robot::MiFuncion, this);//-----------------------------------------
//    }

    // Funci?n que ser? ejecutada por el thread
    void MiFuncion() {//ListaPedidos *Pedidostmp
    	
        while (!terminar) {
            {
                std::unique_lock<std::mutex> lock(mutex);
                while (pausado) {
                    // El thread est? en pausa, espera
                    lock.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    lock.lock();
                }
            }
//          cout << this->nombreR << endl;
//			cout << "Prueba" <<endl;
//          cout<< "hola\n\n"; 
//			tiempoDuracion = producto->cantidad;
            //Aqui funcion
//            tiempo = tiempo / 3;
            std::this_thread::sleep_for(std::chrono::seconds(tiempo));//tiempoDuracion
        
			if (pedido != NULL){
				string temp = "\n" + this -> nombreR + " Con categoria = " + this -> tipo + " Se esta encardo del pedido con numero -> " + pedido -> numero + " especificamente del producto = " + producto -> Pcodigo + "\n";
				cout << this -> nombreR << " esta encargando del pedido con numero -> " << pedido -> numero << endl;
				producto -> cantidad = 0;
				pedido -> registroBitacora = pedido -> registroBitacora + "Final : " + obtenerFechaYHora() +"\n"; 
				
				almacen -> registro = almacen -> registro +  pedido -> numero + "  " + pedido -> Ccodigo + "\n";
				almacen->Encolar(pedido);
				tiempo = 0;
				
				
				this -> registro = this -> registro + "\n" + temp;
				this -> pedido = NULL;
	         	this->estaLibre = true;
			}
			
			
            //Poner las variables en nulo y ademas poner en 
            //if (this->nombreR == "R4")
            this->Pausar();
            
        }
        
        std::cout << "Thread (" << mensaje << ") ha terminado." << std::endl;
    }
	
	
	 void Pausar() {
        pausado = true;
    }

    // Funci?n para reanudar el thread
    void Reanudar() {
        pausado = false;
    }

    // Funci?n para terminar el thread
    void Terminar() {
        terminar = true;
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Destructor
    ~Robot() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
	
};


struct ListaRobot { //Esta lista simple es solo para los clientes
       Robot *primerNodo, *ultimoNodo;
       ListaRobot(){
           primerNodo = ultimoNodo = NULL;
       }
        void insertarAlInicio (string _nombreR, string _tipo, bool _prioridad, bool _estaLibre, bool _estaApagado, int _cantidad, int _tiempo){
            if (primerNodo == NULL){
         		ultimoNodo = primerNodo = new Robot(_nombreR,  _tipo,  _prioridad,  _estaLibre,  _estaApagado,  _cantidad,  _tiempo);
       		}else{
         		Robot *nuevo = new Robot(_nombreR,  _tipo,  _prioridad,  _estaLibre,  _estaApagado,  _cantidad,  _tiempo);
         		nuevo->siguiente = primerNodo;
         		primerNodo = nuevo; 
      }
  }
        void imprimir(){
            Robot * tmp = primerNodo;
            while(tmp != NULL && tmp -> pedido != NULL){
                tmp->imprimir();
                tmp = tmp->siguiente;
            }
            cout<<endl;
        }
        
   void iniciarRobots(){
	Robot * tem = primerNodo;
	while (tem != NULL){
		if (tem->estaApagado == false){
//			cout << tem->nombreR << enld;
			tem->Reanudar();
		}else{
			tem->Pausar();
		}
		tem = tem->siguiente;
	}
}
        
	void MostrarRegisto(){
            Robot * tmp = primerNodo;
            int numerador = 9;
            while(tmp != NULL ){
            	
            	cout << "\n Robot numero -> " << numerador<< "******" << endl;;
                cout << tmp->registro;
                
                tmp = tmp->siguiente;
                numerador--;
            }
            cout<<endl;
        }
};





