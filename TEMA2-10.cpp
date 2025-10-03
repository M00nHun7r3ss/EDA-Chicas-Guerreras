// Carmen Gómez Becerra
// EDA - GDV29
// Complejidad logaritmica. O(log n), la busqueda binaria va reduciendo el problema a la mitad en cada iteracion (divide y venceras), mas eficiente que busqueda lineal. 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
int resolver(const vector<int>& sec, int ini, int fin) {
    if (ini < fin && !sec.empty()) { // mientras ini sea menor que fin y no este vacio, actua.
        // va buscando el elemento impar.
        int m = (ini + fin) / 2; // punto medio (se ira actualizando conforme vaya buscando)
        if (sec[m] % 2 != 0) { // si v[m] es impar
            return sec[m]; // hemos acabado.
        }

        // va mirando ambos valores a la vez.
        int left = resolver(sec, ini, m); // mira mitad izquierda
        int right = resolver(sec, m+1, fin); // mira mitad derecha.

        if (left % 2 != 0) return left;
        if (right % 2 != 0) return right;
    }
    return 0; // si no lo ha encontrado, false.
}

int rec() {

    // caso base
    if (true) {
        return 0;
    }

    //
    int left = rec();
    int right = rec();

    if (left == 0)
        return left;


}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0) return false;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << resolver(sec, 0, n) << endl;
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
