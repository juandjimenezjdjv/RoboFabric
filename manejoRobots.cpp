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

using namespace std;

int enteros();
void cambiarencendido (ListaRobot * robots);
void funcione (ListaRobot * robots);
void cambiarpriori (ListaRobot * robots);
void cambiartipo (ListaRobot * robots);

void robotEnceApa(ListaRobot * robots){
	funcione (robots);
	int opcion = 0;
	do{
		cout << "Manejo de robots" << endl;
		cout << "\t.:Menu:." << endl;
		cout << "  1. Encender o apagar robots." << endl;
		cout << "  2. Cambiar prioridad." << endl;
		cout << "  3. Cambiar tipo." << endl;
		cout << "  4. Imprimir robots. "<< endl;
		cout << "  5. Salir. " << endl;
		cout << "Digite la opcion deseada: ";

		opcion = enteros();
		if (opcion == -1) {
			cout << "Digite un numero correcto." << endl;
			system("pause");
		}
		
		switch(opcion){
			case 1:
				cambiarencendido (robots);
				cout<<"\n";
				system("pause");
				break;
				
			case 2:
				cambiarpriori (robots);
				cout<<"\n";
				system("pause");
				break;
				
			case 3:
				cambiartipo (robots);
				cout<< "\n";
				
				system("pause");
				break;
			
				
			case 4:
				funcione (robots);
				cout<<"\n";
				system("pause");
				break;
			
		}
		system("cls");
	}while(opcion != 5);
}

void funcione (ListaRobot * robots){
	Robot *temp = robots -> primerNodo;
		string tipo, priori, apagado;
		
		while(temp != NULL){
			if (temp -> estaApagado == false)apagado = ". Esta prendido"; else apagado = ". Esta apagado";
			if (temp -> prioridad == false)priori = ". No es de prioridad"; else priori = ". Es de prioridad";
			
			tipo = temp->tipo;
			cout << "Robot: " << temp -> nombreR << apagado << priori << ". De tipo: "<< tipo << endl;
			
			temp = temp -> siguiente;
		}
	}

void cambiarencendido (ListaRobot * robots){
	Robot *temp = robots -> primerNodo;
	cout << "Digite el robot que desea encender o apagar (0-9): " << endl;
	int encendido = enteros();
	bool ciclos = true;
	while (ciclos){
		if (encendido == 9 || encendido == 8 || encendido == 7 || encendido == 6 || encendido == 5 || encendido == 4 || encendido == 3 || encendido == 2 || encendido == 1 || encendido == 0){
			ciclos = false;
		}else{
			cout << "Error" << endl;
			cout << "Digite un numero de robot correcto (0-9): " << endl;
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
	int busca = 9;
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
		busca--;
		temp = temp -> siguiente;
	}
	
}

void cambiarpriori (ListaRobot * robots){
	Robot *temp = robots -> primerNodo;
	cout << "Digite el robot que desea cambiar prioridad  (0-9): " << endl;
	int encendido = enteros();
	bool ciclos = true;
	while (ciclos){
		if (encendido == 9 || encendido == 8 || encendido == 7 || encendido == 6 || encendido == 5 || encendido == 4 || encendido == 3 || encendido == 2 || encendido == 1 || encendido == 0){
			ciclos = false;
		}else{
			cout << "Error" << endl;
			cout << "Digite un numero de robot correcto  (0-9): " << endl;
			encendido = enteros();
		}
	}
	int interruptor = 0;
	cout << "Digite un numero para Prioridad(1) o Sin Prioridad(2): " << endl;
	interruptor = enteros();
	ciclos = true;
	while (ciclos){
		if (interruptor == 1 || interruptor == 2){
			ciclos = false;
		}else{
			cout << "Error" << endl;
			cout << "Digite un numero correcto para Prioridad(1) o Sin Prioridad(2): " << endl;
			interruptor = enteros();
		}
		
	}
	int busca = 9;
	while (temp -> siguiente != NULL){
		if (encendido == busca){
			if (interruptor == 1) {
				temp->prioridad = true;
				cout << "Ahora tiene prioridad." << endl;
			} else {
				temp->prioridad = false;
				cout << "Se quito prioridad." << endl;
			}
		}
		busca--;
		temp = temp -> siguiente;
	}
	
}
void cambiartipo (ListaRobot * robots){
	Robot *temp = robots -> primerNodo;
	cout << "Digite el robot que desea cambiar el tipo (0-9): " << endl;
	int encendido = enteros();
	bool ciclos = true;
	while (ciclos){
		if (encendido == 9 || encendido == 8 || encendido == 7 || encendido == 6 || encendido == 5 || encendido == 4 || encendido == 3 || encendido == 2 || encendido == 1 || encendido == 0){
			ciclos = false;
		}else{
			cout << "Error" << endl;
			cout << "Digite un numero de robot correcto  (0-9): " << endl;
			encendido = enteros();
		}
	}
	int interruptor = 0;
	cout << "Digite un numero para tipo A(1), B(2), C(3) o todas(4): " << endl;
	interruptor = enteros();
	ciclos = true;
	while (ciclos){
		if (interruptor == 1 || interruptor == 2 || interruptor == 3 || interruptor == 4){
			ciclos = false;
		}else{
			cout << "Error" << endl;
			cout << "Digite un numero correcto para tipo A(1), B(2), C(3) o todas(4): " << endl;
			interruptor = enteros();
		}
		
	}
	int busca = 9;
	while (temp -> siguiente != NULL){
		if (encendido == busca){
			if (interruptor == 1) {
				temp->tipo = "A";
				cout << "Ahora es tipo A." << endl;
			} else if (interruptor == 2) {
				temp->tipo = "B";
				cout << "Ahora es tipo B." << endl;
			} else if (interruptor == 3) {
				temp->tipo = "C";
				cout << "Ahora es tipo C." << endl;
			} else {
				temp->tipo = "todas";
				cout << "Ahora es tipo Todas." << endl;
			}
		}
		busca--;
		temp = temp -> siguiente;
	}
	
}

