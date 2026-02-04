#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"

template <class T>
class queue_plus : public queue<T> {
    using Nodo = typename queue<T>::Nodo;

public:
    // Complejidad:
    //Los positivos ya estan ordenados, solo hay que invertir y recolocar los negativos a la izquierda
    void reordena() {
        //Guardaremos nodos negativos y positivos separados
        Nodo* negPrim = nullptr;
        Nodo* negUlt = nullptr;
        Nodo* posPrim = nullptr;
        Nodo* posUlt = nullptr;

        //Tomamos el actual
        Nodo* act = this->prim;

        //Y vamos a recorrer una unica vez 
        while (act != nullptr) {
            //Guardamos el siguiente para avanzar luego
            Nodo* sig = act->sig;
            //Y vaciamos el siguiente del actual
            act->sig = nullptr;

            //Si son negativos
            if (act->elem < 0) {
                // insertar al principio de la lista de negativos 
                if (negPrim == nullptr) {
                    //El actual sera primero y ultimo de los negativos
                    negPrim = negUlt = act;

                    //De forma que:
                	//act = negPrim = negUlt
                    //Aqui solo hay un negativo
                }
                //Si ya hay algun negativo ya, lo colocaremos a su izquierda, porque sera menor.
                //al colocarlo a la izquierda, invertimos el orden
                else {
                    //el siguiente sera el primer negativo
                    act->sig = negPrim;
                    //el actual pasa a ser el primer negativo
                    negPrim = act;

                    //De forma que:
                    //act = negPrim < negUlt
                    //          <---->
                }
            }
            //Si son positivos
            else {
                // insertar al final de la lista de positivos, porque como ya hemos dicho,
                // Los positivos ya estan ordenados
                //Si no habia positivos antes, ahora si
                if (posPrim == nullptr) {
                    //El actual sera primero y ultimo de los positivos
                    posPrim = posUlt = act;

                    //De forma que:
                    //act = posPrim = posUlt
                    //Aqui solo hay un positivo
                }
                //Si ya hay algun positivo ya, lo colocaremos a su derecha, porque sera mayor.
                else {
                    //el siguiente sera el ultimo positivo
                    posUlt->sig = act;
                    //el actual pasa a ser el ultimo positivo
                    posUlt = act;

                    //De forma que:
                    //posPrim > posUlt = act
                    //     <---->
                }
            }

            //Avanzamos
            act = sig;
        }

        //Una vez que hemos llegado aqui, tenemos todos los nodos negativos por una parte (ya ordenados) y los positivos por otra
        // los unimos
        //Si hay negativos
        if (negPrim != nullptr) {
            //Iran a la izquierda del todo
            this->prim = negPrim;
            //Despues del ultimo negativo va el primer positivo
            negUlt->sig = posPrim;
            //Si hemos llegado al final...
            //Si hay positivos, el ultimo positivo sera el ultimo
            //Si solo hay negativos, el ultimo negativo sera el ultimo de la cadena
            this->ult = (posUlt != nullptr ? posUlt : negUlt);
        }
        //Si no hay negativos
        else {
            //Simplemente colocamos la cadena de positivos
            //El primera sera el primer positivo
            this->prim = posPrim;
            //El ultimo sera el ultimo positivo
            this->ult = posUlt;
        }

        //Despues del final de la cola no habra nada - nullptr
        if (this->ult != nullptr)
            this->ult->sig = nullptr;
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
    std::ifstream in("input1.txt");
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