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

    //Si solo hay un elemento, devuelve ese
    if (dif == 1) {
        return v[ini];
    }

    //Buscamos la mitad
    int mitad = (ini + fin) / 2;

    //Si ha llegado aqui
    //Segunda mitad (si la mitad y su siguiente siguen ordenados)
    if (v[mitad] + 1 == v[mitad + 1])
    {
        return resolver(v, mitad, fin);
    }
    //Primera mitad (si a partir de la mitad no estan ordenados)
    else
    {
        return resolver(v, ini, mitad);
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;

    vector<int> sec(n);
    for (int& e : sec) cin >> e;

    // Llamada a la función resolver y solucion
    cout << resolver(sec, 0, n) << endl;
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

}