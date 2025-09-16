// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// función que resuelve el problema
void resolver(std::vector<int>& datos) {

    for (int i = 0; i < datos.size(); i++)
    {
        datos[i] *= 2;
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    // numero de datos
    int nDatos;
    std::cin >> nDatos;
    // datos en sí
    std::vector<int> datos(nDatos);
    for (int i = 0; i < nDatos; i++)
    {
        std::cin >> datos[i];
    }

    resolver(datos);

    // escribir sol
    for (int i = 0; i < nDatos; i++)
    {
        std::cout << datos[i] << " ";
    }

    std::cout << std::endl;

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