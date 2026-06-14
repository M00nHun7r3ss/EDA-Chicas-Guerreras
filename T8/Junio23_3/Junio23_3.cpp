#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <map>
#include <set>
#include <queue>

using namespace std;


class Fecha {
    int _dia, _mes, _anio;

public:
    Fecha(int d = 0, int m = 0, int a = 0) : _dia(d), _mes(m), _anio(a) {}
    int dia() const { return _dia; }
    int mes() const { return _mes; }
    int anio() const { return _anio; }
    bool operator<(Fecha const& other) const {
        return _anio < other._anio ||
            (_anio == other._anio && _mes < other._mes) ||
            (_anio == other._anio && _mes == other._mes && _dia < other._dia);
    }
};

inline std::istream& operator>>(std::istream& entrada, Fecha& h) {
    int d, m, a; char c;
    std::cin >> d >> c >> m >> c >> a;
    h = Fecha(d, m, a);
    return entrada;
}

inline std::ostream& operator<<(std::ostream& salida, Fecha const& f) {
    salida << std::setfill('0') << std::setw(2) << f.dia() << '/';
    salida << std::setfill('0') << std::setw(2) << f.mes() << '/';
    salida << std::setfill('0') << std::setw(2) << f.anio();
    return salida;
}

using Codigo = string;
using Cliente = string;

class Tienda {
private:

    map<Codigo, multiset<Fecha>> almacen;
    map<Codigo, queue<Cliente>> espera;

public:
    vector<Cliente> adquirir(Codigo const& cod, Fecha const& f, int cant) {

        //Los que ya estan servidos
        vector<Cliente> servidos;

        // primero atendemos clientes en espera
        while (cant > 0 && !espera[cod].empty()) {
            servidos.push_back(espera[cod].front());
            espera[cod].pop();
            cant--;
        }

        // lo que sobra lo metemos al almacen
        for (int i = 0; i < cant; ++i) {
            almacen[cod].insert(f);
        }

        return servidos;
    }

    pair<bool, Fecha> vender(Codigo const& cod, Cliente const& cli) {
        // si hay stock
        if (!almacen[cod].empty()) {

            // coger la fecha minima
            auto it = almacen[cod].begin();
            Fecha f = *it;

            // eliminarla
            almacen[cod].erase(it);

            return { true, f };
        }

        // si no hay stock, cliente pasa a espera
        espera[cod].push(cli);
        return { false, Fecha() };
    }

    int cuantos(Codigo const& cod) const {
        //si no hay en el almacen
        if (!almacen.count(cod)) return 0;

        return almacen.at(cod).size();
    }

    bool hay_esperando(Codigo const& cod) const {
        //Si ya estan atendidos
        if (!espera.count(cod)) return false;

        return !espera.at(cod).empty();
    }
};

bool resuelveCaso() {
    std::string operacion, cod, cli;
    Fecha f;
    int cant;
    std::cin >> operacion;
    if (!std::cin)
        return false;

    Tienda tienda;

    while (operacion != "FIN") {
        if (operacion == "adquirir") {
            cin >> cod >> f >> cant;
            vector<Cliente> clientes = tienda.adquirir(cod, f, cant);
            cout << "PRODUCTO ADQUIRIDO";
            for (auto c : clientes)
                cout << ' ' << c;
            cout << '\n';
        }
        else if (operacion == "vender") {
            cin >> cod >> cli;
            pair<bool, Fecha> venta = tienda.vender(cod, cli);
            if (venta.first) {
                cout << "VENDIDO " << venta.second << '\n';
            }
            else
                cout << "EN ESPERA\n";
        }
        else if (operacion == "cuantos") {
            cin >> cod;
            cout << tienda.cuantos(cod) << '\n';
        }
        else if (operacion == "hay_esperando") {
            cin >> cod;
            if (tienda.hay_esperando(cod))
                cout << "SI\n";
            else
                cout << "NO\n";
        }

        std::cin >> operacion;
    }
    std::cout << "---\n";
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