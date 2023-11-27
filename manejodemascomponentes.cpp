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

#include "Robots.h"
#include "picking.h"
#include "empacador.h"
#include "Facturador.h"

using namespace std;

int enteros();
void encendidopicking (ListaPicking * Pickings);
void funcione (ListaPicking * Pickings);
void encendidoempacador (ContenedorEmpacador * emp);
void encendidofacturador (ContenedorFacturador * fact);


void robotdemas(ListaPicking * Pickings, ContenedorEmpacador * emp, ContenedorFacturador * fact){//, BalanceadorH * bala
	int opcion = 0;
	do{
		cout << "Manejo de Pickings" << endl;
		cout << "\t.:Menu:." << endl;
		cout << "  1. Encender o apagar Pickings del picking." << endl;
		cout << "  2. Imprimir todos los picking." << endl;
		cout << "  3. Encender o apagar Empacador." << endl;
		cout << "  4. Encender o apagar Facturador." << endl;
		cout << "  5. Salir. " << endl;
		cout << "Digite la opcion deseada: ";

		opcion = enteros();
		if (opcion == -1) {
			cout << "Digite un numero correcto." << endl;
			system("pause");
		}
		
		switch(opcion){
			case 1:
				encendidopicking (Pickings);
				cout<<"\n";
				system("pause");
				break;
				
			case 2:
				funcione(Pickings);
				cout<<"\n";
				system("pause");
				break;
				
			case 3:
				encendidoempacador (emp);
				cout<< "\n";
				system("pause");
				break;
			
				
			case 4:
				encendidofacturador (fact);
				cout<<"\n";
				system("pause");
				break;
			
		}
		system("cls");
	}while(opcion != 5);
}

void funcione (ListaPicking * Pickings){
	Picking *temp = Pickings -> primerNodo;
		string apagado;
		
		while(temp != NULL){
			if (temp -> estaApagado == false)apagado = ". Esta prendido"; else apagado = ". Esta apagado";

			cout << "Robot picking: " << temp -> id << apagado << endl;
			
			temp = temp -> siguiente;
		}
	}

void encendidopicking (ListaPicking * Pickings){
	Picking *temp = Pickings -> primerNodo;
	cout << "Digite el robot picking que desea encender o apagar, son seis robots (1-6): " << endl;
	int encendido = enteros();
	bool ciclos = true;
	while (ciclos){
		if (encendido == 5 || encendido == 4 || encendido == 3 || encendido == 2 || encendido == 1 || encendido == 6){
			ciclos = false;
		}else{
			cout << "Error" << endl;
			cout << "Digite un numero de robot picking correcto (1-6): " << endl;
			encendido = enteros();
		}
	}
	int interruptor = 0;
	cout << "Digite un numero para apagar(1) o encender(2): " << endl;
	interruptor = enteros();
	ciclos = true;
	while (ciclos){
		if (interruptor == 1 || interruptor == 2){
			ciclos = false;
		}else{
			cout << "Error" << endl;
			cout << "Digite un numero correcto para apagar(1) o encender(2): " << endl;
			interruptor = enteros();
		}
	}
	int busca = 0;
	while (temp -> siguiente != NULL){
		if (encendido == busca){
			if (interruptor == 1) {
				temp->estaApagado = true;
				cout << "Se apago correctamente." << endl;
			} else {
				temp->estaApagado = false;
				cout << "Se encendio correctamente." << endl;
			}
		}
		busca++;
		temp = temp -> siguiente;
	}
	
}

void encendidoempacador (ContenedorEmpacador * emp){
	Empacador *temp = emp -> primerNodo;
	bool ciclos = true;
	string empaca = "";
	if (temp->estaApagado == false) empaca = "encendido"; else empaca = "apagado";
	cout << "El empacador esta " << empaca << endl;
	int interruptor = 0;
	cout << "Digite un numero para apagar(1) o encender(2): " << endl;
	interruptor = enteros();
	ciclos = true;
	while (ciclos){
		if (interruptor == 1 || interruptor == 2){
			ciclos = false;
		}else{
			cout << "Error" << endl;
			cout << "Digite un numero correcto para apagar(1) o encender(2): " << endl;
			interruptor = enteros();
		}
	}
	if (interruptor == 1) {
		temp->estaApagado = true;
		cout << "Se apago correctamente." << endl;
	} else {
		temp->estaApagado = false;
		cout << "Se encendio correctamente." << endl;
	}	
}

void encendidofacturador (ContenedorFacturador * fact){
	Facturador *temp = fact -> primerNodo;
	bool ciclos = true;
	string factura = "";
	if (temp->estaApagado == false) factura = "encendido"; else factura = "apagado";
	cout << "El facturador esta " << factura << endl;
	int interruptor = 0;
	cout << "Digite un numero para apagar(1) o encender(2): " << endl;
	interruptor = enteros();
	ciclos = true;
	while (ciclos){
		if (interruptor == 1 || interruptor == 2){
			ciclos = false;
		}else{
			cout << "Error" << endl;
			cout << "Digite un numero correcto para apagar(1) o encender(2): " << endl;
			interruptor = enteros();
		}
	}
	if (interruptor == 1) {
		temp->estaApagado = true;
		cout << "Se apago correctamente." << endl;
	} else {
		temp->estaApagado = false;
		cout << "Se encendio correctamente." << endl;
	}	
}

