#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
int resolver(vector<int> const& v, int i, int j) {

    // caso base, un solo elemento
    if (i == j) {
        return v[i];
    }

    // Mitad
    int mid = (i + j) / 2;

    // buscamos en ambas mitades
    int izq = resolver(v, i, mid);
    int der = resolver(v, mid + 1, j);

    // Solo un impar (siempre uno). Los demas son pares, asi que, o esta en la izquierda o en la derecha
    if (izq % 2 != 0) return izq;
    return der;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    //Leer numero de elementos
    int n;
    cin >> n;

    //Centinela
    if (n == 0)
        return false;

    //Leer y rellenar vector
    vector<int> v(n);

    for (int i = 0; i < n; i++)
        cin >> v[i];

    cout << resolver(v, 0, n - 1) << "\n";

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
