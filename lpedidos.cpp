#include <iostream>
#include <cstdlib>
#include <string>
#include "Clientes.h"
#include <fstream>
#include <windows.h>
#include <dirent.h>

using namespace std;

void listaArchivos(){//Aqui pasar por referencia las listas para guardar los documentos cargardos
  string dir = "./Pedidos";
  string elem;
  DIR *direccion;
  struct dirent * elementos;
  if (direccion=opendir(dir.c_str())){
    int cont=0;
    while (elementos=readdir(direccion)){
      if (cont != 0  && cont != 1){
        
        //Aqui estan los archivos, en otras palabras aqui se abren y se agregan alistas
        cout << elementos->d_name<<"\n";
        
        
      }
      
      cont++;
    }
  }
  
}



