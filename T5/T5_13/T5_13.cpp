// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"
using namespace std;

template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:
    /*
		Complejidad temporal:
        Dado que los bucles for tienen distintas complejidades (O(pos), O(length), O(pos - newPos - 1)),
        vamos a tomar el peor caso y es que todas ellas, como maximo pueden ser nDatos,
        es decir, el numero total de datos de la lista, por tanto, la complejidad sera O(nDatos)

		Complejidad espacial:
		Y dado que solo se crean algunos nodos auxiliares, pero no listas nuevas,
		ni nodos funcionales nuevos, el espacio se mantiene constante con una complejidad O(1)

    */

    //Entenderemos pos como la posicion inicial del segmento,
    //length como la longitud del segmento
    //y newPos como el numero de posiciones a desplazar (osea, la k)
    void adelantar(int pos, int length, int newPos) {
        //dado que vamos a usar mucho el tamanio, lo guardamos en una varianle auxiliar
        int nDatos = this->size(); //Complejidad O(1)

        //Si la posicion de origen || posicion destino del segmento no es valida || la lista esta vacia -> Complejidad O(1)|| si lon = 0 || k = 0,
        //la operacion no tendra efecto
        if (pos >= nDatos || pos - newPos < 0 || this->empty() || length <= 0 || newPos <= 0) return;

        //Veremos cuantos datos coger
        //Si la longitud de la cadena pedida desde la posicion inicial supera la longitud total de la lista
        if (pos + length >= nDatos)
        {
	        //ajustaremos la longitud pedida
            length = nDatos - pos;
        }

        //Y volvemos a comprobar la longitud, por si acaso
        if (length <= 0) return;

        //Vamos a buscar el nodo de la posicion buscada,
        //desde donde vamos a mover el segmento pedido
        Nodo* inicio_segmento = this->fantasma->sig;
        //Lo avanzamos hasta la posicion pos
        //Complejidad O(pos)
        for (int i = 0; i < pos; i++)
        {
            inicio_segmento = inicio_segmento->sig;
        }
        //De esta manera dejamos el principio de lista "almacenado",
        //para trabajar luego a la hora de recolocarlo

        //Ahora guardamos el ultimo nodo de esa parte de la lista
        Nodo* antes_segmento = inicio_segmento->ant;

        //Y el nodo del final del segmento
        Nodo* fin_segmento = inicio_segmento;
        //Lo avanzamos desde el inicio hasta el final del segmento,
        //es decir, length posiciones;
        //Complejidad O(length - 1 )
        for (int i = 0; i < length - 1; i++) 
        {
            fin_segmento = fin_segmento->sig;
        }

        //Guardamos el nodo de despuesta del segmento,
        //para tener el segmento acotado en todas partes
        Nodo* despues_segmento = fin_segmento->sig;

        //Ahora si, desplazamos el segmento comprendido entre
        //inicio_segmento y fin_segmento
        //Conectamos el final de la cadena del principio
        //con el principio de la cadena del final
        antes_segmento->sig = despues_segmento;
        despues_segmento->ant = antes_segmento;

        //De esta manera, aislamos el segmento. Queda desconectado de lo demas
        //Buscaremos su nueva posicion
        Nodo* nuevo_antes_segmento;
        //Si se pone en la posicion inicial, sera la fantasma (primera posicion)
        if (pos - newPos == 0)
        {
            nuevo_antes_segmento = this->fantasma;
        }
        //Sino, buscara a partir de esa primera posicion
        else
        {
            nuevo_antes_segmento = this->fantasma->sig;
            //Lo avanzamos desde el inicio hasta el anterior de la posicion nueva (pos - nuevaPos - 1)
			//Complejidad O(pos - newPos - 1)
            for (int i = 0; i < pos - newPos - 1; i++)
            {
                nuevo_antes_segmento = nuevo_antes_segmento->sig;
            }
        }


        //Guardamos la nueva posicion de despues del segmento
        Nodo* nuevo_despues_segmento = nuevo_antes_segmento->sig;

        //Ahora colocamos el segmento a partir de nuevo_antes_segmento
        //Conectamos el anterior de la cadena al principio del segmento
        nuevo_antes_segmento->sig = inicio_segmento;
        inicio_segmento->ant = nuevo_antes_segmento;

        //y el final del segmento con el de nuevo_despues_segmento
        fin_segmento->sig = nuevo_despues_segmento;
        nuevo_despues_segmento->ant = fin_segmento;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    //elementos de la lista
    char e;
    //tamanio lista, posicion desde la que movemos, longitud de segmento a mover, numero de posiciones para adelantar
    int n, pos, length, dif;
    //lista de elementos
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
