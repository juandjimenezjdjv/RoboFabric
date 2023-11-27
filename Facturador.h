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

using namespace std;


struct empacador;
struct ContenedorFacturador;
struct HiloEmpacador;

void FacturarF ( ListaPedidos *Factura,ContenedorFacturador *CLazo);
void BitacoraMovimiento(Pedido *_Pedido);
 

struct HiloFacturador {
    std::thread thread; // El objeto thread
    std::string mensaje; // Mensaje que el thread imprimir?
    std::atomic<bool> pausado; // Variable de control para pausar el thread
    std::atomic<bool> terminar; // Variable de control para terminar el thread
    std::mutex mutex; // Mutex para la sincronizaci?n de pausa/reanudaci?n
 
    ListaPedidos *Factura;
    ContenedorFacturador *Lazo;
     
		
    // Constructor
    HiloFacturador(const std::string& msg,ListaPedidos *Factura, ContenedorFacturador *Lazo)
	 : mensaje(msg), pausado(true), terminar(false), Factura(Factura),Lazo(Lazo){
        // Iniciar el thread en el constructor
        thread = std::thread(&HiloFacturador::MiFuncion, this);//-----------------------------------------
    }

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

            //Aqui funcion
            //PrimerHilo(carpeta,ProductosExistencias,Clientes,PedidosPrioridad10,PedidosNo10,PedidosError);
//            cout << "Corriendo la funcion para el empacador " << endl ;
            FacturarF( Factura, Lazo);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "Thread (" << mensaje << ") ha terminado." << std::endl;
    }

    // Funci?n para pausar el thread
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
    ~HiloFacturador() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};



struct Facturador{
	std::thread thread;
	std::string mensaje;
	std::atomic<bool> pausado;
	std::atomic<bool> terminar;
	std::mutex mutex;
	
	string id;
	bool estaLibre;
	bool estaApagado;
	int tiempo;
	Facturador* siguiente = NULL;
	
	Pedido *pedido;
 	ListaPedidos *Factura;
 	string registro;
	
	Facturador (string _id,bool _estaLibre, bool _estaApagado)
	{
		id = _id;
		estaLibre = _estaLibre;
		estaApagado = _estaApagado; 
		Pedido *pedido = new Pedido();
		registro = "";
		
		pausado = true;
		thread = std::thread(&Facturador::MiFuncion, this);
		terminar = false;
		
	}
	
	void imprimir ()
	{
		cout <<" |" << id << "  " << pedido -> numero << "  " << pedido -> Ccodigo <<  "|\n";
	}
	
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
//            cout << tiempo << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));//tiempoDuracion
        
			if (pedido != NULL){
				string temp = "\nEl facturador " + this -> id +  " esta encardo del pedido con numero -> " + pedido -> numero + "\n";
				cout << this -> id << " esta encargando del pedido con numero -> " << pedido -> numero << endl;
				
				this -> registro = this -> registro + pedido -> numero + "  " + pedido -> Ccodigo + "\n";	
				pedido->registroBitacora = pedido->registroBitacora + "Finalizado : " + obtenerFechaYHora() + "\n";
				BitacoraMovimiento(pedido);
	         	this->estaLibre = true;
	         	this -> pedido = NULL;
			}
			
            this->Pausar();
            
        } 
        std::cout << "Thread (" << mensaje << ") ha terminado." << std::endl;
    }

	// Funci?n para Pausar el thread
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
    ~Facturador() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
	
};


struct ContenedorFacturador { //Esta lista simple es solo para los clientes
       Facturador *primerNodo, *ultimoNodo;
       ContenedorFacturador(){
           primerNodo = ultimoNodo = NULL;
       }
        	
	void Encolar( string id,bool _estaLibre, bool _estaApagado){
 		
 		if (primerNodo == NULL){
 			ultimoNodo = primerNodo = new Facturador ( id , _estaLibre,  _estaApagado);
		 }else{
		 	ultimoNodo -> siguiente = new Facturador (id, _estaLibre,  _estaApagado);
		 	ultimoNodo = ultimoNodo -> siguiente;
		 }
	}      

	void imprimir(){
            Facturador * tmp = primerNodo;
            if(tmp != NULL && tmp -> pedido != NULL){
                tmp->imprimir();
                //tmp = tmp->siguiente;
            }
            cout<<endl;
        }
 

};







