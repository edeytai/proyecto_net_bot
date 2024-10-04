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
    std::stack<T>  conexionesEntrantes();
    std::vector<T>  conexionesSalientes();
   
    /* data */
public:

    ConexionesCompudatora(std::string ip, std::string nombre);
    void rellenarRegistros(std::vector<T> &db);
};

template <typename T>
ConexionesCompudatora<T>::ConexionesCompudatora(std::string ip, std::string nombre){
    
    ipComputadora = ip;
    nombreComputadora = nombre;
}

template <typename T>
inline void ConexionesCompudatora<T>::rellenarRegistros(std::vector<T> &db)
{

    std::cout << db.size() << std::endl;
    
}

#endif