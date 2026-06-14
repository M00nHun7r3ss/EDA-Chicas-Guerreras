#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"
using namespace std;


template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:
    void adelantar(int pos, int length, int k) {

        //Si no hay lista, o no hay variables que modificar, no hay nada que hacer
        if (this->empty() || length == 0 || k == 0) return;

        //Tomamos el numero de elementos
        int n = this->nelems;

        //No podemos pasarnos de la posicion final
        if (pos >= n) return;

        //Cogemos menos longitud
        if (pos + length > n)
            length = n - pos;

        //No podemos ir menos del limite izquierdo
        if (pos - k < 0) return;

        //Tomamos el fantasma
        Nodo* fant = this->fantasma;

        //Tomamos el primero, y avanzamos hasta la posicion pedida
        Nodo* ini = fant->sig;
        for (int i = 0; i < pos; i++)
            ini = ini->sig;

        //A partir de ahi buscamos la longitud
        Nodo* fin = ini;
        for (int i = 1; i < length; i++)
            fin = fin->sig;

        //Guardamos los valores de antes y despues
        Nodo* antesIni = ini->ant;
        Nodo* despuesFin = fin->sig;

        //Desconectamos el segmento
        antesIni->sig = despuesFin;
        despuesFin->ant = antesIni;

        //Buscamos la posiciofn final
        Nodo* dest = fant->sig;
        for (int i = 0; i < pos - k; i++)
            dest = dest->sig;

        Nodo* antesDest = dest->ant;

        //Conetamos el segmento
        antesDest->sig = ini;
        ini->ant = antesDest;

        fin->sig = dest;
        dest->ant = fin;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    char e;
    int n, pos, length, dif;
    list_plus<char> l;

    // leer los datos de la entrada
    cin >> n >> pos >> length >> dif;
    for (int i = 1; i <= n; ++i) {
        cin >> e;
        l.push_back(e);
    }

    l.adelantar(pos, length, dif);

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
