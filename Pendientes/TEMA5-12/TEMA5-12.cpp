// Carmen Gómez Becerra
// EDA-GDV29

#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"
using namespace std;

template <class T>
class queue_plus : public queue<T> {
    using Nodo = typename queue<T>::Nodo;

public:
    void cuela(const T& a, const T& b) {
        queue<T> aux; // cola auxiliar para los recorridos.

        // booleano que determina si el primer elemento ha aparecido ya,
        // para que b solo se haga si ha aparecido despues de a.
        bool firstAppeared = false;
        // va moviendo y ordenando de this a aux, dejando this vacio.
        while (!this->empty()) {
            if (this->front() == a && !firstAppeared) {
                // metemos "a" a la cola.
                aux.push(a);
                this->pop();
                firstAppeared = true;

                // metemos "b" delante de "a"
                aux.push(b);
            }
            else if (this->front() == b && firstAppeared){
                this->pop();
            }
            else{
                aux.push(this->front());
                this->pop();
            }
        }

        // se mueve el contenido de aux ordenado al this vacio.
        while (!aux.empty()){
            this->push(aux.front());
            aux.pop();
        }
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, a, b;
    queue_plus<int> q;
    cin >> n;
    if (n == -1) return false;
    while (n != -1) {
        q.push(n);
        cin >> n;
    }
    cin >> a >> b;

    // llamada a metodo
    q.cuela(a, b);

    // escribir sol (pero antes dar una vuelta para comprobar que la cola está bien formada)
    for (int i = 0; i < q.size(); ++i) {
        n = q.front();
        q.pop();
        q.push(n);
    }
    // Ahora imprimimos la cola y de paso la dejamos vacía
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
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
