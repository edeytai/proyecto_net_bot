#ifndef ENTRADA_H  
#define ENTRADA_H 

#include <string>
#include <iostream>
class Entrada {
public:
    std::string fecha;
    std::string hora;
    std::string ipOrigen;
    int puertoOrigen;
    std::string nombreOrigen;
    std::string ipDestino;
    int puertoDestino;
    std::string nombreDestino;


    Entrada(const std::string& fecha, const std::string& hora, const std::string& ipOrigen, 
            int puertoOrigen, const std::string& nombreOrigen, const std::string& ipDestino, 
            int puertoDestino, const std::string& nombreDestino)
        : fecha(fecha), hora(hora), ipOrigen(ipOrigen), puertoOrigen(puertoOrigen),
          nombreOrigen(nombreOrigen), ipDestino(ipDestino), puertoDestino(puertoDestino), 
          nombreDestino(nombreDestino) {}
};

// Definición del constructor por defecto


#endif