// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "list_eda.h"
using namespace std;



/*
	Complejidad temporal:
	Dado que los bucles for tienen distintas complejidades (O(pos), O(length), O(pos - k),
	vamos a tomar el peor caso y es que todas ellas, como maximo pueden ser nDatos,
	es decir, el numero total de datos de la lista, por tanto, la complejidad sera O(nDatos)

	Complejidad espacial:
	Y dado que solo se crean algunos iteradores auxiliares, pero no listas nuevas,
	el espacio se mantiene constante con una complejidad O(1), pero, dado que creamos un vector
	para almacenar el segmento de longitud length, la complejidad sera O(length).

*/
template <typename T>
void adelantar_segmento(list<T>& l, int pos, int length, int k) {
	//dado que vamos a usar mucho el tamanio, lo guardamos en una variable auxiliar
	int nDatos = l.size(); //Complejidad O(1)

	//Si la posicion de origen || posicion destino del segmento no es valida || la lista esta vacia -> Complejidad O(1)|| si lon = 0 || k = 0,
	   //la operacion no tendra efecto
	if (pos >= nDatos || l.empty() || length <= 0 || k <= 0) return;

    //Veremos cuantos datos coger
	//Si la longitud de la cadena pedida desde la posicion inicial supera la longitud total de la lista
    if (pos + length > nDatos)
    {
        //ajustaremos la longitud pedida
        length = nDatos - pos;
    }

    //Y volvemos a comprobar la longitud, por si acaso
    if (length <= 0) return;

    //Vamos a buscar el nodo de la posicion buscada,
    //desde donde vamos a mover el segmento pedido
    auto it_inicio_seg = l.begin();
    //Lo avanzamos hasta la posicion pos
    //Complejidad O(pos)
    for (int i = 0; i < pos; i++)
    {
		it_inicio_seg++;
    }
    //De esta manera dejamos el principio de lista "almacenado",
    //para trabajar luego a la hora de recolocarlo

	//Vamos a tener un iterador al final del segmento tambien,
	//para tener el segmento acotado
	auto it_fin_seg = it_inicio_seg;
	//Lo avanzamos hasta la posicion pos
	//Complejidad O(length)
	for (int i = 0; i < length; i++)
	{
		it_fin_seg++;
	}


    //Guardaremos el segmento en un vector auxiliar
	//Avanzaremos con un iterador auxiliar a lo largo del segmento
	//segun lo vayamos guardando, para guardar el elemento concreto
    //Complejidad O(length)
    vector<T> segmento;
    for (auto it_aux = it_inicio_seg; it_aux != it_fin_seg; it_aux++)
    {
        segmento.push_back(*it_aux);
    }

    //Ahora borramos los elementos de la lista 
    //it_fin_seg va avanzando a la par que borra
	it_fin_seg = l.erase(it_inicio_seg, it_fin_seg);

	//Calculamos donde toca la nueva posicion
	int nuevaPos = pos - k;
	if (nuevaPos < 0) nuevaPos = 0;

    //Ahora buscamos la posicion final desde donde empezara el segmento
    auto posFinal_segmento = l.begin();
    //Lo avanzamos desde el inicio hasta la posicion buscada
    //Complejidad O(pos - k)
    for (int i = 0; i < nuevaPos; i++)
    {
        posFinal_segmento++;
    }

	//Insertamos el segmento aqui (lo tenemos guardado en un vector)
	for (int i = 0; i < segmento.size(); i++)
	{
		l.insert(posFinal_segmento, segmento[i]);
	}
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso()
{
	//elementos de la lista
	char e;
	//tamanio lista, posicion desde la que movemos, longitud de segmento a mover, numero de posiciones para adelantar
	int n, pos, length, k;
	//lista de elementos
	list<char> l;

	// leer los datos de la entrada
	cin >> n >> pos >> length >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> e;
		l.push_back(e);
	}

	adelantar_segmento(l, pos, length, k);

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

int main()
{
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) resuelveCaso();

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}