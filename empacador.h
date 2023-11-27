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
struct ContenedorEmpacador;
struct HiloEmpacador;

void empacadorF (ListaPedidos * Alistados, ListaPedidos *Factura,ContenedorEmpacador *Lazo);

struct HiloEmpacador {
    std::thread thread; // El objeto thread
    std::string mensaje; // Mensaje que el thread imprimir?
    std::atomic<bool> pausado; // Variable de control para pausar el thread
    std::atomic<bool> terminar; // Variable de control para terminar el thread
    std::mutex mutex; // Mutex para la sincronizaci?n de pausa/reanudaci?n
 
    ListaPedidos *Alistados;
    ListaPedidos *Factura;
    ContenedorEmpacador *Lazo;
     
		
    // Constructor
    HiloEmpacador(const std::string& msg,ListaPedidos *Alistados,ListaPedidos *Factura, ContenedorEmpacador *Lazo)
	 : mensaje(msg), pausado(true), terminar(false),Alistados(Alistados),Factura(Factura),Lazo(Lazo){
        // Iniciar el thread en el constructor
        thread = std::thread(&HiloEmpacador::MiFuncion, this);//-----------------------------------------
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
            empacadorF(Alistados, Factura, Lazo);
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
    ~HiloEmpacador() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};



struct Empacador{
	std::thread thread;
	std::string mensaje;
	std::atomic<bool> pausado;
	std::atomic<bool> terminar;
	std::mutex mutex;
	
	string id;
	bool estaLibre;
	bool estaApagado;
	int tiempo;
	Empacador* siguiente = NULL;
	
	Pedido *pedido;
	ListaPedidos *Factura;
	
	string registro;
	
	Empacador (string _id, bool _estaLibre, bool _estaApagado,int _tiempo)
	{
		id = _id;
		estaLibre = _estaLibre;
		estaApagado = _estaApagado;
		tiempo = _tiempo;
		string registro = "";
		
		Pedido *pedido = new Pedido();
		ListaPedidos *Factura = new ListaPedidos();
		
		pausado = true;
		thread = std::thread(&Empacador::MiFuncion, this);
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
            //cout << tiempo << endl;
//            tiempo = tiempo/3;
            std::this_thread::sleep_for(std::chrono::seconds(tiempo));//tiempoDuracion
        
			if (pedido != NULL){
				string temp = "\nEl empacador " + this -> id + " esta encardo del pedido con numero -> " + pedido -> numero + "\n";
				cout << this -> id << " esta encargando del pedido con numero -> " << pedido -> numero << endl;
				
				pedido -> registroBitacora = pedido -> registroBitacora + "Final empacador : " + obtenerFechaYHora() + "\n";
				this -> registro = this -> registro + pedido -> numero + "  " + pedido -> Ccodigo + "\n";
				Factura -> registro = Factura -> registro + pedido -> numero + "  " + pedido -> Ccodigo + "\n";
				Factura -> Encolar(pedido);
				this -> pedido = NULL;
	         	this->estaLibre = true;
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
    ~Empacador() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
	
};


struct ContenedorEmpacador { //Esta lista simple es solo para los clientes
       Empacador *primerNodo, *ultimoNodo;
       ContenedorEmpacador(){
           primerNodo = ultimoNodo = NULL;
       }
        	
	void Encolar(string _id, bool _estaLibre, bool _estaApagado,int _tiempo){
 		
 		if (primerNodo == NULL){
 			ultimoNodo = primerNodo = new Empacador ( _id,  _estaLibre,  _estaApagado, _tiempo);
		 }else{
		 	ultimoNodo -> siguiente = new Empacador (_id,  _estaLibre,  _estaApagado, _tiempo);
		 	ultimoNodo = ultimoNodo -> siguiente;
		 }
	}      

	void imprimir(){
             Empacador * tmp = primerNodo;
            while(tmp != NULL && tmp -> pedido != NULL){
                tmp->imprimir();
                tmp = tmp->siguiente;
            }
            cout<<endl;
        }

};




