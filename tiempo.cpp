#include <iostream>
#include <ctime>
#include <string>

using namespace std;


std::string obtenerFechaYHora() {
    // Obtener la fecha y hora actual en un formato legible
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H-%M-%S", &tstruct);  // Cambiado formato aquí
    return buf;
}

