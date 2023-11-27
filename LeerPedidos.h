#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <atomic>
#include <mutex>
#include <chrono>
#include <thread>
#include "structPedidos.h"
#include <dirent.h>
#include <sstream>
#include "Almacen.h"

using namespace std;
int enteros2(string entrada);
//int ejecutar(ListaPedidos *Pedidostmp);
//void ValidarYEncolarP( ListaProductosAl * ProductosExistencias, ListaCliente * Clientes, ListaPedidos * _Pedidos, ListaPedidos * PedidosPrioridad10, ListaPedidos * PedidosNo10,ListaPedidos * PedidosError);
void PrimerHilo( string carpeta, ListaProductosAl * ProductosExistencias, ListaCliente * Clientes, ListaPedidos * PedidosPrioridad10, ListaPedidos * PedidosNo10,ListaPedidos * PedidosError);


struct MyThread {
    std::thread thread; // El objeto thread
    std::string mensaje; // Mensaje que el thread imprimir?
    std::atomic<bool> pausado; // Variable de control para pausar el thread
    std::atomic<bool> terminar; // Variable de control para terminar el thread
    std::mutex mutex; // Mutex para la sincronizaci?n de pausa/reanudaci?n
    int cont = 0;
    
    string carpeta;
    ListaProductosAl * ProductosExistencias;
    ListaCliente * Clientes;
    ListaPedidos * PedidosPrioridad10;
    ListaPedidos * PedidosNo10;
    ListaPedidos * PedidosError;


    // Constructor
    MyThread(const std::string& msg,string carpeta,  ListaProductosAl * ProductosExistencias, ListaCliente * Clientes, ListaPedidos * PedidosPrioridad10, ListaPedidos * PedidosNo10,ListaPedidos * PedidosError)
	 : mensaje(msg), pausado(false), terminar(false),carpeta(carpeta),ProductosExistencias(ProductosExistencias),Clientes(Clientes),PedidosPrioridad10(PedidosPrioridad10),PedidosNo10(PedidosNo10),PedidosError(PedidosError){
        // Iniciar el thread en el constructor
        thread = std::thread(&MyThread::MiFuncion, this);//-----------------------------------------
    }

    // Funci?n que ser? ejecutada por el thread
    void MiFuncion() {//ListaPedidos *Pedidostmp
        while (!terminar) {
//            {
//                std::unique_lock<std::mutex> lock(mutex);
//                while (pausado) {
//                    // El thread est? en pausa, espera
//                    lock.unlock();
//                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
//                    lock.lock();
//                }
//            }

            //Aqui funcion
            PrimerHilo(carpeta,ProductosExistencias,Clientes,PedidosPrioridad10,PedidosNo10,PedidosError);
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
    ~MyThread() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};


