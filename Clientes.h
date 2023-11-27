#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


struct Cliente;
struct ListaCliente;

struct Cliente {

    	string Ccodigo, Cnombre;
       	int prioridad; 

      	Cliente* siguiente = NULL; // = NULL;
      	
      	
        Cliente(string codigo, string nombre, int _prioridad){

            Ccodigo = codigo;
            Cnombre =  nombre;
            prioridad = _prioridad;
            //siguiente = NULL;
        }
       void imprimir(){ 
               cout << "|" << Ccodigo << " -- " << Cnombre << " -- " << prioridad << "|\n" ;
       }
};


struct ListaCliente { //Esta lista simple es solo para los clientes
       Cliente *primerNodo, *ultimoNodo;
       
       ListaCliente(){
           primerNodo = ultimoNodo = NULL;
       }
        void insertarAlInicio (string codigo,string nombre, int _prioridad){
            if (primerNodo == NULL){
         		ultimoNodo = primerNodo = new Cliente(codigo,nombre,_prioridad);
       		}else{
         		Cliente *nuevo = new Cliente(codigo,nombre,_prioridad);
         		nuevo->siguiente = primerNodo;
         		primerNodo = nuevo; 
      }
  }
        void imprimir(){
            Cliente * tmp = primerNodo;
            while(tmp != NULL){
                tmp->imprimir();
                tmp = tmp->siguiente;
            }
            cout<<endl;
        }
        
		
	Cliente* BuscarCliente(string CodigoC) {
		
		if (primerNodo != NULL){
			Cliente *tmp = primerNodo;

        while (tmp != NULL) {
            if (CodigoC == tmp->Ccodigo) {
                return tmp;
                break; // Puedes usar break si solo quieres la primera ocurrencia
                tmp = tmp->siguiente; 
            }
            tmp = tmp->siguiente;
        }
	}else{
        return NULL; // Devuelve NULL si no se encuentra ningún cliente con el nombre dado	
		}
	}
	
	
	
	void InsertaralFinal (string codigo,string nombre, int _prioridad){
	   	if (primerNodo == NULL){
		   ultimoNodo = primerNodo = new Cliente(codigo,nombre,_prioridad);
		   }else{
			ultimoNodo->siguiente = new Cliente(codigo,nombre,_prioridad);
			ultimoNodo = ultimoNodo->siguiente;
		   }
		   
	}

};



