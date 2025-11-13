//Denisa Juarranz Berindea
//EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

template <class T>
// Buscar el valor minimo en un arbol
/*
 Complejidad: Recorrera solo una rama del arbol, pero dado que todo
 el arbol puede estar en un solo lado, la complejidad sera O(n),
 siendo n la cantidad de nodos totales del arbol
 */
int minimo(bintree<T> const& tree)
{
    //Si no hay arbol, dara error
    if (tree.empty()) throw domain_error("Empty Tree");
    //Si el izquierdo esta vacio, la raiz es la mas pequenia
    if (tree.left().empty()) return tree.root();
    //Si no, sigue avanzando
    return minimo(tree.left());

    //El objetivo es llegar al nodo inferior mas a la izquierda
}

template <class T>
// Buscar el valor maximo en un arbol
/*
 Complejidad: Recorrera solo una rama del arbol, pero dado que todo
 el arbol puede estar en un solo lado, la complejidad sera O(n),
 siendo n la cantidad de nodos totales del arbol
 */
int maximo(bintree<T> const& tree) {

    //Si no hay arbol, dara error
    if (tree.empty()) throw domain_error("Empty Tree");
    //Si el derecho esta vacio, la raiz es la mas grande
    if (tree.right().empty()) return tree.root();
    //Si no, sigue avanzando
    return maximo(tree.right());

    //El objetivo es llegar al nodo inferior mas a la derecha
}

template <class T>
/*
 Complejidad: Dado que recorre una unica vez todos los nodos del arbol, la complejidad sera O(n),
 siendo n la cantidad de nodos totales del arbol
 */
bool resolver(bintree<T> const& tree, int minimo, int maximo)
{
    //Si esta vacio es de busqueda
    if (tree.empty()) return true;

    //Si es menor que el de la izquierda o mayor que el de la derecha, mo es de busqueda
    if (tree.root() <= minimo || tree.root() >= maximo)
    {
        return false;
    }

    //Comprobamos que los valores no sean iguales a la raiz
    if (!tree.left().empty() && tree.left().root() >= tree.root())
    {
        return false;
    }
    if (!tree.right().empty() && tree.right().root() <= tree.root())
    {
        return false;
    }

    //Hacemos la funcion recursiva de ambos lados
    //izquierdo && derecho
    return resolver(tree.left(), minimo, tree.root()) &&
        resolver(tree.right(), tree.root(), maximo);
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> tree;
    tree = leerArbol(-1);


    bool solucion;
    //No se donde hacerla comprobacion para que no me salte el error de arbol vacio, sin crear mas metodos
    //Si esta vacio es de busqueda
    if (tree.empty()) solucion = true;
    //Si no es vacio, tenemos que analizar. Correcciones de -1 y +1 porque los valores si pueden ser tan pequeños o grandes como estos
    else solucion = resolver(tree, minimo(tree) - 1, maximo(tree) + 1); 

    //Devolvera si o no segun si es o no de busqueda
    cout << (solucion ? "SI" : "NO") << endl;
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
