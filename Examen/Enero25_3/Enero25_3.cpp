#include <iostream>
#include <stdexcept>
#include <fstream>
#include <list>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <set>

using namespace std;

using Jugador = string;
using Equipo = string;

class GestorFutbolistas {
private:
    struct InfoJugador {
        Equipo actual;
        set<Equipo> historial;
    };

    struct InfoEquipo {
        unordered_set<Jugador> fichados;
        list<Jugador> ordenFichajes;
    };

    unordered_map<Jugador, InfoJugador> jugadores;
    unordered_map<Equipo, InfoEquipo> equipos;

public:
    // Coste: O(1)
    void fichar(const Jugador& jugador, const Equipo& equipo) {
        // Si el equipo no existe, lo creamos
        if (!equipos.count(equipo)) {
            equipos[equipo] = InfoEquipo();
        }

        // Si el jugador no existe, lo creamos y se lo pasamos al equipo
        if (!jugadores.count(jugador)) {
            jugadores[jugador] = InfoJugador{ equipo, {equipo} };
            equipos[equipo].fichados.insert(jugador);
            equipos[equipo].ordenFichajes.push_front(jugador);
        }
        //Si el jugador ya existia
        else {
            InfoJugador& infoJ = jugadores[jugador];

            // Si ya esta en ese equipo, no hacemos nada
            if (infoJ.actual == equipo) return;

            // Si estaba en otro equipo
            // Sale del equipo anterior
            Equipo anterior = infoJ.actual;
            equipos[anterior].fichados.erase(jugador);

            // Entra en el nuevo equipo
            infoJ.actual = equipo;
            infoJ.historial.insert(equipo);
            equipos[equipo].fichados.insert(jugador);
            equipos[equipo].ordenFichajes.push_front(jugador);
        }
    }

    // Coste: O(1)
    Equipo equipoActual(const Jugador& jugador) const {
        //throw domain_error("Jugador inexistente");
        //Si el jugador no existe
        if (!jugadores.count(jugador))
            throw domain_error("Jugador inexistente");

        //Si existe, devuelve el jugador actual
        return jugadores.at(jugador).actual;
    }

    // Coste: O(1)
    int fichados(const Equipo& equipo) const {
        //throw domain_error("Equipo inexistente");
        //Si el equipo no existe
        if (!equipos.count(equipo))
            throw domain_error("Equipo inexistente");

        //Si existe nos dice el tamanio
        return equipos.at(equipo).fichados.size();
    }

    // Coste: 0(n) siendo n todos los jugadores posibles de la lista
    list<Jugador> ultimosFichajes(const Equipo& equipo, int n) const {
        //throw domain_error("Equipo inexistente");

    	//Si el equipo no existe
        if (!equipos.count(equipo))
            throw domain_error("Equipo inexistente");

        //La lista
        list<Jugador> jList;
        //Coge el equipo
        const InfoEquipo& infoE = equipos.at(equipo);

        //Repasa todo el equipo y guarda los jugadores en la lista
        for (const Jugador& j : infoE.ordenFichajes) {
            if (infoE.fichados.count(j)) {
                jList.push_back(j);
                //Hasta llenarla
                if (jList.size() == n) break;
            }
        }

        //Devuelve la lista
        return jList;
    }

    // Coste:
    int cuantosEquipos(const Jugador& jugador) const {
        //Si no existe el jugador, no hay equipos
        if (!jugadores.count(jugador)) return 0;

        //Si existe, dice el tamanio de su historial de equipos
        return jugadores.at(jugador).historial.size();
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
