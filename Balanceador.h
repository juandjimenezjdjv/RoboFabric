#include "Robots.h"

using namespace std;

void BalanceadorF(ListaPedidos *PedidosAlmacen, ListaPedidos *PrioridadEspecial, ListaPedidos *Prioridad10, ListaPedidos *PrioridadBaja,ListaProductosAl *ProductosExistencias, ListaPedidos *ParaAlisto,ListaRobot *Robots );


struct BalanceadorH {
    std::thread thread; // El objeto thread
    std::string mensaje; // Mensaje que el thread imprimir?
    std::atomic<bool> pausado; // Variable de control para pausar el thread
    std::atomic<bool> terminar; // Variable de control para terminar el thread
    std::mutex mutex; // Mutex para la sincronizaci?n de pausa/reanudaci?n
    int cont = 0;
    
    ListaProductosAl * ProductosExistencias;
    ListaPedidos *PedidosAlmacen;
    ListaPedidos *PrioridadEspecial;
    ListaPedidos *Prioridad10; 
    ListaPedidos *PrioridadBaja;
    ListaPedidos *ParaAlisto;
    ListaRobot *Robots;
    
    string registro;
	
	

    // Constructor
    BalanceadorH(const std::string& msg, ListaProductosAl * ProductosExistencias, ListaPedidos *PedidosAlmacen, ListaPedidos *PrioridadEspecial,ListaPedidos *Prioridad10, ListaPedidos *PrioridadBaja,ListaPedidos *ParaAlisto,ListaRobot *Robots,string registro)
	 : mensaje(msg), pausado(false), terminar(false),ProductosExistencias(ProductosExistencias),PedidosAlmacen(PedidosAlmacen),PrioridadEspecial(PrioridadEspecial),Prioridad10(Prioridad10),PrioridadBaja(PrioridadBaja),ParaAlisto(ParaAlisto),Robots(Robots),registro(registro){
        // Iniciar el thread en el constructor
        thread = std::thread(&BalanceadorH::MiFuncion, this);//-----------------------------------------
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
            BalanceadorF(PedidosAlmacen,PrioridadEspecial,Prioridad10,PrioridadBaja,ProductosExistencias,ParaAlisto,Robots);
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
    ~BalanceadorH() {
        Terminar(); // Asegura que el thread se termine correctamente
    }
};

