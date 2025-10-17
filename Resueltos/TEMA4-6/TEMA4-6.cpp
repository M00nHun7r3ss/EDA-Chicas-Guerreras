// Carmen Gómez Becerra
// EDA - GDV29


#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>

#include "Set.h"

// Complejidad O(n*m). n=s.nelems, m=nElems
// le pasas el set de elementos y el numero de menores que se desea extraer
// devuelve otro set con los menores ordenados.
Set<int> ordenaMenores(Set<int> s, int nElems){
    // set a retornar (auxiliar).
    Set<int> auxSet;

    // hace la extraccion del menor tantas veces como nElems pida.
    for (int i = 0; i < nElems; i++){
        // obtiene el menor del original
        int min = s.getMin(); // O(n)

        // se lo guarda en el auxiliar
        auxSet.add(min); // O(n)

        // lo elimina del original
        s.remove(min); // O(n)

        // Por cada iteracion O(n) + O(n) + O(n) = O(n).
        // Dentro del bucle es O(n).
    }

    // La operacion for es O(m), dentro del bucle es O(n), por tanto for(O(n)) es O(n) * O(m).
    // Conclusion: la complejidad es O(n*m).

    return auxSet;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    std::cin >> n;

    if (n == 0)
        return false;

    Set<int> set;
    int elem;

    // mientras elem no lea '-1'
	while (cin >> elem && elem != -1) {
		set.add(elem);
	}

    std::cout << ordenaMenores(set, n) << std::endl;

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
