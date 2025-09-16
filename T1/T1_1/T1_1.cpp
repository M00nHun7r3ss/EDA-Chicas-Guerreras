// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema
bool resolver(std::vector<int> datos) {

    int n = datos.size();

    //Contadores de secuencias
    //i es el numero de personajes
    //j es el numero de secuencias de menor a mayor
    //k es el numero de secuencias de mayor a menor
    int i = 0, j = 0, k = 0;

    //recorremos hasta el final
    while (i < n - 1)
    {
        if (datos[i] < datos[i + 1]) //Menor a mayor
            j++;
        else if (datos[i] > datos[i + 1]) //Mayor a menor
            k++;
        //esto lo actualizamos siempre que avanzamos
        i++;
    }

    //Si todos estan ordenados, ya sea de menor a mayor o mayor a menor sera true, si no, false
    return k == i || j == i;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    // leer numero de datos
    int nDatos;
    std::cin >> nDatos;

    if (nDatos < 1) return false;

    // leemos los datos en si
    std::vector<int> datos(nDatos);
    for (int i = 0; i < nDatos; ++i) {
        std::cin >> datos[i];
    };

    // escribir sol
    // Si estan ordenados, seran los dalton
    if (resolver(datos))
    {
        std::cout << "DALTON" << std::endl;
    }
    // Si no, sean desconocidos
    else
    {
        std::cout << "DESCONOCIDOS" << std::endl;
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
