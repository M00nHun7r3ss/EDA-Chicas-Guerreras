#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"

using namespace std;

// función que resuelve el problema y justificación del coste
template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:
    void eliminaElem(T const& elem) {

        //El fantasma
        Nodo* fant = this->fantasma;
        //El primero
        Nodo* act = fant->sig;

        while (act != fant) {

            //Guardamos siguiente
            Nodo* sig = act->sig;

            //Si coincide
            if (act->elem == elem) {

                this->borra_elem(act);
            }

            //Avanzamos
            act = sig;
        }
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    list_plus<int> l;
    int e, elem;

    // Leer primer numero de la lista
    cin >> e;
    if (!cin) return false;

    // Leer lista hasta -1
    while (e != -1) {
        l.push_back(e);
        cin >> e;
    }

    // Leemos elemento a eliminar
    cin >> elem;

    // Imprimimos lista original
    int n = l.size();
    for (int i = 0; i < n; ++i) {
        int x = l.front();
        cout << x << " ";
        l.pop_front();
        l.push_back(x);
    }
    cout << endl;

    // Eliminamos elementos
    l.eliminaElem(elem);

    // Ahora imprimimos la lista y de paso la dejamos vacía (tb para probar su consistencia)
    while (!l.empty()) {
        cout << l.front() << " ";
        l.pop_front();
    }
    cout << endl;

    return true;
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
    if (cin >> numCasos) { // Leemos el número de casos inicial 
        for (int i = 0; i < numCasos; ++i) {
            resuelveCaso();
        }
    }
    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}