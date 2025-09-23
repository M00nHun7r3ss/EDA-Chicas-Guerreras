// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool anagramas(const string& cad1, const string& cad2) {
    
    //Damos por hecho que no es un anagrama
    bool anagrama = false;

    //vamos recorriendo ambas cadenas simultaneamente
    int i = 0, j = 0;
    while (i < cad1.size() && j < cad2.size())
    {

    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    string word1, word2;
    cin >> word1 >> word2;

    // solucion
    cout << (anagramas(word1, word2) ? "SI" : "NO") << endl;
}

//#define DOMJUDGE
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