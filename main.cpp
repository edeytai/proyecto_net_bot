#include "Entrada.cpp"
#include <iostream>
#include <vector>
#include "EntradaService.cpp"
#include "ConexionesCompudatora.cpp"
#include <map>

int main(int argc, char const *argv[])
{
   
   
    std::vector<Entrada> db  = EntradaService<Entrada>::ObtenerDB("equipo2.csv");
    
    std::string direccionRedInternaPc = EntradaService<Entrada>::internalNetworkAddress(db);
     ConexionesCompudatora<Entrada> pc1 = ConexionesCompudatora<Entrada> (direccionRedInternaPc, "mi pc");
    pc1.rellenarRegistros(db);

    pc1.comprobarRegistrosConsecutivos();

    pc1.obtenerUltimaConexionEntrante();

    int documentDbSize= EntradaService<Entrada>::getSize(db);
    int documentDbSecondDaySize= EntradaService<Entrada>::getSizeByDay(db, "12-8-2020");
    std::cout << "Hay un total de " <<documentDbSize<<" registros" <<std::endl;
    std::cout << "El segundo dia hubo " <<documentDbSecondDaySize<<" registros" <<std::endl;

    std::string nombreABuscar;
    std::cout<<"Ingresa el nombre a buscar: ";
    std::cin>>nombreABuscar;
    
    if (EntradaService<Entrada>::buscarComputadoras(db, nombreABuscar)) 
    {
        std::cout << nombreABuscar << " tiene una computadora en la red." << std::endl;
    } 
    else
    {
    std::cout << nombreABuscar << " no tiene una computadora en la red." << std::endl;
    }   

    std::string direccionRedInterna = EntradaService<Entrada>::internalNetworkAddress(db);
    if (direccionRedInterna.find('.') != std::string::npos) 
    { 
        std::cout << "La dirección de la red interna es: " << direccionRedInterna << std::endl;
    } 
    else 
    {
        std::cout << direccionRedInterna << std::endl;
    }

    std::set<std::string> serviciosCorreo = EntradaService<Entrada>::emailServicesUsed(db);
    if (!serviciosCorreo.empty()) 
    {
        std::cout << "Servicios de correo electrónico utilizados: ";
        for (std::set<std::string>::iterator it = serviciosCorreo.begin(); it != serviciosCorreo.end(); ++it) 
        {
            std::cout << *it << ", ";
        }
        std::cout << std::endl;
    } 
    else 
    {
        std::cout << "No se identificaron servicios de correo electrónico claramente." << std::endl;
    }

    std::set<int> puertosUsados = EntradaService<Entrada>::usedPortsBelow1000(db);
    if (!puertosUsados.empty()) 
    {
        std::cout << "Puertos destino debajo de 1000 en uso:" << std::endl;
        for (std::set<int>::iterator it = puertosUsados.begin(); it != puertosUsados.end(); ++it) 
        {
            std::cout << *it;
            std::cout << std::endl;
        }
    } 
    else 
    {
        std::cout << "No se encontraron puertos destino debajo de 1000 en uso." << std::endl;
    }
    return 0;
}