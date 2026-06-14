#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <cassert>
#include <map>

using namespace std;
using Estado = string;
using Partido = string;

class ConteoVotos {

private:
    //Estado, numero de diputados, partido y votos de ese partido
    map<Estado, pair<int, map<Partido, int>>> datos;

public:

    void nuevo_estado(const Estado& nombre, int num_compromisarios) 
    {
        //si no hay estado, nada
        if (datos.count(nombre))
            throw domain_error("Estado ya existente");

        //Le pasamos al estado el numero de diputados
        datos[nombre] = { num_compromisarios, {} };
    }

    void sumar_votos(const Estado& estado, const Partido& partido, int num_votos) 
    {
        //si no hay estado, nada
        if (!datos.count(estado))
            throw domain_error("Estado no encontrado");

        //Sumamos en los votos del partido 
        datos[estado].second[partido] += num_votos;
    }

    Partido ganador_en(const Estado& estado) const 
    {
        //si no hay estado, nada
        if (!datos.count(estado))
            throw domain_error("Estado no encontrado");

        //Cogemos todos los votos totales del estado
        auto const& votos = datos.at(estado).second;

        Partido ganador;
        int maxV = -1;

        //Y vemos cada partida, para ver el mas votado
        for (auto const& p : votos) {
            if (p.second > maxV) {
                maxV = p.second;
                ganador = p.first;
            }
        }

        return ganador;
    }

    vector<pair<Partido, int>> resultados() const 
    {
        //Todos los votos de todos los partidos
        map<Partido, int> total; 

        for (auto const& e : datos) {

            //Los votantes y los votos
            int compromisarios = e.second.first;
            auto const& votos = e.second.second;

            // encontrar ganador del estado
            Partido ganador = ganador_en(e.first);

            // sumar diputados al ganador
            total[ganador] += compromisarios;
        }

        // pasar a vector
        vector<pair<Partido, int>> res;

        for (auto const& p : total) {
            res.push_back(p);
        }

        return res;
    }

};


bool resuelveCaso() {
    string comando;
    cin >> comando;
    if (!cin) return false;

    ConteoVotos elecciones;

    while (comando != "FIN") {
        try {
            if (comando == "nuevo_estado") {
                Estado estado;
                int num_compromisarios;
                cin >> estado >> num_compromisarios;
                elecciones.nuevo_estado(estado, num_compromisarios);
            }
            else if (comando == "sumar_votos") {
                Estado estado;
                Partido partido;
                int num_votos;
                cin >> estado >> partido >> num_votos;
                elecciones.sumar_votos(estado, partido, num_votos);
            }
            else if (comando == "ganador_en") {
                Estado estado;
                cin >> estado;
                Partido ganador = elecciones.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << ganador << "\n";
            }
            else if (comando == "resultados") {
                for (const auto& par : elecciones.resultados()) {
                    cout << par.first << " " << par.second << "\n";
                }
            }
        }
        catch (std::exception& e) {
            cout << e.what() << "\n";
        }
        cin >> comando;
    }

    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
