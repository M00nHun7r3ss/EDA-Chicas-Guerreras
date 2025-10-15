// Carmen Gómez Becerra
// EDA-GDV29

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "horas.h"

// Complejidad lineal O(n) -> el tiempo de ejecucion es directamente proporcional a n, que es el tamanio de la entrada.
// metodo que gestiona el output de cada hora comparandolo con el horario de trenes.
void resuelveHora(Horas& h, std::vector<Horas>& v){

    if (!h.correctDate()){
        std::cout << "ERROR" << std::endl;
    }
    else{
        // buscamos el tren mas cercano a la hora consultada, inicialmente falso.
        bool found = false;
        int i = 0;
        while (i < v.size() && !found){
            // el primer elemento que sea mayor o igual que el actual, es el siguiente tren.
            if (h <= v[i]){
                found = true;
                std::cout << v[i] << std::endl;
            }
            i++;
        }

        // si no lo ha encontrado, es que no hay trenes ya.
        if (!found) std::cout << "NO" << std::endl;
    }
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

    // trenes (horarios)
    std::vector<Horas> trenes(n);

    for (int i = 0; i < n; ++i)
	    std::cin >> trenes[i];

    for (int i = 0; i < m; ++i){
        Horas auxH;
        std::cin >> auxH;
        resuelveHora(auxH, trenes);
    }
    
    std::cout << "---" << std::endl;

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

