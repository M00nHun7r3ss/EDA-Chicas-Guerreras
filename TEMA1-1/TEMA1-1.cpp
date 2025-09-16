// Carmen Gómez Becerra
// EDA-GDV29


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// función que resuelve el problema
std::string resolver(bool cond) {
    std::string r; // resultado
    // si se cumple la condicion es desconocido
    if (cond) {
        r = "DALTON";
    }
    else {
        r = "DESCONOCIDOS";
    }

    return r;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nElems; // elementos de la secuencia.
    std::cin >> nElems;

    if (nElems == 0)
        return false;

    // leer la cadena y almacenarla en el vector v.
    std::vector<int> v(nElems);
    for (int i = 0; i < nElems; ++i) {
        std::cin >> v[i];
    }

    bool isDalton = true; // inicialmente asumimos que es dalton.
    bool isUpward = false; // ascendente -> true; descendente -> false;

    if (v[0] < v[1]) isUpward = true; // si el primero es menor que el segundo iniciamos ascendente.

    int i = 0;
    while (i < nElems - 1 && isDalton) { // va buscando hasta que deje de ser dalton (nElems-1 para que al v[i+1] no se pase).

        // (a, b, c)
        // si ascendente y a >= b -> NO DALTON
        // si descendente y a <= b -> NO DALTON
        if ((isUpward && v[i] >= v[i + 1]) || (!isUpward && v[i] <= v[i + 1])) {
            isDalton = false;
        }
        i++;
    }


    std::string sol = resolver(isDalton);

    // escribir sol
    std::cout << sol << std::endl;

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