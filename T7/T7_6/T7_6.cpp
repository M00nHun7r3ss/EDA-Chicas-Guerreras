#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

using Pelicula = string;
using Actor = string;
using RepartosPeliculas = map<Pelicula, map<Actor, int>>;

void leerRepartos(int numPeliculas, RepartosPeliculas& peliculas) {
    Pelicula peli; int numActores;
    Actor actor; int minutos;

    for (int i = 0; i < numPeliculas; ++i) {
        cin >> peli; cin >> numActores;

        for (int j = 0; j < numActores; ++j) {
            cin >> actor >> minutos;
            peliculas[peli][actor] += minutos;
        }
    }
}

void procesarEmisiones(RepartosPeliculas const& repartos,
    vector<string> const& secEmisiones) {

    // cuenta emisiones por peli
    map<Pelicula, int> vecesPeli;
    // acumula minutos totales por actor
    map<Actor, int> tiempoActor;
    // guarda ultima pos de cada peli
    map<Pelicula, int> ultimaPos;

    // recorrer emisiones
    for (int i = 0; i < secEmisiones.size(); ++i) {
        Pelicula peli = secEmisiones[i];

        // contar pelicula
        vecesPeli[peli]++;

        // guardar ultima pos
        ultimaPos[peli] = i;

        // sumar minutos de actores
        for (auto const& par : repartos.at(peli)) {
            tiempoActor[par.first] += par.second;
        }
    }

    // PELICULA
    Pelicula mejorPeli;
    int maxVeces = -1;
    int mejorPos = -1;

    // recorremos pelis
    for (auto const& p : vecesPeli) {
        const Pelicula& peli = p.first;

        // mas emisiones o empate mas reciente
        if (p.second > maxVeces || (p.second == maxVeces && ultimaPos[peli] > mejorPos)) {

            maxVeces = p.second;
            mejorPeli = peli;
            mejorPos = ultimaPos[peli];
        }
    }

    // Imprimimos resultado
    cout << maxVeces << " " << mejorPeli << "\n";

    // ACTORES
    int maxTiempo = 0;

    // Buscamos el maximo tiempo acumulado
    for (auto const& par : tiempoActor) {
        maxTiempo = max(maxTiempo, par.second);
    }

    vector<Actor> mejores;

    // Guardamos todos los actores con ese mazimo
    for (auto const& p : tiempoActor) {
        if (p.second == maxTiempo) {
            mejores.push_back(p.first);
        }
    }

    //ordenamos
    sort(mejores.begin(), mejores.end());

    cout << maxTiempo;

    for (auto const& a : mejores) {
        cout << " " << a;
    }

    cout << "\n";
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int numPelis, numEmisiones;
    cin >> numPelis;
    if (numPelis == 0)
        return false;

    // Lectura de los repartos de las peliculas
    RepartosPeliculas repartos;
    leerRepartos(numPelis, repartos);

    // Lectura de la secuencia de peliculas emitidas en vector<string>
    cin >> numEmisiones;
    vector<string> secEmisiones(numEmisiones);
    for (string& s : secEmisiones) cin >> s;

    procesarEmisiones(repartos, secEmisiones);

    return true;
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}

