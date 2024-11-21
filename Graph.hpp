//
//  Graph.hpp
//  Graph
//
//  Created by Vicente Cubells on 10/11/20.
//

#ifndef Graph_hpp
#define Graph_hpp
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Vertex.hpp"
#include <set>


template <class V, class E>
class Graph {
    
    std::vector < Vertex<V, E> * > nodes;
    
public:
    
    Graph() {}
    ~Graph();
    void obtenerConexPorIpDia(std::string, bool mostrarInfo );
    int obtenerConexPorIp(std::string, bool );
    void mayorNodoConConexiones( );
    void addVertex(V & );
    void addVertex(Vertex<V,E> * );
    void addEdge(Vertex<V,E> *, Vertex<V,E> *, const E & );
    void removeEdge(Vertex<V,E> *, Vertex<V,E> *, const E & );
    
    Vertex<V, E> * search(const V & );
    Vertex<V, E> * search(const Vertex<V,E> *);
    
    void getIncidentePorVertex();
    void loadGraphFromEntradas(std::vector<Entrada> registros);
    void loadGraphFromEntradasWeb(std::vector<Entrada> registros);

    template <class Vn, class En>
    friend std::ostream & operator <<(std::ostream &, const Graph<Vn,En> &);
};

template <class V, class E>
Graph<V,E>::~Graph()
{
    for (auto v: nodes) {
        delete v;
    }
    
    nodes.clear();
}



template <class V, class E>
void Graph<V,E>::addVertex(V & value )
{
    auto vertex = new Vertex<V, E>(value);
    
    nodes.push_back(vertex);
}

template <class V, class E>
void Graph<V,E>::addVertex(Vertex<V,E> * vertex )
{
    nodes.push_back(vertex);
}

template <class V, class E>
void Graph<V,E>::addEdge(Vertex<V,E> * source, Vertex<V,E> * target, const E & value)
{
    /* Buscar vertex origen */
    auto node = find(nodes.begin(), nodes.end(), source);
    
    /* Crear un edge y adicionarlo al vertex */
    Edge<V, E> * edge = new Edge<V,E>(value, target);
    
    (*node)->addEdge(edge);
}

template <class V, class E>
void Graph<V,E>::removeEdge(Vertex<V,E> * source, Vertex<V,E> * target, const E & value )
{
    /* Buscar vertex origen */
    auto node = find(nodes.begin(), nodes.end(), source);
    
    Vertex<V,E> * vertex = (*node);
    
    auto * edges = vertex->getEdges();
    
    Edge<V,E> * to_remove = nullptr;
    
    for (auto e : *edges) {
        if (e->getInfo() == value && e->getTarget() == target) {
            to_remove = e;
            break;
        }
    }
    
    if (to_remove) {
        vertex->removeEdge(to_remove);
    }
    
}

template <class V, class E>
Vertex<V, E> * Graph<V,E>::search(const V & value )
{
    /* Crear un nodo */
    Vertex<V,E> * vertex = new Vertex<V, E>(value);
    
    /* Buscar vertex */
    auto node = search(vertex);
    
    /* Eliminar el nodo temporal */
    delete vertex;
    
    /* Regresar el nodo encontrado */
    return node;
}

template <class V, class E>
Vertex<V, E> * Graph<V,E>::search(const Vertex<V,E> * value )
{
    /* Buscar vertex */
    //auto node = find(nodes.begin(), nodes.end(), value);
    bool found = false;
    Vertex<V,E> * vertex = nullptr;
    
    for (auto n : nodes) {
        if (*n == *value) {
            found = true;
            vertex = n;
            break;
        }
    }
    
    return vertex;
}

template <class V, class E>
void Graph<V,E>::getIncidentePorVertex()
{
    for (auto v : nodes) {
        std::cout << v->getInfo() << " : " << v->getIncidentesEntrada();
        std::cout << std::endl;
    }
}

template <class V, class E>
std::ostream & operator <<(std::ostream & os, const Graph<V,E> & graph)
{
    os << "--- Graph ---" << std::endl;
    
    for (auto v :  graph.nodes) {
        os << *v;
    }
    
    return os;
}

template <class V, class E>
inline int Graph<V, E>::obtenerConexPorIp(std::string ip, bool mostrarInfo)
{

    int contador= 0;
        // Buscar el vértice por su valor
    Vertex<V, E>* vertex = search(ip);
    
    if (vertex == nullptr) {
        std::cout << "No se encontró un vértice con la IP especificada." << std::endl;
        return contador;
    }

    // Obtener las aristas del vértice encontrado
    std::vector<Edge<V, E>*>* edges = vertex->getEdges();

    

    // Recorrer y mostrar cada arista
    for (auto edge : *edges) {
        contador++;
   
        //std::cout << " - Conexión a: " << edge->getTarget()->getInfo() 
        //          << ", Información de la conexión: " << edge->getInfo() << std::endl;
    }
    if (mostrarInfo)
    {
        std::cout << "Conexiones del nodo " << ip << ":" << std::endl;
          std::cout << "este nodo tiene " << contador<< " conexiones"<< std::endl;
    }
    
       
         return contador;
}
template <class V, class E>
inline void Graph<V, E>::obtenerConexPorIpDia(std::string ip, bool mostrarInfo) {
    std::map<std::string, int> conexionesPorDia;                // Mapa para almacenar las conexiones agrupadas por fecha
    std::map<std::string, std::set<std::string>> ipsPorDia;     // Mapa para almacenar las IPs únicas conectadas por fecha

    // Buscar el vértice por su valor (IP)
    Vertex<V, E>* vertex = search(ip);
    if (vertex == nullptr) {
        std::cout << "No se encontró un vértice con la IP especificada." << std::endl;
        return;
    }

    // Obtener las aristas (conexiones) del vértice encontrado
    std::vector<Edge<V, E>*>* edges = vertex->getEdges();

    // Recorrer cada arista y contar las conexiones y IPs únicas por fecha
    for (auto edge : *edges) {
        std::string fecha = edge->getInfo();                   // Suponiendo que `getInfo()` de Edge retorna la fecha
        std::string ipDestino = edge->getTarget()->getInfo();  // Obtener la IP destino desde el vértice de destino
        
        conexionesPorDia[fecha]++;                             // Incrementar el contador de conexiones para esa fecha
        ipsPorDia[fecha].insert(ipDestino);                    // Insertar la IP destino en el conjunto de IPs para esa fecha
    }

    // Mostrar la información si se solicita
    if (mostrarInfo) {
        std::cout << "Conexiones del nodo " << ip << " por día:" << std::endl;
        for (const auto& [fecha, cantidad] : conexionesPorDia) {
            int conexionesUnicas = ipsPorDia[fecha].size();
            std::cout << "Fecha: " << fecha 
                      << ", Conexiones: " << cantidad 
                      << ", Computadoras distintas conectadas: " << conexionesUnicas 
                      << std::endl;
        }
    }

    return;
}


template <class V, class E>
inline void Graph<V, E>::mayorNodoConConexiones() {
    int maxConexiones = 0;
    std::string ipMaxima;
    
    for (auto& node : nodes) {
        std::string ip = node->getInfo();  // Obtener la IP del nodo actual
        int conexiones = obtenerConexPorIp(ip, false);  // Contar las conexiones de este nodo

        // Comparar con el máximo actual
        if (conexiones > maxConexiones) {
            maxConexiones = conexiones;
            ipMaxima = ip;
        }
    }

    // Imprimir el nodo con el mayor número de conexiones
    if (!ipMaxima.empty()) {
        std::cout << "El nodo con más conexiones es: " << ipMaxima 
                  << " con " << maxConexiones << " conexiones." << std::endl;
    } else {
        std::cout << "No se encontraron nodos con conexiones." << std::endl;
    }
}

template <class V, class E>
void Graph<V, E>::loadGraphFromEntradas(std::vector<Entrada> registros) {
    int nregistros = 0;
    
    for (const auto& entrada : registros) {
  
        if (search(entrada.ipOrigen) == nullptr) {
            addVertex(new Vertex<V, E>(entrada.ipOrigen));
            nregistros++;
        }
        if (search(entrada.ipDestino) == nullptr) {
            addVertex(new Vertex<V, E>(entrada.ipDestino));
            nregistros++;
        }
        
 
        Vertex<V, E> * origen = search(entrada.ipOrigen);
        Vertex<V, E> * destino = search(entrada.ipDestino);
        addEdge(origen, destino, entrada.fecha);
    }
     std::cout << "Grafo cargado con " << nregistros<< " nodos"<< std::endl;
    }
    
 
template<class V, class E>
inline void Graph<V, E>::loadGraphFromEntradasWeb(std::vector<Entrada> registros)
{ int nregistros = 0;
    
    for (const auto& entrada : registros) {
  
        if (search(entrada.nombreOrigen) == nullptr) {
            addVertex(new Vertex<V, E>(entrada.nombreOrigen));
            nregistros++;
        }
        if (search(entrada.nombreDestino) == nullptr) {
            addVertex(new Vertex<V, E>(entrada.nombreDestino));
            nregistros++;
        }
        
 
        Vertex<V, E> * origen = search(entrada.nombreOrigen);
        Vertex<V, E> * destino = search(entrada.nombreDestino);
        addEdge( destino, origen,entrada.fecha);
    }

    std::cout << "Grafo cargado con " << nregistros<< " nodos"<< std::endl;
}

#endif /* Graph_hpp */