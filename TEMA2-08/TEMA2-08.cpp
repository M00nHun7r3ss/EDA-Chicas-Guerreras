// Carmen Gómez Becerra
// EDA - GDV29
// Complejidad logaritmica. O(log n), la busqueda binaria va reduciendo el problema a la mitad en cada iteracion (divide y venceras), mas eficiente que busqueda lineal. 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
int minimo(const vector<int>& sec, int ini, int fin, int min, int c) {

    if(!sec.empty()) { // si no es vacio
        int m = (ini + fin) / 2;

        // si el minimo es mayor que el elemento de la mitad.
        if (min > sec[m]) {
            // lo reasignamos y le ponemos un valor mas pequeño
            min = sec[m]; 

            if (c >= sec.size()-1) { // si hemos comprobado todo
                return min;
            }
            else if (c < (sec.size() - 1) / 2) { // si c esta antes que la mitad del array, busca por la izquierda
                c++;
                return minimo(sec, ini, m, min, c); // mira mitad izquierda
            }
            else { // busca por la derecha
                c++;
                return minimo(sec, m + 1, fin, min, c); // mira mitad derecha.
            }
	        
        }
    }
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
    cout << minimo(sec, 0, n, INT_MAX, 0) << endl;
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
