// Carmen Gómez Becerra
// EDA-GDV29
// Complejidad lineal O(n): el tiempo de ejecucion es proporcional al numero de entradas, se recorre una vez el bucle.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int n; // numero de elementos de la secuencia

    // leer los datos de la entrada
    std::cin >> n;

    // recorremos valor a valor para ver si es impar o no.
    int val;
    for (int i = 0; i < n; ++i) {
        std::cin >> val;
        if (val % 2 == 0) { // si es par
            std::cout << val << " ";
        }
    }
    std::cout << std::endl;
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
    system("PAUSE");
#endif

    return 0;
}
