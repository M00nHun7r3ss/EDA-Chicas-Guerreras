/*
Tupla solución: sol[k] = area a la que va el voluntario k

Marcadores:
vector<int> cargaArea(m)  // cuanto llevamos limpiado en cada area
int kilosAct              // total acumulado
int areasCompletas        // cuantas areas ya estan limpias
int mejorSol

Ejemplo de aplicación de poda por estimación:

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

template <class T>
ostream& operator<<(ostream& out, vector<T> const& v) {
    for (auto& e : v) out << e << " ";
    return out;
}


// función que resuelve el problema
void resolver(vector<int>& sol, int k, int n, int m, int l,
    vector<int>& kilosPorArea,
    vector<vector<int>> const& kilosPorVol,
    vector<int>& cargaArea,   // kilos acumulados en cada area
    int kilosAct,             // suma total recogida hasta ahora
    int areasCompletas,       // número de areas ya completamente limpias
    int& mejorSol,            // mejor solucion encontrada
    vector<int>& mejorSolVec)
{
    // Caso base: hemos asignado todos los voluntarios
    if (k == n) {
        if (areasCompletas >= l) {
            if (kilosAct > mejorSol) {
                mejorSol = kilosAct;
                mejorSolVec = sol;
            }
        }
        return;
    }

    //Poda por estimacion 
    //Suponemos que aunque cada voluntario va a su mejor area
    int posibleMax = kilosAct;

    for (int i = k; i < n; i++) {
        int mejor = 0;
        for (int a = 0; a < m; a++) {
            mejor = max(mejor, kilosPorVol[i][a]);
        }
        posibleMax += mejor;
    }

    // Si ni asi lo mejora, podamos
    if (posibleMax <= mejorSol) return;

    //Probamos a asignar voluntario k a cada area posible para ver si nos cuadra
    for (int i = 0; i < m; i++) {

        sol[k] = i;

        // Guardamos el estado previo para poder deshacer
        int antesCarga = cargaArea[i];
        // Comprobamos si el area ya estaba completa antes
        bool estabaCompleta = (antesCarga >= kilosPorArea[i]);

        // El lodo real que ya estaba limpio en esta area antes de meter al voluntario k
        int lodoAntes = min(kilosPorArea[i], antesCarga);

        // Actualizamos
        cargaArea[i] += kilosPorVol[k][i];

        // El lodo real que queda limpio tras meter al voluntario k
        int lodoDespues = min(kilosPorArea[i], cargaArea[i]);

        // El incremento REAL de lodo retirado es la diferencia
        int incrementoReal = lodoDespues - lodoAntes;
        kilosAct += incrementoReal;

        // comprobamos si ahora el area se ha completado
        bool ahoraCompleta = (cargaArea[i] >= kilosPorArea[i]);

        // Si justo se completa en este paso, incrementamos contador
        if (!estabaCompleta && ahoraCompleta)
            areasCompletas++;

        // Recursividad
        resolver(sol, k + 1, n, m, l, kilosPorArea,
            kilosPorVol, cargaArea, kilosAct,
            areasCompletas, mejorSol, mejorSolVec);

        // Si hemos incrementado areas completas, lo revertimos
        if (!estabaCompleta && ahoraCompleta)
            areasCompletas--;

        // Restauramos estado anterior
        kilosAct -= incrementoReal;
        cargaArea[i] = antesCarga;
    }

}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> kilosPorArea(m);
    for (int i = 0; i < m; ++i) {
        cin >> kilosPorArea[i];
    }
    vector<vector<int>> kilosPorVoluntario(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> kilosPorVoluntario[i][j];

    int k = 0;
    vector<int> sol(n);
    vector<int> mejorSolVec(n);
    vector<int> cargaArea(m, 0);

    int mejorSol = -1;

    resolver(sol, 0, n, m, l, kilosPorArea,
        kilosPorVoluntario, cargaArea,
        0, 0, mejorSol, mejorSolVec);

    if (mejorSol == -1) cout << "IMPOSIBLE\n";
    else cout << mejorSol << "\n";

    //Tupla solucion
    //for (int i = 0; i < n; i++) {
    //    cout << mejorSolVec[i] << " ";
    //}
    //cout << "\n";
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
