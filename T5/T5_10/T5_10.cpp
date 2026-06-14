
#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"
#include <vector>
using namespace std;

template <class T>
class queue_plus : public queue<T> {
    using Nodo = typename queue<T>::Nodo;

public:
    void replicaElems(vector<int> const& mult) {
        //El primero
        Nodo* act = this->prim;
        //El anterior, de momento nulo. Rellenaremos segun avancemos
        Nodo* ant = nullptr;

        int i = 0;

        //Hasta fin
        while (act != nullptr) {
            int m = mult[i];

            if (m == 0) {
                // eliminar nodo actual
                Nodo* borrar = act;

                //Conectamos los nodos
                //Si es el primero, ahora el nuevo primero es el siguiente al antiguo primero (osea, el segundo)
                if (ant == nullptr) {
                    this->prim = act->sig;
                }
                //Y si no, nos saltamos el actual
                else {
                    ant->sig = act->sig;
                }

                //Si es el ultimo, el anterior pasa a ser el verdadero ultimo porque nos quitamos el actual
                if (act == this->ult) {
                    this->ult = ant;
                }

                //Avanzamos, borramos y quitamos elementos
                act = act->sig;
                delete borrar;
                this->nelems--;
            }
            //Si m == 1 no hacemos nada
            //Insertamos copias si m > 1 
            else {
                //El ultimo para repetirlo
                Nodo* last = act;

                //Todas las copias que pide
                for (int k = 1; k < m; ++k) {
                    //Solo creamos los nodos necesarios
                    Nodo* nuevo = new Nodo(act->elem, last->sig);
                    //Avanzamos por si hay que crear mas nodos y por las conexiones
                    last->sig = nuevo;
                    last = nuevo;

                    //Si llegamos al final, lo avanzamos
                    if (last->sig == nullptr) {
                        this->ult = last;
                    }

                    //Y aniadimos mas elementos
                    this->nelems++;
                }

                //Conectamos para avanzar
                ant = last;
                act = last->sig;
            }

            i++;
        }
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n;
    queue_plus<int> q;

    cin >> n;
    vector<int> mult(n);
    vector<int> aux(n); // Para darle la vuelta a la secuencia de entrada

    // Leemos la secuencia invertida para q y le damos la vuelta
    for (int i = n - 1; i >= 0; --i) cin >> aux[i];
    for (int e : aux) q.push(e);

    // Leemos la secuencia invertida para mult
    for (int i = n - 1; i >= 0; --i) cin >> mult[i];

    // llamada al metodo
    q.replicaElems(mult);

    // escribir sol (pero antes dar una vuelta para comprobar que la cola está bien formada)
    for (int i = 0; i < q.size(); ++i) {
        n = q.front();
        q.pop();
        q.push(n);
    }

    // Ahora imprimimos la cola y de paso la dejamos vacía (tb para probar su consistencia)
    cout << "[";
    if (!q.empty()) {
        cout << q.front();
        q.pop();
    }
    while (!q.empty()) {
        cout << ", " << q.front();
        q.pop();
    }
    cout << "]" << endl;
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
