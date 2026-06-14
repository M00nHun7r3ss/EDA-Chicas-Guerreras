#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

template <class T>
bool sonEspejo(bintree<T> const& a, bintree<T> const& b) {
    // Si ambos estan vacios, son simetricos
    if (a.empty() && b.empty()) {
        return true;
    }
    // Si uno esta vacio y el otro no, ya no hay simetría
    if (a.empty() || b.empty()) {
        return false;
    }
    // Si tienen contenido, deben coincidir sus raíces Y sus hijos de forma cruzada
    return (a.root() == b.root()) &&
        sonEspejo(a.left(), b.right()) &&
        sonEspejo(a.right(), b.left());
}

template <class T>
bool simetrico(bintree<T> const& tree) {
    // Caso base, un arbol vacio es simetrico
    if (tree.empty()) {
        return true;
    }
    // Comparamos derecha e izquierda
    return sonEspejo(tree.left(), tree.right());
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    bintree<char> tree;
    tree = leerArbol('.');

    if (simetrico(tree)) {
        cout << "SI\n";
    }
    else {
        cout << "NO\n";
    }
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
