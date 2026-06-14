#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

struct Resultado {
    int sumaDescendientes; // Suma de todos los valores por debajo de este nodo
    int numAcumuladores;   // Contador de nodos acumuladores
};

template <class T>
Resultado acumuladores(bintree<T> const& tree) {
    // Caso base: Si el erbol esta vacío, la suma es 0 y no hay acumuladores.
    if (tree.empty()) {
        return { 0, 0 };
    }

    // Procesamos primero las ramas hijas
    Resultado izq = acumuladores(tree.left());
    Resultado der = acumuladores(tree.right());

    // Calculamos la suma de todos los descendientes del nodo actual
    // Es la suma de los descendientes de los hijos mas los valores de los hijos
    int sumaHijoIzq = tree.left().empty() ? 0 : tree.left().root();
    int sumaHijoDer = tree.right().empty() ? 0 : tree.right().root();

    int sumaTotalDescendientes = (izq.sumaDescendientes + sumaHijoIzq) +
        (der.sumaDescendientes + sumaHijoDer);

    // Sumamos los contadores de acumuladores de ambos lados
    int acumuladoresSubarbol = izq.numAcumuladores + der.numAcumuladores;

    // Evaluamos si el nodo actual cumple la condicion de nodo acumulador
    if (tree.root() == T(sumaTotalDescendientes)) {
        acumuladoresSubarbol++;
    }

    // Devolvemos 
    return { sumaTotalDescendientes, acumuladoresSubarbol };
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> tree;
    tree = leerArbol(-1);

    Resultado res = acumuladores(tree);

    cout << res.numAcumuladores << "\n";
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
