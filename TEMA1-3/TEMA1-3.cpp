// Carmen Gómez Becerra
// EDA-GDV29


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// función que resuelve el problema
std::string resolver(bool divides) {
    if (divides) return "SI";
    return "NO";
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int n; // numero de elementos de la secuencia
    int d; // en que posicion se divide la secuencia (este inclusive)

    // leer los datos de la entrada
    std::cin >> n >> d;

    // almacenamos en un vector la secuencia.
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }

    // va buscando el mayor de la izquierda y mira si es menor que el menor de la derecha.
    // (x, y , d, z, t)
    // si "y" mayor izquierda
    // si "t" menor derecha
    // si y > t -> se corta la busqueda

    bool divides = true; // asumimos inicialmente que va a dividir bien
    int maxLeft = 0; // mayor de la izquierda
    int i = 0;
    while (i < n && divides) {
        // si sigue en el tramo de la izquierda y busca el mayor elemento
        if (i <= d && v[i] >= maxLeft) maxLeft = v[i];

        // si hay alguno de la derecha que sea menor que maxLeft, corta bucle y directamente (divides = false)
        if (i > d && v[i] < maxLeft) divides = false;
        i++;
    }

    std::string sol = resolver(divides);

    // escribir sol
    std::cout << sol << std::endl;

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