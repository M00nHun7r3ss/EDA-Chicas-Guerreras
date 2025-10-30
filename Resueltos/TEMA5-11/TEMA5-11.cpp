// Carmen Gómez Becerra
// EDA-GDV29 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "list_eda.h"
using namespace std;


template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:
	// Complejidad O(n), n = this->size(), es decir el numero de elementos de la lista.
    void adelantar(int pos, int lon, int k) { // en las listas enlazadas hacer todo PASO POR PASO.

        // si no es vacio, entra en los margenes, lon y k son >0 y pos >=k (ultimo caso)....
        if (!this->empty() && pos >= 0 && pos < this->size() && lon > 0 && k > 0 && pos >= k) // empty() y size() O(1) cada uno...
        {
            // si pos + lon > n se tomara el segmento de los ultimos n − pos elemento
            if (pos + lon > this->size()) { lon = this->size() - pos; } // O(1)

            // movemos el iterador hasta pos.
            auto it = this->begin(); // O(1)
            for (int i = 0; i < pos; ++i) { // O(n) 
                ++it; // O(1)
            }

            // metemos el contenido a desplazar en un auxiliar.
            list_plus aux;
            for (int i = 0; i < lon; ++i) { // O(n)
                aux.push_back(*it); // O(1)
                ++it; // O(1)
            }

            // retrocedemos al principio y volvemos hasta pos.
            it = this->begin(); // O(1)
            for (int i = 0; i < pos; ++i) {
                ++it; // O(1)
            }

            // DESCONECTAMOS el contenido de [pos, pos+lon).
            for (int i = 0; i < lon; ++i) { // O(n)
                // erase devuelve el iterador al siguiente (reconeta con los de despues).
                it = this->erase(it); // O(1)
            }

            // volvemos al inicio y avanzamos hasta donde estaria k. 
            it = this->begin(); // O(1)
            for (int i = 0; i < pos - k; i++) { // O(n)
                ++it; // O(1)
            }

            // CONECTAMOS el contenido de desp.
            for (auto elem : aux) { // O(n)
                it = this->insert(it, elem);
                ++it; // O(1)
            }
        }

        // Conclusion: como solo se suman muchos O(1) con otros tantos O(n), y entre sí, el resultado sera O(n)
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    char e;
    int n, pos, lon, k;
    list_plus<char> l;

    // leer los datos de la entrada
    cin >> n >> pos >> lon >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> e;
        l.push_back(e);
    }

    l.adelantar(pos, lon, k);

    // Le damos una vuelta para comprobar que la lista está bien formada
    for (int i = 0; i < l.size(); ++i) {
        e = l.back();
        l.pop_back();
        l.push_front(e);
    }

    // Ahora imprimimos la lista y de paso la dejamos vacía (tb para probar su consistencia)
    while (!l.empty()) {
        cout << l.front() << " ";
        l.pop_front();
    }
    cout << endl;
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input1.txt");
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
