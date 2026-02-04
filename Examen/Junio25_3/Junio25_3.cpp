
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

// Complejidad:
//Dado que tento .begin(). como .end() y .erase() son O(1), la complejidad espacial es O(1),
//y en cuanto a la temporal, será O(k), porque se hace el bucle k veces
//El map ya esta ordenado, solo hay que borrar los k menores.
template <class K, class V>
void eliminaKMenores(map<K, V>& map, int k) {

    //Vamos desde el inicio
    auto it = map.begin();
    //Hasta el final
    while (k > 0 && it != map.end()) {
        //Borramos en orden y nos devuelve el siguiente
        it = map.erase(it);
        //Reducimos k y seguimos borrando
        --k;
    }
}

// Complejidad:
//Dado que copiar las claves de map en el vector tiene complejidad O(n) y .sort() tiene complejidad O(n log n), nos quedamos con complejidad temporal O(n log n)
//y en cuanto a la espacial, erase tiene una complejidad O(k), porque se hace el bucle k veces, pero como ya hemos recorrido anteriormente el map para pasarselo al vector
//la complejidad espacial sera O(n)
//El map no esta ordenado, asi que hay que ordenarlo para borrar
template <class C, class V>
void eliminaKMenores(unordered_map<C, V>& map, int k) {
    //Si pide mas de las que hay, borra todas
    if (k >= map.size()) {
        map.clear();
        return;
    }

    //Usaremos un vector para guardar el map y ordenarlo
    vector<C> claves;
    claves.reserve(map.size());

    //Recorremos el map y rellenamos el vector con las claves
    for (pair<const C, V> const& par : map) 
    {
        claves.push_back(par.first);
    }

    //Ordenamos
    sort(claves.begin(), claves.end());

    //Una vez ordenado, borra en orden las claves del vector. Erase() las busca y las borra en el map
    for (int i = 0; i < k; ++i)
    {
        map.erase(claves[i]);
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
    for (pair<const string, int> const& par : map1)
        cout << par.first << " " << par.second << "\n";
    cout << "-\n";

    // Imprimir map2 ordenado por claves (para ello debes volcarlo a un vector, ordenarlo e imprimirlo)
    //Ordenamos el vector
    vector<pair<string, int>> v(map2.begin(), map2.end());
    sort(v.begin(), v.end());

    for (pair<const string, int> const& par : v)
        cout << par.first << " " << par.second << "\n";
    cout << "---\n";
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