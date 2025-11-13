//Denisa Juarranz Berindea
//EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

template <class T>
/*
 Complejidad: Dado que recorre una unica vez todos los nodos del arbol, la complejidad sera O(n),
 siendo n la cantidad de nodos totales del arbol
 */
int resolver(bintree<T> const& tree, int &diametro) {

    //Si no hay arbol, no seguimos. No hay camino
    if (tree.empty()) return 0;

    //Ahora comprobaremos cada lado, por separado, calculando sus diametros
    int diametroIzqda = resolver(tree.left(), diametro);
    int diametroDcha = resolver(tree.right(), diametro);

    // El camino mas largo que pasa por este nodo es la suma de los diametros de cada lado y la raiz
    int caminoActual = diametroIzqda + diametroDcha + 1;

    // Si este camino es más largo que el mejor que teníamos, actualizamos
    diametro = max(diametro, caminoActual);

    // Devolvemos la rama mas larga (teniendo en cuenta el nodo actual) de caa a recursividad
	return 1 + max(diametroIzqda, diametroDcha);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<char> tree;
    tree = leerArbol('.');

    //El diametro inicialmente es 0
    int diametro = 0;

    //Resolvemos, pasando el diametro por referencia, para que se vaya modificando sobre la marcha
    resolver(tree, diametro);

    //Escribimos la solucion
    cout << diametro << endl;
}


//#define DOMJUDGE
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
