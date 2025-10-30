#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "list_eda.h"
using namespace std;

vector<char> extraerLista(list<char>& lista, int pos, int lon) {
	vector<char> segmento(lon);
	list<char> aux;
	int elemPrincipio = 0;
	for (int i = 0; i < pos; i++) {
		aux.push_back(lista.front());
		elemPrincipio++;
		lista.pop_front();
	}

	for (int j = 0; j < lon; j++)
	{
		segmento[j] = lista.front();
		lista.pop_front();
	}

	for (int k = 0; k < elemPrincipio; k++)
	{
		lista.push_front(aux.back());
		aux.pop_back();
	}

	return segmento;
}

void insertarLista(list<char>& lista, int pos, vector<char>segmento) {

	list<char>::iterator it = lista.begin();
	for (int i = 0; i < pos; i++)
	{
		it++;
	}

	for (int i = 0; i < segmento.size(); i++)
	{

		lista.insert(it, segmento[i]);
	}

}

// función que resuelve el problema
void resolver(list<char>& lista, int n, int pos, int lon, int k) {

	//Se hace cuando: no esté vacía, origen correcto, destino correcto
	if (n != 0 && k != 0 && lon != 0 && pos < n && pos - k >= 0)
	{
		//Si además, se da el caso de que el segmento se sale de la lista
		if (pos + lon > n) {
			lon = n - pos;
		}

		//La nueva posición en la que se insertará el segmento será pos - k;
		int nuevaPos = pos - k;
		//Insertamos el segmento extraído en la nueva posición
		insertarLista(lista, nuevaPos, extraerLista(lista, pos, lon));

	}
	//else no hace nada

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

	resolver(l, n, pos, length, k);

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