// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// función que resuelve el problema
bool resolver(vector<int> const& v, int i, int j, int k) {

    // caso base, un solo elemento
    if (i == j) {
        return true;
    }

    //mitad
    int mid = (i + j) / 2;

    //rec izquierda y derecha
    bool izq = resolver(v, i, mid, k);
    bool der = resolver(v, mid + 1, j, k);

    // lados correctos y diferencia entre el primer valor y el último, mayor o igual que k
    return izq && der && abs(v[i] - v[j]) >= k;

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, k;

    //Casos indeterminados
    if (!(cin >> n >> k))
        return false;

    //Leemos y rellenamos vector
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    //Resolver
    bool sol = resolver(v, 0, v.size() - 1, k);

    //Escribir solucion
    if (sol)
        cout << "SI\n";
    else
        cout << "NO\n";

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