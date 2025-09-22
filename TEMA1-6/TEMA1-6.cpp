// Carmen Gómez Becerra
// EDA-GDV29
// Complejidad lineal. Siendo "n" el eda.size() y "m" el tpv.size() -> O(n + m).
// El tiempo de ejecucion es proporcional al numero de entradas, se recorre una vez el bucle.

// Cuestion: si no estuvieran ordenados, el menor orden de complejidad seria cuasi lineal O(n*log(n)).
// Esto seria asi porque habria que ordenarlo antes de hacer las busquedas correspondientes.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// función que resuelve el problema
void comparaListados(vector<string> const& eda, vector<string> const& tpv,
    vector<string>& comunes, vector<string>& soloEda, vector<string>& soloTpv) {

    // inicialmente ambos indices empiezan en cero.
    int i = 0;
    int j = 0;

    while (i < eda.size() && j < tpv.size()){ // hasta que no lleguen al final ambas listas no se termina.

        // AMBOS : aniadimos al comun y avanzamos ambos.
	    if (eda[i] == tpv[j]){ 
            comunes.push_back(eda[i]); // valdria en este caso tanto eda como tpv
            i++;
            j++;
	    }
        // EDA && !TPV : si la letra de eda esta antes alfabeticamente que la de tpv, mete el numero en soloEDA y avanza eda.
        else if (eda[i] < tpv[j]){ 
            soloEda.push_back(eda[i]);
            i++;

        }
        // TPV && !EDA : lo mismo de antes pero con tpv.
        else if (tpv[j] < eda[i]){
            soloTpv.push_back(tpv[j]);
            j++;
        }
    }

    // si hay un vector menor, el bucle acabara con las i, j del ultimo del menor, por tanto hacemos esto para terminar:
    while (i < eda.size()) {
        soloEda.push_back(eda[i]);
        i++;
    }

    while (j < tpv.size())
    {
        soloTpv.push_back(tpv[j]);
        j++;
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<string> eda(n);
    vector<string> comunes;
    vector<string> soloEda;
    vector<string> soloTpv;
    for (string& e : eda) cin >> e;
    cin >> n;
    vector<string> tpv(n);
    for (string& e : tpv) cin >> e;
    comparaListados(eda, tpv, comunes, soloEda, soloTpv);
    for (string& e : comunes) cout << e << " ";
    cout << endl;
    for (string& e : soloEda) cout << e << " ";
    cout << endl;
    for (string& e : soloTpv) cout << e << " ";
    cout << endl;
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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
