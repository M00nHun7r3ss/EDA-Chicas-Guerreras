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


// función que resuelve el problema y justificación del coste
//Complejidad:
//Espacial: 0(1), no se crean estructuras nuevas, solo punteros temporales
//Temporal: 0(n), la lista se recorre entera (n = todos los nodos) una vez
template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:
    void partition(int pivote) {

        //El fantasma
        Nodo* fant = this->fantasma;
        //El primero
        Nodo* act = fant->sig;

        // Buscamos el primer nodo > pivote
        while (act != fant && act->elem <= pivote) {
            act = act->sig;
        }

        // Este sera el primer mayor al pivote
        Nodo* primeroMayor = act;

        // Recorremos el resto.
        // Los de antes del primer mayor estan ya en su sitio
        while (act != fant) {
            //Guardamos puntero al siguiente
            Nodo* sig = act->sig;

            //Si son menores que el pivote
            if (act->elem <= pivote) {
                // lo sacamos de su sitio
                // El nuevo siguiente del anterior pasa a ser el siguiente del actual
                act->ant->sig = act->sig;
                //El nuevo anterior del siguiente pasa a ser el anterior del actual
                act->sig->ant = act->ant;

                //Hasta aqui hemos aislado el actual conectando su anterior y el siguiente en doble direccion
                // anterior actual siguiente
                //      <------------->

                // lo insertamos antes de primeroMayor
                //El nuevo siguiente del actual pasa a ser el primer mayor al pivote (para que vaya antes)
                act->sig = primeroMayor;
                //Y el nue o anterior del actual sera el antiguo anterior del primer mayor
                act->ant = primeroMayor->ant;
                //El nuevo siguiente del anterior al primer mayor ahora sera el actual
                primeroMayor->ant->sig = act;
                //Y el nuevo anterior del mayor sera el actual
                primeroMayor->ant = act;

                //Hasta aqui hemos colocado el actual 
                // anterior actual primerMayor
                //      <---->   <---->

            }

            //Avanzamos
            act = sig;
        }
    }
    
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int e, n, pivote;
    list_plus<int> l;

    // leer los datos de la entrada
    cin >> n >> pivote;
    if (!cin) return false;

    for (int i = 1; i <= n; ++i) {
        cin >> e;
        l.push_back(e);
    }

    l.partition(pivote);

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