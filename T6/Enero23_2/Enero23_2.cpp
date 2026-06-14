
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <climits>
#include "bintree_eda.h"
using namespace std;

// Estructura para almacenar el resultado 
struct Solucion {
    int numDragones; // Numero de dragones minimo en el camino
    int idHoja;      // Identificador de la hoja elegida
};

// Complejidad: O(n)
Solucion resolver(bintree<int> const& a) {
    // Caso base: Si detectamos una hoja (no hijos)
    if (a.left().empty() && a.right().empty()) {
        // No sumamos dragones
        return { 0, a.root() }; 
    }

    // Si alguno de los dos hijos esta vacio, vamos hacia el otro
    if (a.left().empty()) {
        Solucion der = resolver(a.right());
        if (a.root() == 1) der.numDragones++;
        return der;
    }
    if (a.right().empty()) {
        Solucion izq = resolver(a.left());
        if (a.root() == 1) izq.numDragones++;
        return izq;
    }

    // Caso normal, el nodo tiene ambos hijos disponibles. Miramos ambos lados
    Solucion izq = resolver(a.left());
    Solucion der = resolver(a.right());

    Solucion mejor;

    // Seleccionamos el camino con menos dragones. 
    // En caso de empate (<=), elegimos el izquierdo
    if (izq.numDragones <= der.numDragones) {
        mejor = izq;
    }
    else {
        mejor = der;
    }

    // Sumamos el dragon del nodo actual si corresponde
    if (a.root() == 1) {
        mejor.numDragones++;
    }

    return mejor;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> arbol;
    int capacidad;
    arbol = leerArbol(-1);

    // Si el arbol esta vacio (no deberia), no hacemos nada
    if (arbol.empty()) return;

    Solucion sol = resolver(arbol);

    cout << sol.idHoja << "\n";
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
