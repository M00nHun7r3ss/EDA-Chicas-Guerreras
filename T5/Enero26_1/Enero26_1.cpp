/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no:
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"

using namespace std;

/*
Complejidad:
Temporal O(n) solo se recorre una vez la lista inicial
Espacial O(1) no se crean nodos nuevos

*/


template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:
    // Complejidad: 
    list_plus<T> remConsecutiveEq() {

        list_plus<T> sol;

        //Primero
        Nodo* act = this->fantasma->sig;

        //Hasta que no se acaben
        while (act != this->fantasma && act->sig != this->fantasma)
        {

            //Si el siguiente es repe
            if (act->elem == act->sig->elem) {

                //Será el eliminado
                Nodo* eliminado = act->sig;

                // Conectamos la lista inicial
                act->sig = eliminado->sig;
                eliminado->sig->ant = act;

                /*
                * act = eliminado->sig->ant ... eliminado ... elimiado->sig = act->sig
                *   |---------------------|
                *    elimiado->sig NUEVO ACT->sig
                *            y 
                *   Act NUEVO eliminado->sig->ant 
                */

                // insertar en res (al final)
                eliminado->sig = sol.fantasma;
                eliminado->ant = sol.fantasma->ant;
                sol.fantasma->ant->sig = eliminado;
                sol.fantasma->ant = eliminado;

                //Aniadimos nodo en sol, quitamos nodo de inicial
                sol.nelems++;
                this->nelems--;

            }
            //Si no conciden, avanzamos al siguiente nodo
            else {
                act = act->sig;
            }
        }

        return sol;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n;
    char e;
    list_plus<char> l, res;

    // leer los datos de la entrada
    cin >> n;
    if (n == -1) return false;
    for (int i = 1; i <= n; ++i) {
        cin >> e;
        l.push_back(e);
    }

    res = l.remConsecutiveEq();

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

    // Ahora imprimimos la lista res y de paso la dejamos vacía (tb para probar su consistencia)
    while (!res.empty()) {
        cout << res.front() << " ";
        res.pop_front();
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

    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}