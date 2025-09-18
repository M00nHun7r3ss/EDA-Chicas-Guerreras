// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// función que resuelve el problema
void resolver(std::vector<int>& datos) {

    //Contadores
    int val = 0, pic = 0;

    //recorremos hasta el final
    for (int i = 1; i < datos.size() - 1; i++) {

        if (datos[i] < datos[i - 1] && datos[i] < datos[i + 1]) //Mayor - Menor - Mayor = valle
        {
            val++;
        }
        else if (datos[i] > datos[i - 1] && datos[i] > datos[i + 1]) //Menor - Mayor - Menor = pico
        {
            pic++;
        }
    }

    //Reutilizamos el propio vector para devolver el resultado
    datos[0] = pic;
    datos[1] = val;

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int nDatos;
    std::cin >> nDatos;

    //rellenamos el vector
    std::vector<int> datos(nDatos);
    for (int i = 0; i < nDatos; ++i) {
        std::cin >> datos[i];
    };

    resolver(datos);

    // escribir sol
    std::cout << datos[0] << " " << datos[1] << std::endl;

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