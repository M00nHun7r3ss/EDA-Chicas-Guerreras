#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Complejidad O(log n), n = nelems del vector
int resolver(const vector<int>& sec, int ini, int fin) {

    int mit = (ini + fin) / 2; // valor mitad

    // mientras ini sea menor que fin y no este vacio, actua.
    if (ini < fin && !sec.empty()) {
        if (sec[mit] % 2 != 0) { // mira si mitad impar
            return sec[mit]; 
        }
        else {
            // en este caso no esta claro cuando sube y cuando baja, asi que lo hacemos a la vez
            int izq = resolver(sec, ini, mit); // busca izquierda
            int der = resolver(sec, mit + 1, fin); // busca derecha

            // si alguno es impar, returnea
            if (izq != 0) return izq;
            if (der != 0) return der;
        }
    }

    // en otro caso
    return 0;
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