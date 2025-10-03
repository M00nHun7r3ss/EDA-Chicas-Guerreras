/*
Nombre completo: Carmen Gómez Becerra
DNI: 06330538H
Usuario del juez: EDA-GDV29   
Puesto de laboratorio: Pto0101
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Complejidad logaritmica. O(log n), la busqueda binaria va reduciendo el problema a la mitad en cada iteracion (divide y venceras), mas eficiente que busqueda lineal.

// función que resuelve el problema
int resolver(const vector<int>& sec, int ini, int fin, int inc) {
    
    if (inc > 0){ // si el incremento es mayor que cero.
        if (ini < fin && !sec.empty()) { // mientras ini sea menor que fin y no este vacio, actua.

            // va buscando el elemento del salario.
            int m = (ini + fin) / 2; // punto medio (se ira actualizando conforme vaya buscando)

            int diff = sec[m] - sec[m - 1]; // el actual menos el anterior.

            if (diff == inc) {
                return m; // hemos acabado.
            }
            else if (diff > inc) { // si la diferencia es mayor, mira por la izquierda.
                return resolver(sec, ini, m, inc);
            }
            else { // si la diferencia es menor, mira por la derecha.
                return resolver(sec, m + 1, fin, inc);
            }
        }
    }
    else { // si el incremento es CERO.
        return 0;
    }
    
    return -1; // si no lo ha encontrado, false.
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, inc;
    cin >> inc >> n;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    // Llamada a función y escritura de la salida
    std::cout << resolver(sec, 1, n, inc) << std::endl; // empieza en 1 porque va restando siempre al anterior, para que no se salga del vector.
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input2.txt");
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
