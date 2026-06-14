#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
using namespace std;

using TablaRefs = map<string, list<int>>;

// pasa una palabra a minusculas
string aMinusculas(string p) {
    for (char& c : p) c = tolower(c);
    return p;
}

void referencias(int numLineas, TablaRefs& refs) {
    string palabra;
    char c;
    for (int numLinea = 1; numLinea <= numLineas; numLinea++) {
        cin.get(c);
        // mientras no lleguemos al final de la línea
        while (c != '\n') {
            cin.unget(); // Se vuelve a dejar c en cin (por si era la 1ª letra de la linea)

            // leemos una palabra completa
            cin >> palabra;

            // pasamos a minusculas
            palabra = aMinusculas(palabra);

            // solo palabras de mas de 2 letras
            if (palabra.length() > 2) {

                // obtenemos la lista de lineas asociada a esa palabra
                list<int>& l = refs[palabra];

                // evitar repetir linea
                if (l.empty() || l.back() != numLinea) {
                    // aniadimos la linea actual
                    l.push_back(numLinea);
                }
            }
            //Leemos siguiente caracter
            cin.get(c);
        }
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    char c;
    cin >> n;
    cin.get(c); // Me salto el \n de detrás del N
    if (n == 0)
        return false;

    TablaRefs refs;
    referencias(n, refs);

    // escribir sol
    for (auto const& par : refs) {

        cout << par.first;

        for (int linea : par.second) {
            cout << " " << linea;
        }

        cout << "\n";
    }

    cout << "---\n";

    return true;

}

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