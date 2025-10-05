// Carmen Gómez Becerra
// EDA - GDV29
// Complejidad logaritmica. O(log n), la busqueda binaria va reduciendo el problema a la mitad en cada iteracion (divide y venceras), mas eficiente que busqueda lineal. 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// siendo estrictamente decrecientes hasta un determinado valor a partir del cual son estrictamente crecientes, se pide encontrar el valor del minimo.
int minimo(const vector<int>& sec, int ini, int fin) {
    int arraySize = sec.size();
    if (arraySize == 1 || sec[0] < sec[1]) return sec[0]; // caso valor unico y extremo valor izquierda

    if (sec[arraySize - 1] < sec[arraySize - 2]) return sec[arraySize - 1]; // caso valor extremo derecha.

    if (ini < fin-1 && !sec.empty()) { // mientras ini sea menor que fin y no este vacio, actua.
        int m = (ini + fin) / 2; // punto medio (se ira actualizando conforme vaya buscando)
        if (sec[m] != sec[0] && sec[m] != sec[arraySize-1]) { // si no es ni el primero ni el ultimo del array (mirados anteriormente)
            // va buscando el elemento mas pequenio de la curva concava
            if (sec[m] < sec[m - 1] && sec[m] < sec[m + 1]) { // si a la izquierda y a la derecha de la mitad son mayores...
                return sec[m]; // hemos acabado.
            }

            if (sec[m] < sec[m + 1]) { // si el de la derecha es mayor, mira a la izquierda...
                return minimo(sec, ini, m);
            }

            if (sec[m] < sec[m - 1]) { // si el de la izquierda es mayor, mira a la derecha...
                return minimo(sec, m + 1, fin);
            }
        }
    }
    return 0; // si no lo ha encontrado, false (no sale nunca este caso).
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (!cin) return false;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << minimo(sec, 0, n) << endl;
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
    //system("PAUSE");
#endif

    return 0;
}