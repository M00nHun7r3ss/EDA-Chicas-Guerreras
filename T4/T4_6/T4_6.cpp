// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Set.h"
using namespace std;

//Devuelve los k numeros menores distintos de la serie
/*Complejidad:
O(n * k) donde n = elementos de la serie y k = numero maximo de elementos a mantener
Porque recorrera todos los elementos n de la serie, e internamente, como maximo la complejidad sera O(k)
 */

Set<int> resolver(int k, const vector<int>& datos)
{
    Set<int> resultado;

    for (int i = 0; i < datos.size(); i++) // Complejidad O(n)
    {
        //Si no contiene ya los datos
	    if (!resultado.contains(datos[i])) // Complejidad O(k) 
	    {
            //Y hay sitio
		    if (resultado.size() < k)
		    {
                //lo aniade
                resultado.add(datos[i]); // Complejidad O(k) 
		    }
            //Sin embargo, si no hay sitio, y el menor que el maximo
            else if (datos[i] < resultado.getMax()) // Complejidad O(1) 
            {
	            //Sustituiremos el maximo por el nuevo elemento
                resultado.removeMax(); // Complejidad O(k) 
                resultado.add(datos[i]); // Complejidad O(k) 
            }
	    }
    }

    return resultado;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int k;
    cin >> k;

    if (k == 0) return false;

    int n;
    cin >> n;
    vector<int> datos;
    while (n != -1)
    {
        datos.push_back(n);
        cin >> n;
    }

    Set<int> solucion = resolver(k, datos);

    cout << solucion << endl;

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}