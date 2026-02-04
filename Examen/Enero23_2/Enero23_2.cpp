#include <iostream>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

void buscarCamino(const bintree<int>& arb, int dragones, int& minDragones, int& mejorCamino)
{
    //Si esta vacio no podemos hacer nada, regresamos
    if (arb.empty()) return;

    //Revisamos los nodos
    int valor = arb.root();

    // Si es nodo dragon
    if (valor == 1) { dragones++; }

    // Si es hoja normal
    if (arb.left().empty() && arb.right().empty()) {
        // Es hoja (valor >= 3)
        //Si el camino es mejor, cogemos ese, y seguimos mirando
        if (dragones < minDragones) {
            minDragones = dragones;
            mejorCamino = valor;
        }
        return;
    }

    //Recursividad
    // Recorrer primero izquierda 
    if (!arb.left().empty()) buscarCamino(arb.left(), dragones, minDragones, mejorCamino);
    // Recorrer derecha
    if (!arb.right().empty()) buscarCamino(arb.right(), dragones, minDragones, mejorCamino);
}

int caminoConMenosDragones(bintree<int>& arb)
{
    int minDragones = INT_MAX; //Maximo posible
    int mejorCamino = -1; //Hoja vacia

    //Buscamos con los datos dados
    buscarCamino(arb, 0, minDragones, mejorCamino);

    //Devuelve mejor camino
    return mejorCamino;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracioon, y escribiendo la respuesta
void resuelveCaso() {
    bintree<int> arb;
    arb = leerArbol(-1);

    //Escribimos solucion
    cout << caminoConMenosDragones(arb) << endl;
    
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

