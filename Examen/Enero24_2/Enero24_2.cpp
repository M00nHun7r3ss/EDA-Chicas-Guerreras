#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// funcion que resuelve el problema
// Busqueda binaria sobre Solucion(i) = A[i] - B[i]
pair<int, int> resolver(vector<int> const A, vector<int> const B) {

    int n = A.size();

    int ini = 0, fin = n - 1;

    //Buscamos entre medias
    while (ini <= fin) {
        //Mitad
        int mid = (ini + fin) / 2;
        //Vemos si esta en la mitad
        int diferencia = A[mid] - B[mid];

        //Acierto
        if (diferencia == 0) {
            return { mid, -1 };
        }
        //Buscamos en mitad derecha
        else if (diferencia < 0) {
            ini = mid + 1;
        }
        //Buscamos en mitad izquierda
        else {
            fin = mid - 1;
        }
    }

    // No existe cruce exacto
    // El cruce estaría entre fin e inicio
    // Se revierte ini y fin, porque al avanzar, se cruzan y fin pasa a ser menor que ini, e ini mayor que fin
    return { fin, ini };

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracion, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0) return false;

    vector<int> A(n);
    for (int i = 0; i < n; ++i) cin >> A[i];
    vector<int> B(n);
    for (int i = 0; i < n; ++i) cin >> B[i];

    pair<int, int> sol = resolver(A, B);

    // escribir sol
    //ACIERTO, posicion exacta
    if (sol.second == -1) {
        cout << "SI " << sol.first << "\n";
    }
    //POSICION INTERMEDIA
    else {
        cout << "NO " << sol.first << " " << sol.second << "\n";
    }

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
