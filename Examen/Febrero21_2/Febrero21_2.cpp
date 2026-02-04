#include <iostream>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

template <class T>
bool esSimetrica(const bintree<T>& a, const bintree<T>& b) {
    // Ambos lados vacios - simetrica
    if (a.empty() && b.empty()) return true;

    // Uno vacío y otro no - no simetrica
    if (a.empty() || b.empty()) return false;

    // Comparar subarboles cruzados 
    return esSimetrica(a.left(), b.right()) &&
        esSimetrica(a.right(), b.left());
}

template <class T>
bool resolver(const bintree<T>& arb) {
    // Árbol vacío o un solo nodo - simetrico
    if (arb.empty()) return true;

    //Comprobacion general
    return esSimetrica(arb.left(), arb.right());
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuracioon, y escribiendo la respuesta
void resuelveCaso() {
    bintree<char> arb;
    arb = leerArbol('.');

    //Escribimos solucion
    if (resolver(arb))
        cout << "SI" << endl;
    else
        cout << "NO" << endl;

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

