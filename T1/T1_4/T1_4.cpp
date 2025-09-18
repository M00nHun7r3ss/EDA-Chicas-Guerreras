// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema
void resolver(std::vector<int>& datos) {

    //usaremos un vector auxiliar para dejar los pares a un lado y redimensionar 
    std::vector<int> aux;
    int i = 0;
    int newSize = 0;

    //Buscamos los pares y los guardamos en el auxiliar
    while (i < datos.size()) {

        if (datos[i] % 2 == 0)
        {
            aux.insert(aux.begin() + newSize, datos[i]);
            newSize++;
        }

        i++;
    }

    //Redimensionamos al nuevo tamanio y reemplazamos los datos para devolverlos
    datos.resize(newSize);
    for (int i = 0; i < datos.size(); i++) {
        datos[i] = aux[i];
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	// leemos el numero de datos
    int nDatos;
    std::cin >> nDatos;

    //rellenamos el vector
    std::vector<int> datos(nDatos);
    for (int i = 0; i < nDatos; ++i) {
        std::cin >> datos[i];
    }

    //quitamos los impares
    resolver(datos);

    // escribir sol
    for (int i = 0; i < datos.size(); ++i) {
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