/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no:

Cuestión extra: ¿Cuál sería la menor complejidad en tiempo que podría tener una función que elimine los k pares clave-valor con menor valor para cada caso (map y unordered_map)? Justifica tu respuesta.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

// Complejidad:
template <class K, class V>
void eliminaKMenores(map<K, V>& map, int k) {

    // En map los elementos ya estan ordenados, asi que los k menores son los primeros
    auto it = map.begin();

    // Eliminamos los k primeros 
    while (it != map.end() && k > 0) {
        it = map.erase(it); 
        k--;
    }
}

// Complejidad: 
template <class C, class V>
void eliminaKMenores(unordered_map<C, V>& map, int k) {

    // Pasamos los elementos a un vector para poder ordenarlos
    vector<pair<C, V>> v(map.begin(), map.end());

    // Ordenamos
    sort(v.begin(), v.end());

    // Eliminamos los k menores 
    for (int i = 0; i < k && i < v.size(); i++) {
        map.erase(v[i].first);
    }
}

void resuelveCaso() {
    map<string, int> map1;
    unordered_map<string, int> map2;
    int n, k;

    // Lectura de datos
    cin >> n >> k;
    string clave;
    int valor;
    for (int i = 0; i < n; ++i) {
        cin >> clave >> valor;
        map1.insert({ clave, valor });
        map2.insert({ clave, valor });
    }

    // Llamada a funciones
    eliminaKMenores(map1, k);
    eliminaKMenores(map2, k);

    // Escritura de la salida

    // Imprimir map1 ordenado por claves
    for (auto const& par : map1) {
        cout << par.first << " " << par.second << "\n";
    }

    cout << "-\n";

    // Para map2 hay que ordenarlo manualmente

    // Pasamos a vector
    vector<pair<string, int>> v(map2.begin(), map2.end());

    // Ordenamos por clave 
    sort(v.begin(), v.end());

    // Imprimimos
    for (auto const& par : v) {
        cout << par.first << " " << par.second << "\n";
    }

    cout << "---\n";
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input3.txt");
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