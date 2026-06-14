#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <list>
#include <stdexcept>
using namespace std;

class carnet_puntos {

private:

    map<string, int> puntos; // dni y sus puntos
    vector<list<string>> porPuntos; // lista dnis con x puntos
    map<string, list<string>::iterator> pos; // iterador de cada dni

public:
    //16 porque necesitamos huecos de 0 a 15 inclusive
    carnet_puntos() : porPuntos(16) {}

    void nuevo(const string& dni) {
        //Si duplicado lanza error
        if (puntos.count(dni))
            throw domain_error("Conductor duplicado");

        //Si no, da 15 puntos iniciales y le pasa el dni
        puntos[dni] = 15;
        porPuntos[15].push_front(dni);

        //y lo pone al principio, como primero aniadido
        pos[dni] = porPuntos[15].begin();
    }

    void quitar(const string& dni, int p) {
        //Si no existe carnet para dni lanza error
        if (!puntos.count(dni))
            throw domain_error("Conductor inexistente");

        //coge los puntos del dni
        int actual = puntos[dni];
        //determinamos el maximo numero de puntos que le podemos dejar
        int nuevo = max(0, actual - p);

        // quitar de lista actual
        porPuntos[actual].erase(pos[dni]);

        // anadir a nueva (nuevos puntos)
        porPuntos[nuevo].push_front(dni);
        pos[dni] = porPuntos[nuevo].begin();

        puntos[dni] = nuevo;
    }

    void recuperar(const string& dni, int p) {
        //Si no existe carnet para dni lanza error
        if (!puntos.count(dni))
            throw domain_error("Conductor inexistente");

        //coge los puntos del dni
        int actual = puntos[dni];
        //determinamos el minimo numero de puntos que le podemos dejar
        int nuevo = min(15, actual + p);

        // quitar de lista actual
        porPuntos[actual].erase(pos[dni]);

        // anadir a nueva (nuevos puntos)
        porPuntos[nuevo].push_front(dni);
        pos[dni] = porPuntos[nuevo].begin();

        puntos[dni] = nuevo;
    }

    int consultar(const string& dni) const {
        //Si no existe carnet para dni lanza error
        if (!puntos.count(dni))
            throw domain_error("Conductor inexistente");

        return puntos.at(dni);
    }

    int cuantos_con_puntos(int p) const {
        //entre los limites
        if (p < 0 || p > 15)
            throw domain_error("Puntos no validos");

        //sacamos de la lista
        return porPuntos[p].size();
    }

    const list<string>& lista_por_puntos(int p) const {
        //entre los limites
        if (p < 0 || p > 15)
            throw domain_error("Puntos no validos");

        //la lista en si de dnis
        return porPuntos[p];
    }
};

bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;

    carnet_puntos dgt;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                cin >> dni;
                dgt.nuevo(dni);
            }
            else if (orden == "quitar") {
                cin >> dni >> punt;
                dgt.quitar(dni, punt);
            }
            else if (orden == "recuperar") {
                cin >> dni >> punt;
                dgt.recuperar(dni, punt);
            }
            else if (orden == "consultar") {
                cin >> dni;
                punt = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << punt << '\n';
            }
            else if (orden == "cuantos_con_puntos") {
                cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            }
            else if (orden == "lista_por_puntos") {
                cin >> punt;
                auto const& lista = dgt.lista_por_puntos(punt);
                cout << "Tienen " << punt << " puntos:";
                for (auto const& dni : lista)
                    cout << ' ' << dni;
                cout << '\n';
            }
            else
                cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}

int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("pause");
#endif
    return 0;
}
