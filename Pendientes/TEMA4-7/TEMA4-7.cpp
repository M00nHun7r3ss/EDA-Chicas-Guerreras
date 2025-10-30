// Carmen Gómez Becerra
// EDA-GDV29


#include <iostream>
#include <iomanip>
#include <fstream>

#include "Set.h"

void leeSet(Set<int>& s, int n){
    int num;
    for (int i = 0; i < n; i++) {
        std::cin >> num;
        s.add(num);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    Set<int> set1;
    Set<int> set2;

    std::cin >> n;
    leeSet(set1, n);
    std::cin >> n;
    leeSet(set2, n);

    if (!std::cin)
        return false;

    // escribir sol
    std::cout << (set1 <= set2) << std::endl;


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
