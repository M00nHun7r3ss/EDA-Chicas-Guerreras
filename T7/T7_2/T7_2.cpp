#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
using namespace std;

using Diccionario = map<string, int>;

void leerDiccionario(Diccionario& diccionario) {
    char c;
    string clave;
    int valor;
    cin.get(c);
    while (c != '\n') {
        cin.unget();
        cin >> clave >> valor;

        // guardamos en el map
        diccionario[clave] = valor;

        cin.get(c);
    }
}

void resuelveCaso() {
    Diccionario antiguo;
    Diccionario nuevo;
    leerDiccionario(antiguo);
    leerDiccionario(nuevo);

    //soluciones a devolver
    set<string> anadidas;
    set<string> eliminadas;
    set<string> modificadas;

    // recorrer diccionario nuevo
    for (auto const& par : nuevo) {

        auto it = antiguo.find(par.first);

        //Llegamos al final
        if (it == antiguo.end()) {
            // no estaba antes, aniadida
            anadidas.insert(par.first);
        }
        //Lo encotramos
        else if (it->second != par.second) {
            // estaba pero valor distinto, modificada
            modificadas.insert(par.first);
        }
    }

    // recorrer diccionario antiguo
    for (auto const& par : antiguo) {

        //LLegamos al final
        if (nuevo.find(par.first) == nuevo.end()) {
            // ya no esta, eliminada
            eliminadas.insert(par.first);
        }
    }

    // imprimir resultado
    if (anadidas.empty() && eliminadas.empty() && modificadas.empty()) {
        cout << "Sin cambios\n";
    }
    else {
        if (!anadidas.empty()) {
            cout << "+";
            for (auto const& s : anadidas) cout << " " << s;
            cout << "\n";
        }

        if (!eliminadas.empty()) {
            cout << "-";
            for (auto const& s : eliminadas) cout << " " << s;
            cout << "\n";
        }

        if (!modificadas.empty()) {
            cout << "*";
            for (auto const& s : modificadas) cout << " " << s;
            cout << "\n";
        }
    }

    cout << "---\n";
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos; char c;
    std::cin >> numCasos;
    cin.get(c);
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
