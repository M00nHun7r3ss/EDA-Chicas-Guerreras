// Carmen Gómez Becerra
// EDA-GDV29
// Complejidad cuasi lineal O(n*log(n)): esto es asi por ordenar auxEDA y auxTPV con el metodo std::sort

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// función que resuelve el problema
void comparaListados(vector<string> const& eda, vector<string> const& tpv,
    vector<string>& comunes, vector<string>& soloEda, vector<string>& soloTpv) {

    // hay que hacer esto porque eda y tpv son const, y por tanto no podemos hacerles sort()
    vector<string> auxEDA = eda;
    vector<string> auxTPV = tpv; 

    // si no es lista ordenada, ordenar vectores de menor a mayor con el metodo sort.
    sort(auxEDA.begin(), auxEDA.end());
    sort(auxTPV.begin(), auxTPV.end());

    // ----- DE AQUI PA ABAJO IGUAL QUE TEMA1-6 -----

    // inicialmente ambos indices empiezan en cero.
    int i = 0;
    int j = 0;

    while (i < auxEDA.size() && j < auxTPV.size()) { // hasta que no lleguen al final ambas listas no se termina.

        // AMBOS : aniadimos al comun y avanzamos ambos.
        if (auxEDA[i] == auxTPV[j]) {
            comunes.push_back(auxEDA[i]); // valdria en este caso tanto eda como tpv
            i++;
            j++;
        }
        // EDA && !TPV : si la letra de eda esta antes alfabeticamente que la de tpv, mete el numero en soloEDA y avanza eda.
        else if (auxEDA[i] < auxTPV[j]) {
            soloEda.push_back(auxEDA[i]);
            i++;

        }
        // TPV && !EDA : lo mismo de antes pero con tpv.
        else if (auxTPV[j] < auxEDA[i]) {
            soloTpv.push_back(auxTPV[j]);
            j++;
        }
    }

    // si hay un vector menor, el bucle acabara con las i, j del ultimo del menor, por tanto hacemos esto para terminar:
    while (i < auxEDA.size()) {
        soloEda.push_back(auxEDA[i]);
        i++;
    }

    while (j < auxTPV.size())
    {
        soloTpv.push_back(auxTPV[j]);
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
