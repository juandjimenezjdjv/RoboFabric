#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include "Clientes.h"
#include "Almacen.h"
#include "structPedidos.h"
#include <dirent.h>

using namespace std;
int enteros();
int enteros2(string entero);    
    

//*************************************************************************
//Esta lee el archivo de clientes
// y la otra permite agregar cleintes a la misma cola desde la aplicacion

ListaCliente* leerClientes(string archivo){
	ListaCliente * ListaClientes = new ListaCliente();
    ifstream clientes(archivo);
    
    if ( clientes.is_open()){
    	string linea;
        while (getline(clientes, linea)) { 
//        	cout << linea << endl;
        	
			istringstream ss(linea);
            string campo;
            string codCliente;
            string nombre;
            int priori;
            int cont =0;
            while (getline(ss, campo, '\t')) {
            	if (cont == 0)
					codCliente = campo;
				else if (cont == 1)
					nombre = campo;
				else if (cont == 2){
					char* endptr;
				    priori = strtol(campo.c_str(), &endptr, 10);
				}
        		cont++;
    		}
    		ListaClientes -> insertarAlInicio(codCliente,nombre,priori);
    		cont=0;
    		//Aqui agregar a lista simple si no hay error del catch
//    		cout << codCliente << "  --  " << nombre << "  --  " << priori << "\n" << endl;
        }
//    listaClientes->imprimir();
	return ListaClientes;
    clientes.close();
    }else{
	    cerr << "Hubo un error con el archivo de Clientes " ;
    }
    
}

void AddClientes(ListaCliente *ListaClientes){
	int funciona = 0;
	string CodigoC, NombreC, respuesta, priori;
    int prioridad;
    
	cin.ignore();
    cout << "Cual es el codigo del nuevo cliente? " << endl;
    getline(cin,CodigoC);
    cout << "Cual es el nombre del cliente? " << endl;
    getline(cin,NombreC);
  	cout << "Cual es la prioridad del cliente? " << endl;
  	bool valida = true;
    while(valida){
    	prioridad = enteros();
    	if (prioridad > 0 && prioridad < 11)
    		valida = false;
    	else
    		cout << "Digite una prioridad para el cliente entre 1 a 10:" << endl;
	}
    
	ListaClientes -> insertarAlInicio (CodigoC,NombreC,prioridad);

    cout << "Desea ver la lista actualizada? (s/n) " << endl;
    cin >> respuesta;

    ofstream Ctxt("Clientes.txt", ios::app);

    if (Ctxt.fail()){
        cout << "Hubo un error con abrir el archivo de Clientes" << endl;
    }else{
    	ostringstream stream;
    	stream << prioridad;
    	priori = stream.str();
        string linea = CodigoC + "\t" + NombreC + "\t" + priori;
        Ctxt << linea << endl;
    }

    Ctxt.close();

    if (respuesta == "s" || respuesta == "S")
        ListaClientes -> imprimir();
}

//Fin de CLIENTESS
//*************************************************************************


//*************************************************************************
//Esta lee el archivo de productos y los lamacena en una lista doblemente enlazada


ListaProductosAl* LeerAlmacentxt(string nombreArchivo) {
	
    ListaProductosAl* ProductosAl = new ListaProductosAl();
    string codigo, cantidadStr, tiempoStr, ubicacion;
    int cantidad, tiempo;
    string categoria;
    string respuesta;

    ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream stream(linea);
            
            getline(stream, codigo, '\t');
            getline(stream, cantidadStr, '\t');
            getline(stream, tiempoStr, '\t');
            getline(stream, categoria, '\t');
            getline(stream, ubicacion, '\n');

            // Convierte las cadenas a los tipos de datos adecuados
            cantidad = enteros2(cantidadStr);
            tiempo =  enteros2( tiempoStr);
            

            //cout << "Dato 1: " << codigo << ", Dato 2: " << cantidad << ", Dato 3: " << tiempo
            //          << ", Dato 4: " << categoria << ", Dato 5: " << ubicacion << endl;
            
            if (categoria == "A" || categoria == "B" ||categoria == "C" ){
            	if(cantidad >= 0){
            		ProductosAl->insertarAlInicio(codigo, cantidad, tiempo, categoria, ubicacion);
				}else{
					cerr << "No se agrego debido a las cantidad";	
				}
			}else {
				cerr << "No se agrego el Articulo con el codigo " << codigo << " debido a la categoria";
			}
            
        }

        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }

   return ProductosAl;
}


//Fin de Productos
//*************************************************************************


//*************************************************************************
//Estas son 2 muy importantes ************
// Ejecutar lo que hace es abrir una carpeta y ir archivo por archivo leyendo el pedido encolarlo escribirlo en una nueva carpeta y borrarlo de la actual
//Leer archivo lo que hace es obtener los datos para crear el objeto y encolarlo


// Función para leer el contenido de un archivo y almacenarlo en un string
string leerArchivo(const  string& ruta, ListaPedidos *Pedidos) {
     ifstream archivoEntrada(ruta.c_str());
     string contenido;
    ListaProductos *Productos = new ListaProductos();
    if (archivoEntrada.is_open()) {
    	
         string linea, numero, codigo, temporal, Pcodigo, Pcantidad;
         bool banderaProductos = false;
         int cantidadP,contador = 0;
         
         
         
        while ( getline(archivoEntrada, linea)) {
        	
			if (contador == 0)
			numero = linea;
			else if(contador == 1)
			codigo = linea;
			else{
				 
				temporal = linea;
				istringstream ss(linea);
    			getline(ss, Pcodigo, '\t');  
    			getline(ss, Pcantidad);
				
				cantidadP = enteros2(Pcantidad);
				Productos -> insertarAlInicio(Pcodigo,cantidadP);
				
				banderaProductos = true;
			}
			contador++;
            contenido += linea + '\n';  // Agregar el contenido de la línea al string
        }
        if (banderaProductos == true){
        	Pedidos -> Encolar2(numero,codigo,Productos);
		}

        
        
        //cout << "\nde txt a memoria\n";
        archivoEntrada.close();
        remove(ruta.c_str());
    }
    return contenido;
}

ListaPedidos* ejecutar(string carpeta) {
     //string carpeta = "./Pedidoszzz";
     ListaPedidos *Pedidostmp = new ListaPedidos();
     string contenidoTotal;

    DIR* directorio;
    struct dirent* archivoEntrada;

    if ((directorio = opendir(carpeta.c_str())) != NULL) {
        while ((archivoEntrada = readdir(directorio)) != NULL) {
             string nombreArchivo = archivoEntrada->d_name;
            if (nombreArchivo.size() >= 4 &&
                nombreArchivo.substr(nombreArchivo.size() - 4) == ".txt") {
                // Construye la ruta completa del archivo
                 string rutaCompleta = carpeta + "/" + nombreArchivo;
                 string contenido = leerArchivo(rutaCompleta,Pedidostmp);
                 
                contenidoTotal += contenido;
            }
        }
        closedir(directorio);
    } else {
         cerr << "No se pudo abrir la carpeta." <<  endl;
        return Pedidostmp;
    }

    return Pedidostmp;
}


//****************************************************************************















