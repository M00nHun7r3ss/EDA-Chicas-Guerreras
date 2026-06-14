#include <iostream>
#include <stdexcept>
#include <fstream>
#include <list>
#include <utility>
#include <map>
#include <set>
#include <list>

using namespace std;

using Jugador = string;
using Equipo = string;

class GestorFutbolistas {
private:

    map<Jugador, Equipo> jugadorEquipo;
    map<Equipo, int> numJugadores;
    map<Equipo, list<Jugador>> fichajes;
    map<Jugador, set<Equipo>> historial;


public:
    // Coste: O(log n)
    void fichar(const Jugador& jugador, const Equipo& equipo) {

        // jugador nuevo
        //Si el jugador no estaba ya en el map
        if (!jugadorEquipo.count(jugador)) {
            //Adjudicamos clave-valor
            jugadorEquipo[jugador] = equipo;
            //Subimos el numero de jugadores del equipo
            numJugadores[equipo]++;
            //Aniadimos el jugador a la lista del equipo
            fichajes[equipo].push_back(jugador);
            //Y el equipo en la lista del jugador
            historial[jugador].insert(equipo);
        }
        //No es un jugador nuevo, ya estaba jugando en algun equipo
        else {
            //Vemos en cual de los equipos estaba jugando
            Equipo actual = jugadorEquipo[jugador];

            // si ya esta en ese equipo, nada
            if (actual == equipo) return;

            // si es otro equipo, quitar del equipo anterior
            numJugadores[actual]--;

            // aniadir al nuevo con todos los pasos de antes
            jugadorEquipo[jugador] = equipo;
            numJugadores[equipo]++;
            fichajes[equipo].push_back(jugador);
            historial[jugador].insert(equipo);
        }
    }

    // Coste: O(log n)
    Equipo equipoActual(const Jugador& jugador) const {
        //Este jugador no existe
        if (!jugadorEquipo.count(jugador))
            throw domain_error("Jugador inexistente");
        
        return jugadorEquipo.at(jugador);
    }

    // Coste: O(log n)
    int fichados(const Equipo& equipo) const {
        //Este equipo no tiene jugadores, por tanto no existe
        if (!numJugadores.count(equipo))
            throw domain_error("Equipo inexistente");

        return numJugadores.at(equipo);
    }

    // Coste: Si toca recorrer la lista entera, pues O(n) siendo n el numero de jugadores totales
    list<Jugador> ultimosFichajes(const Equipo& equipo, int n) const {
        //Este equipo no tiene jugadores, por tanto no existe
        if (!numJugadores.count(equipo))
            throw domain_error("Equipo inexistente");
        
        //Los jugadores
        list<Jugador> sol;

        //Pasamos por todos los fichajes del equipo
        auto const& lista = fichajes.at(equipo);

        auto it = lista.rbegin();

        //Y mientras haya jugadores
        while (it != lista.rend() && sol.size() < n) {

            const Jugador& j = *it;

            //Si el jugador esta en el equipo, lo aniadimos
            if (jugadorEquipo.at(j) == equipo) {
                sol.push_back(j);
            }

            ++it;
        }

        return sol;
    }

    // Coste: O(log N)
    int cuantosEquipos(const Jugador& jugador) const {
        //Si no ha estado en ningun equipo
        if (!historial.count(jugador)) return 0;

        return historial.at(jugador).size();
    }
};


bool resuelveCaso() {
    string operacion;
    cin >> operacion;
    if (!cin) return false;

    GestorFutbolistas gestor;
    while (operacion != "FIN") {
        try {
            if (operacion == "fichar") {
                string jugador, equipo;
                cin >> jugador >> equipo;
                gestor.fichar(jugador, equipo);
            }
            else if (operacion == "equipo_actual") {
                string jugador;
                cin >> jugador;
                string equipo = gestor.equipoActual(jugador);
                cout << "El equipo de " << jugador << " es " << equipo << endl;
            }
            else if (operacion == "fichados") {
                string equipo;
                cin >> equipo;
                int n = gestor.fichados(equipo);
                cout << "Jugadores fichados por " << equipo << ": " << n << endl;
            }
            else if (operacion == "ultimos_fichajes") {
                string equipo;
                int n;
                cin >> equipo >> n;
                list<string> ultimos = gestor.ultimosFichajes(equipo, n);
                cout << "Ultimos fichajes de " << equipo << ": ";
                for (const auto& jugador : ultimos) {
                    cout << jugador << " ";
                }
                cout << endl;
            }
            else if (operacion == "cuantos_equipos") {
                string jugador;
                cin >> jugador;
                int n = gestor.cuantosEquipos(jugador);
                cout << "Equipos que han fichado a " << jugador << ": " << n << endl;
            }
        }
        catch (std::exception& e) {
            cout << "ERROR: " << e.what() << "\n";
        }
        cin >> operacion;
    }

    cout << "---\n";
    return true;
}

//#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
