// Carmen Gómez Becerra
// EDA-GDV29
// Complejidad cuadratica O(n^2): bucles anidados.

#include <iostream>
#include <fstream>
#include <vector>

// Divide el conjunto de elementos en una parte ordenada y otra desordenada.
// Toma un elemento de la parte desordenada y lo inserta en la posición correcta en la parte ordenada.
// Repite este proceso hasta que todos los elementos estén ordenados.
void insertionSort(std::string &cad, int size) {
    for (int i = 1; i < size; ++i) {
        int key = cad[i];
        int j = i - 1;

        while (j >= 0 && cad[j] > key) {
            cad[j + 1] = cad[j];
            j = j - 1;
        }

        cad[j + 1] = key;
    }
}

bool anagramas(const std::string& cad1, const std::string& cad2) {

    // al principio asumimos que no es anagrama
	bool anagrama = false;

    int nCad1 = cad1.length();
    int nCad2 = cad2.length();
    
    // si ambas cadenas son del mismo tamanio entra al bucle, si no, directamente false.
    if (nCad1 == nCad2) {
        // listas que seran ordenadas alfabeticamente.
        std::string auxCad1 = cad1;
        std::string auxCad2 = cad2;

        // ordena alfabeticamente las dos listas y compara.
        insertionSort(auxCad1, nCad1);
        insertionSort(auxCad2, nCad2);

        anagrama = auxCad1 == auxCad2;
    }

	return anagrama;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    std::string word1, word2;
    std::cin >> word1 >> word2;
    std::cout << (anagramas(word1, word2) ? "SI" : "NO") << std::endl;
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