// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
int resolver(vector<int> v, int ini, int fin) {

    int dif = fin - ini;

    if (dif == 0) {
        return 0;
    }
    if (dif == 1) {
        return v[ini];
    }

    int mitad = (ini + fin) / 2;

    //Búsqueda en la primera mitad
    int min1 = resolver(v, ini, mitad);
    //Búsqueda en la segunda mitad
    int min2 = resolver(v, mitad, fin);

    if (min1 <= min2) {
        return min1;
    }
    else {
        return min2;
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int n;
    cin >> n;

    if (!std::cin)
        return false;

    vector<int> v(n);
    for (int& e : v) cin >> e;

    // Llamada a la función resolver
    // Mostrar el resultado
    cout << resolver(v, 0, n) << endl;

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