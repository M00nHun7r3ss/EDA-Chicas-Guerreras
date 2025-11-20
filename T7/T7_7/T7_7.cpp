// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <fstream>
using namespace std;


using DNI = string;

class carnet_puntos {
private:
    //Registro de dni y puntos
    unordered_map<string, int> conductores;
    //Vector de tamanio 16 (de 0 a 15) con el numero de conductores con cada cantidad de puntos
    vector<int> contador;                 

public:
    //Constructora inicializa contadores a 0
    carnet_puntos() : contador(16, 0) {}

    // Complejidad: O(1)
	// Aniade un nuevo conductor con 15 puntos
    // Lanza excepcion si el conductor ya existe
    void nuevo(DNI const& conductor) {
        //Si ya se ha registrado el dni
        if (conductores.count(conductor)) //Complejidad O(1)
            //Lanza error
            throw domain_error("Conductor duplicado");
        //Sino, aniade 15 puntos al conductor  //Complejidad O(1)
        conductores[conductor] = 15;
        //Y lo aniade al contador de conductores con 15 puntos  //Complejidad O(1)
        contador[15]++;                        
    }
    

    // Complejidad: O(1)
	// Quita puntos a un conductor al cometer una infraccion
    // Lanza excepcion si el conductor ya existe
    void quitar(DNI const& conductor, int puntos) {

        //Buscamos al conductor //Complejidad O(1)
        auto cond = conductores.find(conductor);
        //Si no se ha encontrado //Complejidad O(1)
        if (cond == conductores.end())
            //Lanza error
            throw domain_error("Conductor inexistente");

        //En base a los puntos que habia antes
        int punt = cond->second;
        //Actualizamos el contador, quitando uno de ese numero de puntos //Complejidad O(1)
        contador[punt]--;                       
        //Calculamos los nuevos, con un minimo de 0 puntos
    	punt -= puntos;
        if (punt <= 0)
        {
            punt = 0;
        }
		//Actualizamos los puntos nuevos
        cond->second = punt;                     
        //Actualizamos el contador, aniadiendo uno de ese numero de puntos //Complejidad O(1)
        contador[punt]++;                   
    }

    // Complejidad : O(1)
	// Consulta los puntos actuales de un conductor
    // Lanza excepcion si el conductor no existe
    int consultar(DNI const& conductor) const {

        //Buscamos al conductor //Complejidad O(1)
        auto cond = conductores.find(conductor);
        //Si no se ha encontrado //Complejidad O(1)
        if (cond == conductores.end())
            //Lanza error
            throw domain_error("Conductor inexistente");

        //Si no, devuelve el numero de puntos del conductor
        return cond->second;                     
    }

    // Complejidad: O(1)
	// Devuelve cuantos conductores tienen un numero determinado de puntos (dicha posicion en el vector contador)
    // Lanza excepción si el numero de puntos no es valido (0-15)
    int cuantos_con_puntos(int puntos) const {

        //Si el numero de puntos no es valido //Complejidad O(1)
        if (puntos < 0 || puntos > 15)
            //Lanza error
            throw domain_error("Puntos no validos");

        //Sino, devuelve el contador //Complejidad O(1)
        return contador[puntos];           
    }
};

bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;

    carnet_puntos dgt;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                cin >> dni;
                dgt.nuevo(dni);
            }
            else if (orden == "quitar") {
                cin >> dni >> punt;
                dgt.quitar(dni, punt);
            }
            else if (orden == "consultar") {
                cin >> dni;
                punt = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << punt << '\n';
            }
            else if (orden == "cuantos_con_puntos") {
                cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            }
            else
                cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}


int main() {
    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("pause");
#endif
    return 0;
}
