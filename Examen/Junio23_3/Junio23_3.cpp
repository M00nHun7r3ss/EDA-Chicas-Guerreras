
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <map>
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
    struct Producto {
        map<Fecha, int> stock;      // unidades en fecha
        queue<Cliente> esperando;  // clientes en espera de dicho productor
    };

    unordered_map<Codigo, Producto> productos;

public:
    vector<Cliente> adquirir(Codigo const& cod, Fecha const& f, int cant) {

        //Clientes ya atendidos 
        vector<Cliente> atendidos;
        //Producto deseado
        Producto& p = productos[cod];

        //Si hay gente esperando y hay producto
        while (!p.esperando.empty() && cant > 0) {
            //Les atendemos
            atendidos.push_back(p.esperando.front());
            //Dejan de esperar
            p.esperando.pop();
            //Reducimos el stock
            --cant;
        }

        //Se guarda lo que quede en el almacen
        if (cant > 0) p.stock[f] += cant;

        //Devuelve los clientes ya atendidos
        return atendidos;
    }

    pair<bool, Fecha> vender(Codigo const& cod, Cliente const& cli) {

        //Producto deseado
        Producto& p = productos[cod];

        //Si hay en el almacen
        if (!p.stock.empty()) {
            //Mira el stock del menor dia
            auto it = p.stock.begin();
            //La fecha de dicho dia
            Fecha f = it->first;
            //Reduce el stock
            --(it->second);
            //Si no queda, borra la entrada entera de la fecha
            if (it->second == 0) p.stock.erase(it);
            //Se ha vendido en tal fecha
            return { true, f };
        }
        else {
            //Si no hay stock, ponemos el cliente en espera
            p.esperando.push(cli);
            //No se ha vendido nada. A fecha indeterminada, porque no ha habido venta
            return { false, Fecha() }; 
        }
    }

    int cuantos(Codigo const& cod) const {
        //Buscamos le producto determinado
        auto it = productos.find(cod);
        //Si no existe, devueve 0
        if (it == productos.end()) return 0;

        //Si ha llegado hasta aqui, revisa el stock en cada fecha y lo va sumando
        int total = 0;
        for (const pair<const Fecha, int>& par : it->second.stock) total += par.second;
        return total;
    }

    bool hay_esperando(Codigo const& cod) const {
        //Buscamos le producto determinado
        auto it = productos.find(cod);
        //Si no existe, no puede haber nadie esperando
        if (it == productos.end()) return false;

        //Si ha llegado hasta aqui, revisa si hay alguien esperando
        return !it->second.esperando.empty();
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
    std::ifstream in("datos.txt");
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