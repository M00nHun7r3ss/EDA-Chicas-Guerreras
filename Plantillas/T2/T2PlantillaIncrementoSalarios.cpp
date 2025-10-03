/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no: 
*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Complejidad:


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, inc;
    cin >> inc >> n;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    // Llamada a función y escritura de la salida
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input2.txt");
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
