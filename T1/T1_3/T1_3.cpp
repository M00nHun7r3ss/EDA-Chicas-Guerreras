// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema
bool resolver(std::vector<int>& datos, int pos) {

    //Damos por hecho que es menor desde el principio y vamos confirmando
    bool menor = true;

    //Buscamos el máximo hasta la posición
    int max = datos[0];
    for (int i = 0; i < pos + 1; i++) {
        if (max < datos[i]) {
            max = datos[i];
        }
    }

    //Ahora comprobamos la condicion, buscando que los del lado derecho sean mayores
    int i = pos + 1;

    //Busqueda por bandera, hasta el final
    while (i < datos.size() && menor) {

        //Si alguno de los datos del lado derecho es menor que el maximo del lado izquierdo,
        //no se cumplira la condicion
        if (max >= datos[i]) {

            menor = false;
        }

        i++;

    }

    return menor;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    // leemos el numero de datos y la posicion
    int nDatos, pos;
    std::cin >> nDatos >> pos;

    // rellenamos el vector
    std::vector<int> datos(nDatos);
    for (int i = 0; i < nDatos; ++i) {
        std::cin >> datos[i];
    }

    // escribir sol
    if (resolver(datos, pos)) { //Vector correctamente dividido
        std::cout << "SI" << std::endl;

    }
    else { //Vector incorrectamente dividido
        std::cout << "NO" << std::endl;
    }

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