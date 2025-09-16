// Carmen Gómez Becerra
// EDA-GDV29


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// función que resuelve el problema
std::string resolver(int i, int n) {
    // si no se han recorrido y comprobado todos los valores 
    if (i < n) {
        return "DESCONOCIDO";
    }
    else {
        return "DALTON";
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nElems; // elementos de la secuencia.
    std::cin >> nElems;

    if (nElems == 0)
        return false;

    // casos DESCONOCIDO (v[i], v[i+1], v[i+2], ...):
    // si v[i] <= v[i+1] && v[i+1] >= v[i+2]
    // si v[i] >= v[i+1] && v[i+1] <= v[i+2]

    // 1 <= 2 ES && 2 >= 2 ES -> acaba
    // 1 <= 2 ES && 2 >= 3 NO -> sigue
    // 4 >= 3 ES && 3 <= 2 NO -> sigue
    
    // leer la cadena y almacenarla.
    std::vector<int> v(nElems);
    for (int i = 0; i < nElems; ++i) {
        std::cin >> v[i];
    }

    // si se cumplen las condiciones para de leer el caso y directamente pone DESCONOCIDO.
    int i = 0;
    int n = nElems - 3; // ponemos que busque hasta nElems-2 para que no se salga del vector por lo de v[i+1] v[i+2]
    while (i < n)
        //|| v[i] <= v[i + 1] && v[i + 1] >= v[i + 2] || v[i] >= v[i + 1] && v[i + 1] <= v[i + 2]) 
    {
        ++i;
    }

    std::string sol = resolver(i, n);

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

