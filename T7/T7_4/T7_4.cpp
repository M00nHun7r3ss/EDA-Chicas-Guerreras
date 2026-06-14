#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

// función que resuelve el problema
int resolver(vector<int> const& v) {

    // elementos sin repetir
    unordered_set<int> serie; 

    //Inicio
    int ini = 0;  
    int maxLen = 0;

    // recorremos con fin
    for (int fin = 0; fin < v.size(); fin++) {

        // si hay repetido, movemos ini hasta eliminarlo, porque no nos interesan los repetidos
        while (serie.count(v[fin])) {
            serie.erase(v[ini]);
            ini++;
        }

        // aniadimos el nuevo elemento
        serie.insert(v[fin]);

        // actualizamos maximo de dias con capitulos distintos en emision
        int longitud = fin - ini + 1;
        if (longitud > maxLen)
            maxLen = longitud;
    }

    return maxLen;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;

    vector<int> datos(n);
    for (int i = 0; i < n; i++) {
        cin >> datos[i];
    }

    //Escribe solucion
    int sol = resolver(datos);

    cout << sol << "\n";
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
    system("PAUSE");
#endif

    return 0;
}