
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
        if (banderaProductos == false)
        cout << "Hubo un error ";
        
        
        Pedidos -> Encolar2(numero,codigo,Productos);
        cout << "\nde txt a memoria\n";
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


 
