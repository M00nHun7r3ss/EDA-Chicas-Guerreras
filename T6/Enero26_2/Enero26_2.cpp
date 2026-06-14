
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "bintree_eda.h"
using namespace std;

// Estructura auxiliar para devolver la informacion de barcos y hueco libre
struct Info {
    int barcos;
    int hueco;
};

// Complejidad: O(n) en tiempo, donde n es el numero total de islas 
Info calcularFlota(bintree<int> const& a, int capacidad) {

    // Caso base, si el esta vacío, no se requieren barcos ni hay espacio libre.
    if (a.empty()) {
        return { 0, 0 };
    }

    // Procesamos ambos lados del arbol
    Info izq = calcularFlota(a.left(), capacidad);
    Info der = calcularFlota(a.right(), capacidad);

    // Unimos los barcos que confluyen y el espacio total libre disponible
    int barcosTotales = izq.barcos + der.barcos;
    int huecoDisponible = izq.hueco + der.hueco;
    int tesorosIsla = a.root();

    // Gestionamos la carga de los tesoros de la isla actual
    if (tesorosIsla <= huecoDisponible) {
        // Los tesoros de la isla caben en los huecos de la flota acumulada
        huecoDisponible -= tesorosIsla;
    }
    else {
        // No caben en los huecos actuales. Llenamos los barcos existentes hasta el limite
        int sobrantes = tesorosIsla - huecoDisponible;

        // Calculamos cuantos barcos adicionales hacen falta 
        int barcosNuevos = (sobrantes + capacidad - 1) / capacidad;
        int capacidadNueva = barcosNuevos * capacidad;

        barcosTotales += barcosNuevos;
        huecoDisponible = capacidadNueva - sobrantes;
    }

    return { barcosTotales, huecoDisponible };
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> arch;
    int capacidad;
    arch = leerArbol(-1);
    std::cin >> capacidad;

    Info resultado = calcularFlota(arch, capacidad);

    cout << resultado.barcos << " " << resultado.hueco << "\n";
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
