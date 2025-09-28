// Carmen Gómez Becerra
// EDA-GDV29


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada.
    int n; 
    std::cin >> n;

    // PICOS Y VALLES:
    // ej.: (a, b, c, d)
    // · el primero no puedes combrobar el anterior.
    // · el ultimo no puedes comprobar el posterior.
    // · valle -> a > b && b < c
    // · pico -> a < b && c < b

    // almacenamos en un vector la secuencia.
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }

    // picos y valles inicialmente a 0.
    int nValley = 0;
    int nPeak = 0;

    // tiene que recorrer toda la secuencia para ver sus picos y valles.
    for (int i = 1; i < n - 1; i++) { // empezamos en el segundo y acabamos en el penultimo.
        if (v[i - 1] > v[i] && v[i] < v[i + 1]) nValley++;
        if (v[i - 1] < v[i] && v[i + 1] < v[i]) nPeak++;
    }

    // escribir sol
    std::cout << nPeak << " " << nValley << std::endl;
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
