// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "horas.h"

// metodo que gestiona el output de cada hora
void resuelveHora(Horas* h){

    // TODO lo has hecho mal porque aun no has leido lo que hay abajo, recuerda.
    if (!h->correctDate()){
        std::cout << "ERROR";
    }
    else if () {
	    
    }

    std::endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n, // numero de trenes de la estacion
		m; // horas a consultar

    std::cin >> n >> m;

    // El numero de trenes que sale de la estacion es siempre mayor que cero y menor que 1000.
    // La entrada termina con 0 0
    if (((n <= 0) || (n > 1000)) && m <= 0)
        return false;

    // crea un nuevo Horas.
    Horas* t = new Horas(0, 0, 0); 

    for (int i = 0; i < n; ++i){
        std::cin >> t; // lee
        resuelveHora(t);
    }

    if ()

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

