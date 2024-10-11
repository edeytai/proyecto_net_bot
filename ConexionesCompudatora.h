#ifndef ConexionesCompudatora_H  
#define ConexionesCompudatora_H 
#include <string>
#include <iostream>
#include <stack>
#include <vector>

template<typename T>
class ConexionesCompudatora
{
private:
    std::string  ipComputadora;
    std::string  nombreComputadora;
    std::vector<T>  conexionesEntrantes;
    std::vector<T>  conexionesSalientes;
   
    /* data */
public:

    ConexionesCompudatora(std::string ip, std::string nombre);
    void rellenarRegistros(std::vector<T> &db);
    void comprobarRegistrosConsecutivos();
};

template <typename T>
ConexionesCompudatora<T>::ConexionesCompudatora(std::string ip, std::string nombre){
    std::string valoresUsuario;
    ipComputadora = ip;
    ip.pop_back();
    std::cout << "Ingresa un número del 1 al 150 para crear tu dirección ip interna: " << std::endl;
    
    std::cin >> valoresUsuario;
     
     ipComputadora = ip;
     ipComputadora += valoresUsuario;
    nombreComputadora = nombre;
}

template <typename T>
inline void ConexionesCompudatora<T>::rellenarRegistros(std::vector<T> &db)
{
    for (size_t i = 0; i < db.size(); i++)
    {
        if (ipComputadora ==db[i].ipDestino)
        {
            conexionesEntrantes.push_back(db[i]);
        }
        if (ipComputadora ==db[i].ipOrigen)
        {
            conexionesSalientes.push_back(db[i]);
          
        }
        
        

    }
    std::cout << "" << std::endl;
    std::cout << "______________________________" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "La base de registros tiene un total de " << db.size()<< " registros, la ip de la computadora es "<< ipComputadora<<  std::endl;
    std::cout << "Hay un total de conexiones entrantes: " << conexionesEntrantes.size()<< std::endl;
    std::cout << "Hay un total de conexiones salientes: " << conexionesSalientes.size()<< std::endl;
    std::cout << "" << std::endl;
    std::cout << "______________________________" << std::endl;
    std::cout << "" << std::endl;
    
}

template <typename T>
void ConexionesCompudatora<T>::comprobarRegistrosConsecutivos()
{
    int contadorConsecutivos = 0;
    int maxConsecutivos = 0;

    if (conexionesSalientes.size() < 2) 
    {
        std::cout << "No hay suficientes conexiones salientes para comprobar registros consecutivos." << std::endl;
        return;
    }
    for (size_t i = 1; i < conexionesSalientes.size(); i++) 
    {
        if (conexionesSalientes[i].ipDestino == conexionesSalientes[i - 1].ipDestino)
        {
            contadorConsecutivos++;
        } 
        else 
        {
            if (contadorConsecutivos > maxConsecutivos) 
            {
                maxConsecutivos = contadorConsecutivos;
            }
            contadorConsecutivos = 0;
        }
    }
    if (contadorConsecutivos > maxConsecutivos) 
    {
        maxConsecutivos = contadorConsecutivos;
    }

    std::cout << "La IP " << ipComputadora << " tuvo un máximo de " << (maxConsecutivos + 1) << " conexiones consecutivas con el mismo destino." << std::endl;
}

#endif