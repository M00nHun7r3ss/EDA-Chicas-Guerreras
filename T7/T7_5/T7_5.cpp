// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

/*
 Complejidad:
 Usare las siguientes variables para explicar la complejidad
 nEnvs (numero de envios totales. Todos los intentos de todos los equipos)
 nEqs (numero de equipos)
 nProbs (numero de problemas)

La complejidad seria en el peor caso O(nEnvs) + O(nEqs * nProbs) + O(nEqs * log nEqs) + O (nEqs)
Leer los envios tiene una complejidad O(nEnvs) siendo n el numero de envios
Revisar los envios y rellenar el resultado tiene una complejidad O(nEqs * nProbs)
Ordenar los resultados tiene una complejidad O(nEqs * log nEqs)
Escribir el resultado tiene una complejidad O(nEqs)
 */

void procesaEnvios(vector<pair<string, pair<int, int>>>& resultados) {
    string equipo, problema, veredicto;
    int minuto;
    //Registro de toda la informacion del envio: equipo, intentos, timepo
    unordered_map<string, unordered_map<string, pair<int, int>>> enviosEquipo;

    //Leemos el equipo
    cin >> equipo;

    //Si no ha llegado al final de la lista
    //Complejidad del while O(n) siendo n el numero de envios a consultar (la suma de todos los intentos de todos los equipos)
    while (equipo != "FIN") {
        //Leemos todos los datos de la salida del juez
        cin >> problema >> minuto >> veredicto;

        //Registra por cada problema al equipo
        unordered_map<string, pair<int, int>>& problemas = enviosEquipo[equipo];

        //Revisa los veredictos
        //Si sale bien
        if (veredicto == "AC") {
            // Si no hay AC previo, guardamos el minuto del primer AC
            if (problemas[problema].second == 0) {
                problemas[problema].second = minuto;
            }
        }
        else {
            // Si no se ha resuelto aún, aumentamos los intentos fallidos
            if (problemas[problema].second == 0) {
                problemas[problema].first++;
            }
        }

        //Procesa el siguiente equipo
        cin >> equipo;
    }

    //Revisamos los resultados para gestionar la salida y rellenar el resultado
    //Complejidad O(n * m) siendo n el numero de equipos y m el numero de problemas de cada equipo
    for (auto& e : enviosEquipo) {
        int problemasResueltos = 0, tiempoTotal = 0;

        //Recorremos los problemas del equipo
        for (pair<const string, pair<int, int>>& problem : e.second) {

            //Si se ha resuelto el problema
            if (problem.second.second != 0) {

                problemasResueltos++;
                tiempoTotal += problem.second.second + 20 * problem.second.first;
            }
        }

        //Guardamos el resultado del equipo
        resultados.push_back({ e.first, {problemasResueltos, tiempoTotal}});
    }

   // Ordenamos por numero de problemas resueltos, menos tiempo y orden alfabetico
   // De principio a fin, comparamos dos a dos resultado de equipo
   // Complejidad del sort: O(n log n) siendo n el numero de resultados asociados a cada equipo
    sort(resultados.begin(), resultados.end(), [](const pair<string, pair<int, int>>& a, const pair<string, pair<int, int>>& b) {
        //Mayor numero de problemas resuelto
        if (a.second.first != b.second.first)
            return a.second.first > b.second.first;
        //Menor tiempo necesitado
        if (a.second.second != b.second.second)
            return a.second.second < b.second.second;
        //Orden alfabetico
        return a.first < b.first; 
    });
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    //Vector de nombre del equipo, n problemas resueltos, n minutos tiempo
    vector<pair<string, pair<int, int>>> resultados;
	procesaEnvios(resultados);

    // Se imprime la salida: nombre del equipo, n problemas resueltos, n minutos tiempo
    //Complejidad O(n) siendo n el numero de resultados
    for (pair<string, pair<int, int>>& result : resultados)
    {
        cout << result.first << " " << result.second.first << " " << result.second.second << "\n";
    }
	cout << "---\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}