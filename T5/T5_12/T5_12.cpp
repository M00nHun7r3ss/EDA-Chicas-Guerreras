// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"
using namespace std;


template <class T>
class queue_plus : public queue<T> {
    using Nodo = typename queue<T>::Nodo;

public:
    /*
		Complejidad temporal:
		La cola se recorre una unica vez para buscar ambos elementos A y B,
		asi que en el peor de los casos, se recorreran todos los elementos de cola
		Por tanto la complejidad sera O(n), donde n es el tamanio de la cola

		Complejidad espacial:
		Y dado que solo se crean algunos nodos auxiliares, pero no listas nuevas,
		ni nodos funcionales nuevos, el espacio se mantiene constante con una complejidad O(1)

   */
    void cuela(const T& a, const T& b) {
        // Ojo que para acceder a prim o ult hay que escribir this->prim o this->ult
        //Si la cola esta vacia -> Complejidad O(1) o si solo hay un elemento -> Complejidad O(1) (se necesitan minimo 2)
        //la operacion no tendra efecto
        if (this->empty() || this->size() == 1) return;

        // Punteros
        Nodo* actual = this->prim; //Con este recorremos
        Nodo* posA = nullptr; //Primera aparicion de A
        Nodo* posB = nullptr; //Primera aparicion de B
        Nodo* antB = nullptr; //Nodo anterior a B, para poder desplazarlo

        //Buscamos la primera aparicion de A
        while (actual != nullptr && posA == nullptr)
        {
            //Si no se ha encontrado ya una A, es esa
            if (actual->elem == a) {
                posA = actual;
            }
            //Y pasamos al siguiente
            actual = actual->sig;
        }

        //Si no existe la A en la cola proporcionada o esta en la ultima posicion,
        //no seguimos, porque o bien no esta, o no puede haber una B despues de la A
        if (posA == nullptr || posA == this->ult) return;

        // Una vez que ya hemos encontrado la A, buscamos la primera B
        antB = posA;
        actual = posA->sig;
        while (actual != nullptr && posB == nullptr)
        {
            //Si no se ha encontrado ya una B, es esa
            if (actual->elem == b) {
                posB = actual;
            }
            //Si no, seguimos avanzando el anterior a B
            else {
                antB = actual;
            }
            //Y pasamos al siguiente
            actual = actual->sig;
        }

        //Si no existe la B en la cola proporcionada, o ya esta colocada , no seguimos
        if (posB == nullptr || posA->sig == posB) return;

        //Separamos b del resto de la cola
        //Conectamos el anterior a B con el siguiente de B
        antB->sig = posB->sig;
        //Y si B era el ultimo, el anterior pasa a ser el ultimo,
        //porque pretendemos mover B hacia la izquierda
        if (posB == this->ult) this->ult = antB;

        //Y ahora, unimos con A
        //El nuevo siguiente de B sera el anterior siguiente de A
        posB->sig = posA->sig;
        //El nuevo siguiente de A es B
        posA->sig = posB;
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
