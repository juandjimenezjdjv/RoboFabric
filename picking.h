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

struct Picking;
struct ListaPicking;
struct BalanceadorPicking;

void FuncionBalanceadorPicking (ListaPicking *Picking6,ListaPedidos *ParaAlisto,ListaPedidos *Alisto,ListaProductosAl *ProductosExistencias);


struct BalanceadorPicking {
    std::thread thread; // El objeto thread
    std::string mensaje; // Mensaje que el thread imprimir?
    std::atomic<bool> pausado; // Variable de control para pausar el thread
    std::atomic<bool> terminar; // Variable de control para terminar el thread
    std::mutex mutex; // Mutex para la sincronizaci?n de pausa/reanudaci?n
    int cont = 0;
    
 
    ListaPedidos *ParaAlisto;
    ListaPedidos *Alistados;
    ListaPicking *Picking6;
    ListaProductosAl *ProductosExistencias;
		
    // Constructor
    BalanceadorPicking(const std::string& msg,ListaPedidos *ParaAlisto,ListaPedidos *Alistados,ListaPicking *Picking6,ListaProductosAl *ProductosExistencias)
	 : mensaje(msg), pausado(false), terminar(false),ParaAlisto(ParaAlisto),Alistados(Alistados),Picking6(Picking6),ProductosExistencias(ProductosExistencias){
        // Iniciar el thread en el constructor
        thread = std::thread(&BalanceadorPicking::MiFuncion, this);//-----------------------------------------
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
            FuncionBalanceadorPicking(Picking6,ParaAlisto,Alistados,ProductosExistencias);
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
    ~BalanceadorPicking() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};



struct Picking{
	std::thread thread;
	std::string mensaje;
	std::atomic<bool> pausado;
	std::atomic<bool> terminar;
	std::mutex mutex;
	
	string id;
	bool estaLibre;
	bool estaApagado;
	int tiempo;
	Picking* siguiente;
	
	Pedido *pedido;
	ListaPedidos *Alistados;
	
	string registro;
	
	Picking (string _id, bool _estaLibre, bool _estaApagado,int _tiempo)
	{
		id = _id;
		estaLibre = _estaLibre;
		estaApagado = _estaApagado;
		tiempo = _tiempo;
		string registro = "";
		
		Pedido *pedido = new Pedido();
		ListaPedidos *Alistados = new ListaPedidos();
		
		pausado = true;
		terminar = false;
		siguiente = NULL;
		thread = std::thread(&Picking::MiFuncion, this);
		
	}	
	
	void imprimir ()
	{
		cout <<" |" << id << "  " << pedido -> numero << "  " << pedido -> Ccodigo << "|\n";
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
//            tiempo = tiempo/10;
            std::this_thread::sleep_for(std::chrono::seconds(tiempo));//tiempoDuracion
        
			if (pedido != NULL){
				string temp = "\n" + this -> id +  " esta encardo del pedido con numero -> " + pedido -> numero + "\n";
				cout <<this -> id << " esta encargando del pedido con numero -> " << pedido -> numero << endl;
				
				this -> registro = this -> registro + pedido -> numero + "  " + pedido -> Ccodigo + "\n";
				pedido -> registroBitacora = pedido -> registroBitacora + "Final : " + obtenerFechaYHora() + "\n" + "En cola de Alistados : "+  obtenerFechaYHora() + "\n";
				Alistados -> registro = Alistados -> registro + pedido -> numero + "  " + pedido -> Ccodigo + "\n";
				Alistados -> Encolar(pedido);
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
    ~Picking() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
	
};


struct ListaPicking { //Esta lista simple es solo para los clientes
       Picking *primerNodo, *ultimoNodo;
       ListaPicking(){
           primerNodo = ultimoNodo = NULL;
       }
        void insertarAlInicio (string _id, bool _estaLibre, bool _estaApagado, int _tiempo){
            if (primerNodo == NULL){
         		ultimoNodo = primerNodo = new Picking(_id, _estaLibre,  _estaApagado, _tiempo);
       		}else{
         		Picking *nuevo = new Picking(_id, _estaLibre,  _estaApagado, _tiempo);
         		nuevo->siguiente = primerNodo;
         		primerNodo = nuevo; 
      }
  }
        void imprimir(){
            Picking * tmp = primerNodo;
            while(tmp != NULL && tmp -> pedido != NULL){
                tmp->imprimir();
                tmp = tmp->siguiente;
            }
            cout<<endl;
        }
        
  	Picking * Desencolar(){
		
	   	if (primerNodo != NULL){
	   		Picking *borrado = primerNodo;
	   		if (primerNodo == NULL){
	   			ultimoNodo = NULL;
				}
	   		primerNodo = primerNodo->siguiente;
	   		borrado -> siguiente = NULL;
	   		return borrado;
			}	   		
	   	return NULL;
	}
	
	
	void Encolar(Picking *nuevo){
 		
 		if (primerNodo == NULL){
 			ultimoNodo = primerNodo = nuevo;
		 }else{
		 	ultimoNodo -> siguiente = nuevo;
		 	ultimoNodo = ultimoNodo -> siguiente;
		 }
	 }      

	void Encolar2(string id, bool _estaLibre, bool _estaApagado,int _tiempo){
	   	if (primerNodo == NULL){
		   ultimoNodo = primerNodo = new Picking(id, _estaLibre,  _estaApagado, _tiempo);
		   }else{
			ultimoNodo->siguiente = new Picking(id, _estaLibre,  _estaApagado, _tiempo);
			ultimoNodo = ultimoNodo->siguiente;
		   }
		   
	}


	void MostrarRegisto(){
            Picking * tmp = primerNodo;
            int numerador = 0;
            while(tmp != NULL ){
            	
            	cout << "\n Robot de picking numero -> " << numerador<< "******" << endl;;
                cout << tmp->registro;
                
                tmp = tmp->siguiente;
                numerador++;
            }
            cout<<endl;
        }


};




