// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
char resolver(const vector<char>& v, char ini, char fin, char prim, char ult) {

    int diferencia = fin - ini;

    //No hay elementos
    if (diferencia == 0) 
        return prim;
    //Si coincide esta justo despues, si no esta inmediatamente antes
    else if (diferencia == 1) 
        return v[ini] == prim ? v[ini] + 1 : v[ini] - 1;
    //Extremo izquierdo
    if (v[ini] != prim)
        return prim;
    //Extremo derecho
    if (v[fin - 1] != ult)
        return ult; 

    //Mitad
    int mitad = (ini + fin) / 2;
    //Lo que buscamos, la referencia para buscar donde esta
    char esperado = prim + (mitad - ini);

    if (esperado == v[mitad])
        // el fugado esta a la derecha
        return resolver(v, mitad, fin, v[mitad], ult);

    //Si no, esta a la izquierda
    return resolver(v, ini, mitad, prim, v[mitad - 1]); 
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    char prim, ult, n;
    cin >> prim >> ult;
    n = ult - prim;
    vector<char> v(n);
    for (char& e : v) cin >> e;
    cout << resolver(v, 0, n, prim, ult) << endl;
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