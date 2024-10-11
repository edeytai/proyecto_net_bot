#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Entrada.h"
#include <string>
#include <algorithm>
#include <set>
#include <map>

template <class T>
class EntradaService
{
private:
    /* data */
public:

    static std::vector<T> ObtenerDB(const std::string &);
    static int getSize(const std::vector<T> &vec);
    static int getSizeByDay(const std::vector<Entrada> &vec, std::string day);

    static bool buscarComputadoras(const std::vector<Entrada>& bitacora, const std::string& c);
    static std::string internalNetworkAddress(const std::vector<Entrada> &vec);
    static std::set<std::string> emailServicesUsed(const std::vector<Entrada> &vec);
    static std::set<int> usedPortsBelow1000(const std::vector<Entrada> &vec);

};

template <class T>
inline std::vector<T> EntradaService<T>::ObtenerDB(const std::string &nombreArchivo)
{

    std::ifstream archivo(nombreArchivo);
    std::vector<T> db;
    if (!archivo.is_open())
    {
        std::cerr << "Error al abrir" << std::endl;
        return db;
    }
    std::string linea;
    while (std::getline(archivo, linea))
    {

        std::stringstream ss(linea); // Crear un stringstream de la línea
        std::string valor;
        std::string fecha, hora, ipOrigen, puertoOrigenSt, nombreOrigen, ipDestino, puertoDestinoSt, nombreDestino;

        std::getline(ss, fecha, ',');
        std::getline(ss, hora, ',');
        std::getline(ss, ipOrigen, ',');
        std::getline(ss, puertoOrigenSt, ',');
        std::getline(ss, nombreOrigen, ',');
        std::getline(ss, ipDestino, ',');
        std::getline(ss, puertoDestinoSt, ',');
        std::getline(ss, nombreDestino, ',');
        // Conversión de los puertos a enteros
        int puertoOrigen = (puertoOrigenSt == "-" ? 0 : std::stoi(puertoOrigenSt));
        int puertoDestino = (puertoDestinoSt == "-" ? 0 : std::stoi(puertoDestinoSt));

        // Crear objeto Entrada con los valores leídos y agregarlo a la base de datos
        db.emplace_back(Entrada(fecha, hora, ipOrigen, puertoOrigen, nombreOrigen, ipDestino, puertoDestino, nombreDestino));
    }

    archivo.close();
    return db;
}

template <class T>
inline int EntradaService<T>::getSize(const std::vector<T> &vec)
{
    return vec.size();
}

template <class T>
inline int EntradaService<T>::getSizeByDay(const std::vector<Entrada> &vec, std::string day)
{
    std::vector<Entrada> resultados;
    int resultado = 0;
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (vec[i].fecha == day)
        {
            resultado++;
        }
    }

    return resultado;
}

template <class T>
inline bool EntradaService<T>::buscarComputadoras(const std::vector<Entrada>& bitacora, const std::string& c) 
{
    std::string nombreBuscado = c; 
    std::transform(nombreBuscado.begin(), nombreBuscado.end(), nombreBuscado.begin(), tolower);

    for (size_t i = 0; i < bitacora.size(); ++i) 
    {
        std::string nombreOrigenMinusculas = bitacora[i].nombreOrigen;
        std::transform(nombreOrigenMinusculas.begin(), nombreOrigenMinusculas.end(), nombreOrigenMinusculas.begin(), tolower);

        std::string nombreDestinoMinusculas = bitacora[i].nombreDestino;
        std::transform(nombreDestinoMinusculas.begin(), nombreDestinoMinusculas.end(), nombreDestinoMinusculas.begin(), tolower);

        if (nombreOrigenMinusculas == nombreBuscado + ".reto.com" || 
            nombreDestinoMinusculas == nombreBuscado + ".reto.com") 
        { 
            return true;
        }
    }
    return false;
}

template <class T>
inline std::string EntradaService<T>::internalNetworkAddress(const std::vector<Entrada> &vec)
{
    std::map<std::string, int> prefixCounts;

    for (std::vector<Entrada>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        std::string ip = it->ipOrigen;
        size_t lastDot = ip.find_last_of('.');
        if (lastDot != std::string::npos)
        {
            std::string prefix = ip.substr(0, lastDot + 1);
            prefixCounts[prefix]++;
        }
    }

    std::string mostCommonPrefix;
    int maxCount = 0;
    for (std::map<std::string, int>::const_iterator it = prefixCounts.begin(); it != prefixCounts.end(); ++it)
    {
        if (it->second > maxCount)
        {
            mostCommonPrefix = it->first;
            maxCount = it->second;
        }
    }

    if (maxCount > 0)
    {
        return mostCommonPrefix + "X";
    }
    else
    {
        return "No se pudo determinar la dirección de red interna.";
    }
}

template <class T>
inline std::set<std::string> EntradaService<T>::emailServicesUsed(const std::vector<Entrada> &vec)
{
    std::set<std::string> emailServices;
    std::set<int> emailPorts;
    emailPorts.insert(465);
    emailPorts.insert(433);
    emailPorts.insert(110);
    emailPorts.insert(143);
    emailPorts.insert(993);
    emailPorts.insert(995);
    emailPorts.insert(25);
    emailPorts.insert(587);

    typename std::vector<Entrada>::const_iterator it;
    for (it = vec.begin(); it != vec.end(); ++it)
    {
        if (emailPorts.find(it->puertoDestino) != emailPorts.end() || emailPorts.find(it->puertoOrigen) != emailPorts.end())
        {
            emailServices.insert(it->nombreDestino);
        }
    }
    return emailServices;
}

template <class T>
inline std::set<int> EntradaService<T>::usedPortsBelow1000(const std::vector<Entrada> &vec)
{
    std::set<int> puertos;
    for (std::vector<Entrada>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it->puertoDestino > 0 && it->puertoDestino < 1000)
        {
            puertos.insert(it->puertoDestino);
        }
    }
    return puertos;
}