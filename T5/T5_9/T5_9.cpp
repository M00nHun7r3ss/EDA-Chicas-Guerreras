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
    void ordena() {

        //El primero
        auto it = this->begin();

        //Si ya estamos al final nada
        if (it == this->end()) return;

        //Cogemos el anterior
        auto prev = it;
        ++it;

        while (it != this->end()) {
            //Si el actual es menor que el anterior
            if (*it < *prev) {
                //Eliminamos
                it = this->erase(it);
            }
            else {
                // Avanzamos los dos
                prev = it;
                ++it;
            }
        }
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    list_plus<int> l;
    int e;

    // Leer primer numero de la lista
    cin >> e;
    if (!cin) return false;

    // Leer lista hasta -1
    while (e != -1) {
        l.push_back(e);
        cin >> e;
    }

    // Ordenamos
    l.ordena();

    // Le damos una vuelta para comprobar que la lista está bien formada
    for (int i = 0; i < l.size(); ++i) {
        e = l.back();
        l.pop_back();
        l.push_front(e);
    }

    // Ahora imprimimos la lista y de paso la dejamos vacía (tb para probar su consistencia)
    while (!l.empty()) {
        cout << l.front();
        l.pop_front();
        if (!l.empty()) {
            cout << " ";
        }
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