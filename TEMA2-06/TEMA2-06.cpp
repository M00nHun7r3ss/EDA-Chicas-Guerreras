// Carmen Gómez Becerra
// EDA - GDV29
// Complejidad ...

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

bool elemento_situado(const std::vector < int >& v, int ini, int fin) {
    int i = 0;
    bool situado = false; // inicialmente asumimos que no habra un bien situado.
    while (i < v.size()) {

    }
}

// función que resuelve el problema
bool resolver(const std::vector<int>& v, int ini, int fin) {
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    std::cin >> n;
    std::vector<int> sec(n);
    for (int& e : sec) std::cin >> e;
    std::cout << (resolver(sec, 0, n) ? "SI" : "NO") << std::endl;
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
