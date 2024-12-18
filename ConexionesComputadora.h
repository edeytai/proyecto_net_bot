#ifndef ConexionesComputadora_H  
#define ConexionesComputadora_H 
#include <string>
#include <iostream>
#include <stack>
#include <vector>

template<typename T>
class ConexionesComputadora
{
private:
    std::string ipComputadora;
    std::string nombreComputadora;
    std::vector<T> conexionesEntrantes;
    std::vector<T> conexionesSalientes;

public:
    ConexionesComputadora(std::string ip, std::string nombre);
    void rellenarRegistros(std::vector<T> &db);
    void comprobarRegistrosConsecutivos();
    void obtenerUltimaConexionEntrante();
};

template <typename T>
ConexionesComputadora<T>::ConexionesComputadora(std::string ip, std::string nombre) {
    std::string valoresUsuario;
    ipComputadora = ip;
    ip.pop_back();
    std::cout << "Ingresa un número del 1 al 150 para crear tu dirección IP interna: " << std::endl;
    std::cin >> valoresUsuario;
    ipComputadora = ip + valoresUsuario;
    nombreComputadora = nombre;
}

template <typename T>
void ConexionesComputadora<T>::rellenarRegistros(std::vector<T> &db) {
    for (size_t i = 0; i < db.size(); i++) {
        if (ipComputadora == db[i].ipDestino) {
            conexionesEntrantes.push_back(db[i]);
        }
        if (ipComputadora == db[i].ipOrigen) {
            conexionesSalientes.push_back(db[i]);
        }
    }

    std::cout << "\n______________________________\n" << std::endl;
    std::cout << "La base de registros tiene un total de " << db.size() << " registros. La IP de la computadora es " << ipComputadora << "." << std::endl;
    std::cout << "Conexiones entrantes: " << conexionesEntrantes.size() << std::endl;
    std::cout << "Conexiones salientes: " << conexionesSalientes.size() << std::endl;
    std::cout << "\n______________________________\n" << std::endl;
}

template <typename T>
void ConexionesComputadora<T>::comprobarRegistrosConsecutivos() {
    int contadorConsecutivos = 1;
    int maxConsecutivos = 0;
    std::string sitioWebMaxConsecutivos;

    if (conexionesSalientes.size() < 3) {
        std::cout << "No hay suficientes conexiones salientes para comprobar secuencias de tres o más conexiones." << std::endl;
        return;
    }

    for (size_t i = 1; i < conexionesSalientes.size(); i++) {
        if (conexionesSalientes[i].nombreDestino == conexionesSalientes[i - 1].nombreDestino) {
            contadorConsecutivos++;

            if (contadorConsecutivos > maxConsecutivos) {
                maxConsecutivos = contadorConsecutivos;
                sitioWebMaxConsecutivos = conexionesSalientes[i].nombreDestino;
            }
        } else {
            contadorConsecutivos = 1;
        }
    }

    if (maxConsecutivos >= 3) {
        std::cout << "La computadora ha realizado " << maxConsecutivos << " conexiones consecutivas al mismo sitio web: " << sitioWebMaxConsecutivos << "." << std::endl;
    } else {
        std::cout << "No se encontraron secuencias de tres o más conexiones consecutivas al mismo sitio web." << std::endl;
    }
}

template <typename T>
void ConexionesComputadora<T>::obtenerUltimaConexionEntrante() {
    if (conexionesEntrantes.empty()) {
        std::cout << "No hay conexiones entrantes para esta computadora." << std::endl;
        return;
    }

    T ultimaConexion = conexionesEntrantes.back();
    std::string ip = ultimaConexion.ipOrigen;
    std::string redInterna = EntradaService<T>::internalNetworkAddress(conexionesEntrantes);

    std::string tipoConexion;
    if (ip.substr(0, redInterna.length()) == redInterna) {
        tipoConexion = "interna";
    } else {
        tipoConexion = "externa";
    }

    std::cout << "La última conexión que recibió la computadora fue desde la IP: " << ip << " y es una conexión " << tipoConexion << "." << std::endl;
}

#endif