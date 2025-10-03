// Carmen Gómez Becerra
// EDA - GDV29
// Complejidad lineal. O(log n), la busqueda binaria va reduciendo el problema a la mitad en cada iteracion (divide y venceras), mas eficiente que busqueda lineal. 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

bool elemento_situado(const std::vector < int >& v, int ini, int fin) {

    if (ini < fin && !v.empty()){ // mientras ini sea menor que fin, actua.
        // inicialmente asumimos que no habra un bien situado.
		// va buscando si esta situado quitandose cachos de vector (busqueda binaria)
        int m = (ini + fin) / 2; // punto medio (se ira actualizando conforme vaya buscando)
        if (v[m] == m) { // si v[m] == i
            return true; // hemos acabado.
        }
        else if (v[m] > m) { // el valor es mayor que la mitad (se pasa)
            return elemento_situado(v, ini, m); // mira mitad izquierda
        }
        else { // si el valor es menor que la mitad (no llega)
            return elemento_situado(v, m + 1, fin); // mira mitad derecha.
        }
    }
    return false; // si no lo ha encontrado, false.
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    std::cin >> n;
    std::vector<int> sec(n);
    for (int& e : sec) std::cin >> e;
    std::cout << (elemento_situado(sec, 0, n) ? "SI" : "NO") << std::endl;
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
