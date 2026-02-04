
/*
Tupla solución:
soluc[k] = area asignada al voluntario k, -1 si no se asigna

Marcadores:
recogidoPorArea[i]  // kilos acumulados en el area i
kilosTotales        // total retirado
areasLimpias        // nº de areas ya limpias

Ejemplo de aplicación de poda por estimación:
maxRestante[k]      // Maximo lodo que podrian retirar los voluntarios k..n-1

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
void resolver(vector<int>& soluc, //Tupla solucion
    int k, 
    int n, int m, int l, 
    vector<int>& kilosPorArea, 
    vector<vector<int>> const& kilosPorVoluntario, 
    vector<int>& recogidoPorArea, 
    int kilosTotales,      // kilos totales de todas las areas
    int areasLimpias,      // areas ya limpias
    int& mejor,            // mejor solución encontrada
    vector<int> const& maxRestante) // poda 
{
    //PODA
	// Si aunque asignemos todos los voluntarios restantes
    // no podemos superar la mejor solución conocida, cortamos
    if (kilosTotales + maxRestante[k] <= mejor) return;

    //Caso base
    // Ya hemos decidido para todos los voluntarios
    if (k == n) {
        // Solo es solución valida si limpiamos al menos l áreas
        if (areasLimpias >= l) {
            // Actualizamos el máximo de kilos retirados
            mejor = max(mejor, kilosTotales);
        }
        return;
    }

    //De primeras no asignamos el voluntario a ninguna area
    soluc[k] = -1;

    resolver(soluc, k + 1, n, m, l,kilosPorArea, kilosPorVoluntario,recogidoPorArea, kilosTotales, areasLimpias, mejor, maxRestante);

    //En caso de asignarlo
    for (int area = 0; area < m; ++area) {

        // Guardamos el estado anterior (para deshacer luego)
        int antes = recogidoPorArea[area];
        bool estabaLimpia = antes >= kilosPorArea[area];

        // Aniadimos lo que aporta este voluntario
        // lo que puede aportar realmente para no exceder la necesidad
        int aporte = min(kilosPorVoluntario[k][area], kilosPorArea[area] - recogidoPorArea[area]);
        recogidoPorArea[area] += aporte;

        bool ahoraLimpia = recogidoPorArea[area] >= kilosPorArea[area];

        // Si el area pasa de sucia a limpia, sumamos 1
        int nuevasLimpias = areasLimpias;
        if (!estabaLimpia && ahoraLimpia) nuevasLimpias++;

        //Asignamos dicha area
        soluc[k] = area;

        resolver(soluc, k + 1, n, m, l, kilosPorArea, kilosPorVoluntario, recogidoPorArea,
            kilosTotales + aporte, nuevasLimpias, mejor, maxRestante);

        // Regresamos
        recogidoPorArea[area] = antes;
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

    vector<int> soluc(n);
    vector<int> recogidoPorArea(m, 0);
    int k = 0;
    int mejor = -1;

    //Poda
    //Calculamos el maximo de lodo que podrian recoger los voluntarios de k hasta n-1 si se
    //asignan en el area mas adecuada
    vector<int> maxRestante(n + 1, 0);
    //Recorremos los voluntarios desde el ultimo hasta el primero porque queremos
    //calcular la suma acumulada de los maximos posibles a partir de cada voluntario.
    for (int i = n - 1; i >= 0; --i) {
        // Encontramos la mayor cantidad de lodo que puede retirar el voluntario i
        // en cualquiera de las areas
        int mejorVol = 0;
        for (int a = 0; a < m; ++a)
            mejorVol = max(mejorVol, kilosPorVoluntario[i][a]);

        //LO que aporta este y los siguientes
        maxRestante[i] = maxRestante[i + 1] + mejorVol;
    }

    resolver(soluc, k, n, m, l, kilosPorArea, kilosPorVoluntario, recogidoPorArea, 0, 0, mejor, maxRestante);

    if (mejor == -1) cout << "IMPOSIBLE\n";
    else cout << mejor << "\n";
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
