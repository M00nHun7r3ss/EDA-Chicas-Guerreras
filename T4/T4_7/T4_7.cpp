// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Set.h"
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
//Basado en la plantilla del ejercicio 4_5
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, e;
    Set<int> set1, set2;

    cin >> n;
    if (!cin) return false;

    //Leemos el primer conjunto
    for (int i = 0; i < n; i++) {
        cin >> e; set1.add(e);
    }

    //Leemos el segundo conjunto
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> e; set2.add(e);
    }

    //Resultado del operador <= (true = 1, false = 0)
    cout << (set1 <= set2) << endl;

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}