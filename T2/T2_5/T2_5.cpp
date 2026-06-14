// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

struct Solution {
    bool ok;
    int pares;
};

// función que resuelve el problema
Solution resolver(vector<int> const& v, int i, int j) {

    // Caso base, un solo elemento, siempre caucásico
    // y tiene 1 par o 0 pares segun valor
    if (i == j) {
        return { true, (v[i] % 2 == 0 ? 1 : 0) };
    }

    // Mitad
    int mid = (i + j) / 2;

    // Resolvemos lados
    Solution izq = resolver(v, i, mid);
    Solution der = resolver(v, mid + 1, j);

    // Unimos lados
    int totalPares = izq.pares + der.pares;

    // Condicion valido: ambas mitades caucásicas y diferencia de pares <= 2
    bool ok = izq.ok && der.ok && abs(izq.pares - der.pares) <= 2;

    return { ok, totalPares };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;

    // Centinela
    if (n == 0)
        return false;

    //leer vector y rellenar
    vector<int> v(n);

    for (int i = 0; i < n; i++)
        cin >> v[i];

    //solucion busqueda binaria
    Solution sol = resolver(v, 0, n - 1);

    //escribir solucion
    if (sol.ok)
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
