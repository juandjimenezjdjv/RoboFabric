#include <cstdlib>
#include <iostream>

using namespace std;


struct ProductoAlmacen{
	
	string codigo;
	int Cantidad;
	int tiempo;
	string categoria;
	string Ubicacion;
	ProductoAlmacen * siguiente;
	ProductoAlmacen * anterior;
	
	ProductoAlmacen(string _codigo, int _Cantidad, int _tiempo, string _categoria, string _Ubicacion)
	{
		codigo = _codigo;
		Cantidad = _Cantidad;
		tiempo = _tiempo;
		categoria = _categoria;
		Ubicacion = _Ubicacion;
		siguiente = anterior = NULL;
	}
		
	void imprimir ()
	{
		cout << "<- |" << codigo << "  " << Cantidad << "  "  << tiempo << "  "  << categoria << "  "  << Ubicacion << "| ->";
	}
};

struct ListaProductosAl{
	ProductoAlmacen * primerNodo;
	ProductoAlmacen * ultimoNodo;
	
	ListaDoble(){ 
		primerNodo = ultimoNodo = NULL;
	}	
	
	bool isEmpty(){
		return primerNodo == NULL;
	}
	
	void insertarAlInicio (string _codigo, int _Cantidad, int _tiempo, string _categoria, string _Ubicacion){
		if (isEmpty())
			primerNodo = ultimoNodo = new ProductoAlmacen (_codigo,  _Cantidad,  _tiempo,  _categoria,  _Ubicacion);
		else{
			ProductoAlmacen * nuevo = new ProductoAlmacen(_codigo,  _Cantidad,  _tiempo,  _categoria,  _Ubicacion);
			nuevo->siguiente = primerNodo;
			primerNodo->anterior = nuevo;
			primerNodo = nuevo;
		}
	}
	
 	void imprimir()
	{
		ProductoAlmacen * tmp = primerNodo;
		while (tmp != NULL)
		{
			tmp->imprimir();
			tmp = tmp->siguiente; 		
		}
		cout <<endl;
	}
	
	int largo(){
		
		ProductoAlmacen * tmp = primerNodo;
		int contador = 0;
		while (tmp != NULL)
		{
			contador++;	
			tmp = tmp -> siguiente;
		}
		return contador;
	}
	
	ProductoAlmacen* BuscarProducto(string PrCodigoBsc){
		
		ProductoAlmacen * tmp = primerNodo;
		
		while(tmp != NULL){
			
			if (tmp -> codigo == PrCodigoBsc){
				return tmp;
				
			}
			tmp = tmp -> siguiente;
		}
		return NULL;	
	}
	
};

