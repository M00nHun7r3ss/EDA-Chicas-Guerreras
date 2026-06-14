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
#include "queue_eda.h"

template <class T>
class queue_plus : public queue<T> {
    using Nodo = typename queue<T>::Nodo;

public:
    // Complejidad:
    void reordena() {

        //Primer nodo
        Nodo* act = this->prim;

        // lista negativos (inicialmente invertida)
        Nodo* neg_ini = nullptr; 
        // lista positivos
        Nodo* pos_ini = nullptr;  
        // para saber donde acaban los positivos
        Nodo* pos_fin = nullptr;

        while (act != nullptr) {

            //Cogemos el siguiente
            Nodo* sig = act->sig;

            //Buscamos negativo
            if (act->elem < 0) {
                // insertamos al principio e invertimos orden
                act->sig = neg_ini;
                neg_ini = act;
            }
            //ESO DEJA EL NEGATIVO A LA IZQUIERDA DEL ACTUAL
            //Ahora buscamos positivo
            else {
                // Si no habia positivos, pues sera el primero y el ultimo
                if (pos_ini == nullptr) {
                    pos_ini = pos_fin = act;
                    act->sig = nullptr;
                }
                //Si ya habia, pues el siguiente al ultimo aniadido
                else {
                    pos_fin->sig = act;
                    pos_fin = act;
                    act->sig = nullptr;
                }
            }

            //Pasamos al siguiente
            act = sig;
        }

        //Reconstruimos la cola
        //NO HAY NEGATIVOS
        if (neg_ini == nullptr) {
            //Solo positivos
            this->prim = pos_ini;
            this->ult = pos_fin;
        }
        //SI HAY NEGATIVOS
        else {
            //eL final de los negativos
            Nodo* neg_fin = neg_ini;
            while (neg_fin->sig != nullptr)
                neg_fin = neg_fin->sig;

            //se une con el principio de los positivos
            neg_fin->sig = pos_ini;

            //El primero es ahora el primer negativo
            this->prim = neg_ini;
            //Si no hubiese positivos, pues solo los negativos
            this->ult = (pos_fin != nullptr ? pos_fin : neg_fin);
        }
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, e;
    queue_plus<int> q;
    std::cin >> n;
    if (n == 0) return false;
    for (int i = 0; i < n; ++i) {
        std::cin >> e;
        q.push(e);
    }

    q.reordena();

    // escribir sol (pero antes dar una vuelta para comprobar que la cola está bien formada)
    for (int i = 0; i < q.size(); ++i) {
        n = q.front();
        q.pop();
        q.push(n);
    }

    // Ahora imprimimos la cola y de paso la dejamos vacía
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
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