// Carmen Gómez Becerra
// EDA - GDV29


#include <iostream>
#include <iomanip>
#include <fstream>


// función que resuelve el problema
int resolver(int datos) {
    return datos * 2;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    std::cin >> n;

    if (n == -1)
        return false;

    int secuencia; // secuencia de numeros
    for (int i = 0; i < n; ++i) {
        std::cin >> secuencia;
        int sol = resolver(secuencia);
        std::cout << sol << " ";
    }

    // escribir sol

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso()) {
        std::cout << std::endl;
    }
        


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
