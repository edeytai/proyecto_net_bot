#ifndef BSTLECTURA_H
#define BSTLECTURA_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

template <typename T>
class conexionesEntrantes 
{
    public:
    int cantidad;
    std::string dominio;

    conexionesEntrantes() : cantidad(0), dominio("") {}
    conexionesEntrantes(const std::string& dom, int cant) : dominio(dom), cantidad(cant) {}

    bool operator<(const conexionesEntrantes& otra) const 
    {
        return cantidad > otra.cantidad;
    }

    friend std::ostream& operator<<(std::ostream& os, const conexionesEntrantes& con) 
    {
        os << con.dominio << " con " << con.cantidad << " conexiones";
        return os;
    }
};

template <typename T>
class BSTLectura 
{
    public:
    std::map<std::string, int> conexionesPorDia(const std::vector<T>& db, const std::string& fecha);
    void top(const std::vector<T>& db, const std::string& fecha, int topN);
    std::map<std::string, std::vector<conexionesEntrantes<T> > > topPorDia(const std::vector<T>& db, int n);
    void top5TodosLosDias(const std::map<std::string, std::vector<conexionesEntrantes<T> > >& topnporfecha);
    void apareceUnDiaYSubsecuentes(const std::map<std::string, std::vector<conexionesEntrantes<T> > >& topnporfecha);
    void sitioConMuchasConexiones(const std::map<std::string, std::vector<conexionesEntrantes<T> > >& topnporfecha);

    private:
    bool dominioEnConexiones(const std::vector<conexionesEntrantes<T> >& conexiones, const std::string& dominio);
};

template <typename T>
std::map<std::string, int> BSTLectura<T>::conexionesPorDia(const std::vector<T>& db, const std::string& fecha) 
{
    std::map<std::string, int> conexiones;
    for (typename std::vector<T>::const_iterator it = db.begin(); it != db.end(); ++it) 
    {
        if (it->fecha == fecha && it->nombreDestino != "-" && 
            it->nombreDestino.find(".reto.com") == std::string::npos &&
            (it->puertoDestino == 80 || it->puertoDestino == 443)) 
        {
            conexiones[it->nombreDestino]++;
        }
    }
    return conexiones;
}

template <typename T>
void BSTLectura<T>::top(const std::vector<T>& db, const std::string& fecha, int topN) 
{
    std::map<std::string, int> conexionesMap = conexionesPorDia(db, fecha);
    std::vector<conexionesEntrantes<T> > conexionesVec;
    for (typename std::map<std::string, int>::iterator it = conexionesMap.begin(); it != conexionesMap.end(); ++it) 
    {
        conexionesVec.push_back(conexionesEntrantes<T>(it->first, it->second));
    }
    std::sort(conexionesVec.begin(), conexionesVec.end());
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "Top " << topN << " conexiones para la fecha " << fecha << ":\n";
    for (int i = 0; i < topN && i < conexionesVec.size(); ++i) 
    {
        std::cout << conexionesVec[i] << std::endl;
    }
}

template <typename T>
std::map<std::string, std::vector<conexionesEntrantes<T> > > BSTLectura<T>::topPorDia(const std::vector<T>& db, int n) 
{
    std::set<std::string> fechasUnicas;
    for (typename std::vector<T>::const_iterator it = db.begin(); it != db.end(); ++it) 
    {
        if (it->puertoDestino == 80 || it->puertoDestino == 443) 
        {
            fechasUnicas.insert(it->fecha);
        }
    }
    std::map<std::string, std::vector<conexionesEntrantes<T> > > topConexionesPorDia;
    for (std::set<std::string>::iterator fechaIt = fechasUnicas.begin(); fechaIt != fechasUnicas.end(); ++fechaIt) 
    {
        std::map<std::string, int> conexionesMap = conexionesPorDia(db, *fechaIt);
        std::vector<conexionesEntrantes<T> > conexionesVec;
        for (typename std::map<std::string, int>::iterator it = conexionesMap.begin(); it != conexionesMap.end(); ++it) 
        {
            conexionesVec.push_back(conexionesEntrantes<T>(it->first, it->second));
        }
        std::sort(conexionesVec.begin(), conexionesVec.end());
        if (conexionesVec.size() > n) {
            conexionesVec.resize(n);
        }
        topConexionesPorDia[*fechaIt] = conexionesVec;
    }
    return topConexionesPorDia;
}

template <typename T>
void BSTLectura<T>::top5TodosLosDias(const std::map<std::string, std::vector<conexionesEntrantes<T> > >& topnporfecha) 
{
    std::map<std::string, int> dominioFrecuencia;
    for (typename std::map<std::string, std::vector<conexionesEntrantes<T> > >::const_iterator it = topnporfecha.begin(); it != topnporfecha.end(); ++it) 
    {
        for (typename std::vector<conexionesEntrantes<T> >::const_iterator vecIt = it->second.begin(); vecIt != it->second.end(); ++vecIt) 
        {
            dominioFrecuencia[vecIt->dominio]++;
        }
    }
    for (typename std::map<std::string, int>::const_iterator it = dominioFrecuencia.begin(); it != dominioFrecuencia.end(); ++it) 
    {
        std::cout << "--------------------------------------------------------------\n";
        std::cout << it->first << " aparece en " << it->second << " días.\n";
    }
}

template <typename T>
void BSTLectura<T>::apareceUnDiaYSubsecuentes(const std::map<std::string, std::vector<conexionesEntrantes<T> > >& topnporfecha) 
{
    std::set<std::string> dominiosImpresos;
    for (typename std::map<std::string, std::vector<conexionesEntrantes<T> > >::const_iterator it = topnporfecha.begin(); it != topnporfecha.end(); ++it) 
    {
        for (typename std::vector<conexionesEntrantes<T> >::const_iterator vecIt = it->second.begin(); vecIt != it->second.end(); ++vecIt) 
        {
            if (dominiosImpresos.find(vecIt->dominio) != dominiosImpresos.end()) continue;

            bool apareceEnTodos = true;
            for (typename std::map<std::string, std::vector<conexionesEntrantes<T> > >::const_iterator sigIt = std::next(it); sigIt != topnporfecha.end(); ++sigIt) 
            {
                if (!dominioEnConexiones(sigIt->second, vecIt->dominio)) 
                {
                    apareceEnTodos = false;
                    break;
                }
            }

            if (apareceEnTodos) 
            {
                std::cout << "--------------------------------------------------------------\n";
                std::cout << vecIt->dominio << " aparece en " << it->first << " y en todos los días subsecuentes.\n";
                dominiosImpresos.insert(vecIt->dominio);
            }
        }
    }
}

template <typename T>
bool BSTLectura<T>::dominioEnConexiones(const std::vector<conexionesEntrantes<T> >& conexiones, const std::string& dominio) 
{
    for (typename std::vector<conexionesEntrantes<T> >::const_iterator it = conexiones.begin(); it != conexiones.end(); ++it) 
    {
        if (it->dominio == dominio) 
        {
            return true;
        }
    }
    return false;
}

template <typename T>
void BSTLectura<T>::sitioConMuchasConexiones(const std::map<std::string, std::vector<conexionesEntrantes<T> > >& topnporfecha) 
{
    for (typename std::map<std::string, std::vector<conexionesEntrantes<T> > >::const_iterator it = topnporfecha.begin(); it != topnporfecha.end(); ++it) 
    {
        int totalConexiones = 0;
        for (typename std::vector<conexionesEntrantes<T> >::const_iterator vecIt = it->second.begin(); vecIt != it->second.end(); ++vecIt) 
        {
            totalConexiones += vecIt->cantidad;
        }
        double promedio = static_cast<double>(totalConexiones) / it->second.size();
        std::cout << "--------------------------------------------------------------\n";
        std::cout << "Sitios con conexiones superiores al promedio para el día " << it->first << ":\n";
        for (typename std::vector<conexionesEntrantes<T> >::const_iterator vecIt = it->second.begin(); vecIt != it->second.end(); ++vecIt) 
        {
            if (vecIt->cantidad > promedio) 
            {
                std::cout << vecIt->dominio << " con " << vecIt->cantidad << " conexiones\n";
            }
        }
    }
}
#endif