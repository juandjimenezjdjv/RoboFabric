#include <iostream>
#include <cstdlib>
#include <string>
 

using namespace std;

struct Producto;
struct ListaProductos;
struct Pedidos;
struct ListaPedidos;

struct Producto{
    string Pcodigo;
    int cantidad;
    Producto* siguiente;
    
    Producto(){
    	Pcodigo = "";
    	cantidad = 0;
    	siguiente = NULL;
	}
    
    Producto(string codigo, int _cantidad){
        Pcodigo = codigo;
        cantidad = _cantidad;
    }

    void imprimir(){ 
       cout << "|" << Pcodigo << " -- " << cantidad << "|\n" ;
    }

};

struct ListaProductos{

     Producto *primerNodo, *ultimoNodo;
       ListaProductos(){
           primerNodo = ultimoNodo = NULL;
       }

    void insertarAlInicio (string codigo, int cantidad){

        if (primerNodo == NULL){
         ultimoNodo = primerNodo = new Producto(codigo,cantidad);
       }else{
         Producto *nuevo = new Producto(codigo,cantidad);
         nuevo->siguiente = primerNodo;
         primerNodo = nuevo; 
      }
  }

    void imprimir(){
        Producto *tmp = primerNodo;
        while(tmp != NULL){
            // aqu? programar lo que necesiten en cada iteraci?n
            tmp->imprimir();
            tmp = tmp->siguiente;
        }
        cout<<endl;
    }
    
    int largo(){
 		Producto *tmp = primerNodo;
		int contador = 0;
		while (tmp != NULL)
		{
			contador++;
			tmp = tmp -> siguiente;
		}
		return contador;
	}

};

struct Pedido{

    string numero;
    string Ccodigo;
    ListaProductos *Productos = new ListaProductos();
    string registroBitacora;
    Pedido *siguiente = NULL;

	Pedido(){
		numero = "";
		Ccodigo = "";
		registroBitacora = "";
		Productos = NULL;
		siguiente = NULL;
	}

    Pedido(string _numero, string codigo, ListaProductos *_Productos){
        numero = _numero;
        registroBitacora = "";
        Ccodigo = codigo;
        Productos = _Productos;
    }

    void imprimir(){
    	//cout << "1" <<endl;
        cout << "|" << numero << " -- " << Ccodigo << "\n" ;
        Productos->imprimir();
        cout << "\n\n";
    }
    
   
};

struct ListaPedidos{
    	Pedido *primerNodo, *ultimoNodo;
    	string registro;
    ListaPedidos(){
    	primerNodo = ultimoNodo = NULL;
    	registro = "";
    }

    void insertarAlInicio (string numero, string codigo, ListaProductos *_Productos){

        if (primerNodo == NULL){
         ultimoNodo = primerNodo = new Pedido(numero,codigo, _Productos);
       }else{
         Pedido *nuevo = new Pedido(numero,codigo, _Productos);
         nuevo->siguiente = primerNodo;
         primerNodo = nuevo; 
      }
  }

    void imprimir(){
        Pedido *tmp = primerNodo;
        while(tmp != NULL){
            // aqu? programar lo que necesiten en cada iteraci?n
            tmp->imprimir();
            tmp = tmp->siguiente;
        }
        cout<<endl;
    }
	
	Pedido * Desencolar(){
		
	   	if (primerNodo != NULL){
	   		Pedido *borrado = primerNodo;
	   		if (primerNodo == NULL){
	   			ultimoNodo = NULL;
				}
	   		primerNodo = primerNodo->siguiente;
	   		borrado -> siguiente = NULL;
	   		return borrado;
			}	   		
	   	return NULL;
}
	
	
	void Encolar(Pedido *nuevo){
 		
 		if (primerNodo == NULL){
 			ultimoNodo = primerNodo = nuevo;
		 }else{
		 	ultimoNodo -> siguiente = nuevo;
		 	ultimoNodo = ultimoNodo -> siguiente;
		 }
	 }
	 
	void Encolar2(string numero, string codigo, ListaProductos *_Productos){
	   	if (primerNodo == NULL){
		   ultimoNodo = primerNodo = new Pedido(numero,codigo, _Productos);
		   }else{
			ultimoNodo->siguiente = new Pedido(numero,codigo, _Productos);
			ultimoNodo = ultimoNodo->siguiente;
		   }
		   
	}
	   

	
	
};









