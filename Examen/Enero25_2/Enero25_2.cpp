#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

struct Info {
    int suma;       // suma de abajo
    int cont;       // nodos acumuladores
};

template <class T>
Info acumuladores(const bintree<T>& tree) {
    // arbol vacio - no hay nada que hacer
    if (tree.empty()) {
        return { 0, 0 };
    }

    // Recursividad en hijos
    Info iz = acumuladores(tree.left());
    Info dr = acumuladores(tree.right());

    // Suma de descendientes de ambas ramas
    int sumaDesc = iz.suma + dr.suma;

    // Total acumuladores hasta ahora de ambas ramas
    int cont = iz.cont + dr.cont;

    // Comprobar si el nodo actual es acumulador (lo de arriba y lo de abajo suma igual)
    if (tree.root() == sumaDesc) {
        cont++;
    }

    // Suma total del subarbol (incluyendo el nodo actual)
    int sumaTotal = sumaDesc + tree.root();

    return { sumaTotal, cont };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> tree;
    tree = leerArbol(-1);

    //Pasa la solucion
    cout << acumuladores(tree).cont << endl;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    ifstream in("datos.txt");
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
