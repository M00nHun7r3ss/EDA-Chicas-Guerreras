
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

// info de cada problema de un equipo
struct InfoProblema {
    int intentos = 0;     // intentos incorrectos
    bool resuelto = false;
};

// info total de un equipo
struct InfoEquipo {
    int resueltos = 0;
    int tiempo = 0;
    map<string, InfoProblema> problemas;
};

// para ordenar la salida
struct Resultado {
    string nombre;
    int resueltos;
    int tiempo;
};

bool comparacion(Resultado const& a, Resultado const& b) {
    if (a.resueltos != b.resueltos)
        return a.resueltos > b.resueltos; // mas resueltos mejor
    if (a.tiempo != b.tiempo)
        return a.tiempo < b.tiempo; // menos tiempo mejor
    return a.nombre < b.nombre; // orden alfabetico
}

void procesaEnvios(vector<Resultado>& resultados) {

    map<string, InfoEquipo> equipos;
    string equipo, problema, veredicto;
    int minuto;

    cin >> equipo;
    while (equipo != "FIN") {
        cin >> problema >> minuto >> veredicto;

        InfoEquipo& eq = equipos[equipo];
        InfoProblema& pr = eq.problemas[problema];

        // si ya esta resuelto, ignoramos
        if (pr.resuelto) {
            cin >> equipo;
            continue;
        }

        if (veredicto == "AC") {
            // problema resuelto
            pr.resuelto = true;
            eq.resueltos++;

            // tiempo = minuto + penalizacion
            eq.tiempo += minuto + pr.intentos * 20;
        }
        else {
            // intento incorrecto
            pr.intentos++;
        }
        
        cin >> equipo;
    }

    // construir vector de resultados
    for (auto const& par : equipos) {
        Resultado r;
        r.nombre = par.first;
        r.resueltos = par.second.resueltos;
        r.tiempo = par.second.tiempo;
        resultados.push_back(r);
    }

    // ordenar clasificacion
    sort(resultados.begin(), resultados.end(), comparacion);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    vector<Resultado> resultados;

    procesaEnvios(resultados);

    // Se imprime la salida
    for (auto const& r : resultados) {
        cout << r.nombre << " " << r.resueltos << " " << r.tiempo << "\n";
    }
    
    cout << "---\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input.txt");
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