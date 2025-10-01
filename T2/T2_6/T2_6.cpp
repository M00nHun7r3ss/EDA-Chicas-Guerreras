// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
bool elemento_situado(const vector<int>& v, int ini, int fin) {

    int diferencia = fin - ini;

    //si no quedan datos para analizar
    if (diferencia == 0) return false;

    //si solo queda un dato
    if (diferencia == 1)
    {
        //y ese dato corresponde con su posicion
        if (v[ini] == ini) return true;

        //si no corresponden
        else return false;
        
    }

    //Calculamos la mitad para buscar en cada una de ellas
    int mitad = (ini + fin) / 2;

    //Buscamos en la primera mitad
    if (v[mitad] > mitad)
    {
        return elemento_situado(v, ini, mitad);
    }

    //Buscamos en la segunda mitad
    if (v[mitad] < mitad)
    {
        return elemento_situado(v, mitad, fin);
    }

    //Daremos por hecho que si ha llegado hasta aqui, estan colocados
    return true;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    // numero de datos
    int n;
    cin >> n;

    //vector secuencia numeros
    vector<int> sec(n);
    //rellenamos secuencia de numeros
    for (int& e : sec) cin >> e;

    //resolvemos con una busqueda binaria de inicio a fin
    cout << (elemento_situado(sec, 0, n) ? "SI" : "NO") << endl;
}

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
