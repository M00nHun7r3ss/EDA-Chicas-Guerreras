// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
bool resolver(vector<int> v, int ini, int fin, int valor) {

    int dif = fin - ini;

    if (dif == 1) {
        return v[ini] == valor;
    }
    int mitad = (ini + fin) / 2;

    // vector ordenado
    if (v[ini] <= v[mitad])
    {
        //Primera mitad
        if (valor >= v[ini] && valor < v[mitad])
            return resolver(v, ini, mitad, valor);
        //Si ha llegado aqui, Segunda mitad
        return resolver(v, mitad, fin, valor);
    }

    //Si ha llegado aqui, vector desordenado
    //Primera mitad
    if (valor >= v[mitad] && valor < v[ini])
        return resolver(v, mitad, fin, valor);
    //Si ha llegado aqui, Segunda mitad
    return resolver(v, ini, mitad, valor);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n = 0, valor = 0;
    std::cin >> n >> valor;

    if (n == -1)
        return false;

    vector<int> v(n);
    for (int& e : v) cin >> e;

    // Llamada a la función resolver
    // Mostrar el resultado - encontrado SI, no encontrado NO
    cout << (resolver(v, 0, n, valor) ? "SI" : "NO") << endl;

    return true;

}

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
    system("PAUSE");
#endif

    return 0;
}
