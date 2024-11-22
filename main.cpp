#include "Entrada.cpp"
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "EntradaService.cpp"
#include "ConexionesComputadora.cpp"
#include "BSTLectura.cpp"
#include "Graph.cpp"

int main(int argc, char const *argv[])
{
   
   
    std::vector<Entrada> db  = EntradaService<Entrada>::ObtenerDB("equipo2.csv");
    EntradaService<Entrada>::internalNetworkAddress(db);

    BSTLectura<Entrada> bstLectura;
    std::set<std::string> fechasUnicas;
   for (std::vector<Entrada>::iterator it = db.begin(); it != db.end(); ++it) 
   {
       fechasUnicas.insert(it->fecha);
   }
   int topN = 5;
   for (std::set<std::string>::iterator fecha = fechasUnicas.begin(); fecha != fechasUnicas.end(); ++fecha) 
   {
       bstLectura.top(db, *fecha, topN);
   }

   std::map<std::string, std::vector<conexionesEntrantes<Entrada> > > topPorDia = bstLectura.topPorDia(db, topN);
   bstLectura.top5TodosLosDias(topPorDia);
   bstLectura.apareceUnDiaYSubsecuentes(topPorDia);
   bstLectura.sitioConMuchasConexiones(topPorDia);
   
   std::string direccionRedInternaPc = EntradaService<Entrada>::internalNetworkAddress(db);
    ConexionesComputadora<Entrada> pc1 = ConexionesComputadora<Entrada> (direccionRedInternaPc, "mi pc");
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



 Graph<std::string, std::string> * multilista = new Graph<std::string, std::string>();

 Graph<std::string, std::string> * multilistaSitiosWeb = new Graph<std::string, std::string>();
const std::string ipInterna= "192.168.86.85";
multilista->loadGraphFromEntradas(db);
multilista->obtenerConexPorIp(ipInterna, true);
multilista->obtenerConexPorIpDia(ipInterna, true);
multilista->mayorNodoConConexiones();
const std::string sitioB= "merriam-webster.com";
const std::string sitioC= "homedepot.com";
const std::string sitioD= "gmail.com";
multilistaSitiosWeb->loadGraphFromEntradasWeb(db);
//multilistaSitiosWeb->obtenerConexPorIp(sitioB, true);
//multilistaSitiosWeb->obtenerConexPorIpDia(sitioB, true);
//multilistaSitiosWeb->mayorNodoConConexiones();
multilistaSitiosWeb->obtenerConexPorIp(sitioD, true);
multilistaSitiosWeb->obtenerConexPorIpDia(sitioD, true);

    return 0;



    


        
}

