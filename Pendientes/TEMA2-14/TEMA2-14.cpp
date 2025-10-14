
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
int resolver(const vector<int>& sec, int ini, int fin) {

    if (!sec.empty()){ // mientras no este vacio, actua
        int vSize = sec.size();

        // CASO 1 elemento
        if (vSize == 1) return sec[0]; 

        int m = (ini + fin) / 2; // punto medio

        // CASOS extremo derecha y extremo izquierda:
        // - si se llega al ultimo del array, lo devuelve porque ha llegado al final. (CASO extremo derecha)
        // - si es el primero del array y el siguiente no es consecutivamente mayor, devuelve porque el salto esta al principio. (CASO extremo izquierda)
        if ((sec[m] == sec[vSize-1]) || (sec[m] == sec[0] && sec[m + 1] != sec[m] + 1)){ 
            return sec[m]; 
        }

        // CASOS normales, en el centro del vector, con anterior y posterior:
        if (ini < fin){ 

            // si el siguiente no es consecutivamente mayor, y el anterior es consecutivamente menor, hemos acabado.
            if ((sec[m + 1] != sec[m] + 1) && (sec[m-1] == sec[m] - 1)){
                return sec[m];
            }

            // si el siguiente no es consecutivamente mayor, y el anterior tampoco, mira a la izquierda.
            if ((sec[m + 1] != sec[m] + 1) && (sec[m - 1] != sec[m] - 1)){
                return resolver(sec, ini, m);
            }

            // si el siguiente es consecutivamente mayor, mira a la derecha.
            if ((sec[m + 1] != sec[m] + 1)){
                return resolver(sec, m+1, fin);
            }
        }
    }
    return -1; // si no lo ha encontrado, false.
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << resolver(sec, 0, n) << endl;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input3.txt");
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
