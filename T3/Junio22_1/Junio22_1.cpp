#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility> 
using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (auto e : v) out << e;
    return out;
}


// función que resuelve el problema
void resolver(int k, //Tarea actual que estamos asignando (va de 0 a n-1)
    int n, int a, int t, //n tareas totales, a alumnos totales, t tareas que puede realizar un alumno
    const vector<vector<int>>& preferencias, //gustos de los alumnos
    vector<int>& tareasPorAlumno, //restricciones por alumno
    int puntuacionActual, //suma acumulada actual
    int& mejorPuntuacion, //maximo global encontrado
    vector<pair<int, int>>& solActual, //tupla solucion
    vector<pair<int, int>>& mejorSolVec) 
{
    // Caso base: Asignamos 2 alumnos a n tareas
    if (k == n) {
        if (puntuacionActual > mejorPuntuacion) {
            mejorPuntuacion = puntuacionActual;
            mejorSolVec = solActual; 
        }
        return;
    }

    // Probamos todas las parejas posibles de alumnos (i, j) para la tarea k
    for (int i = 0; i < a; ++i) {
        for (int j = i + 1; j < a; ++j) {

            // Comprobamos si ambos alumnos pueden aceptar una tarea mas
            if (tareasPorAlumno[i] < t && tareasPorAlumno[j] < t) {

                // Asignamos la tarea k a los alumnos i y j
                // Registramos la pareja en la tupla 
                solActual[k] = { i, j }; 
                tareasPorAlumno[i]++;
                tareasPorAlumno[j]++;
                int puntosPareja = preferencias[i][k] + preferencias[j][k];

                // Pasamos a la siguiente tarea (k + 1)
                resolver(k + 1, n, a, t, preferencias, tareasPorAlumno,
                    puntuacionActual + puntosPareja, mejorPuntuacion, solActual, mejorSolVec);

                // Regresamos a los valores anteriores
                tareasPorAlumno[i]--;
                tareasPorAlumno[j]--;
            }
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, a, t;
    cin >> n >> a >> t;
    if (n == 0 && a == 0 && t == 0) return false;
    vector<vector<int>> preferencias(a, vector<int>(n));
    for (int i = 0; i < a; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> preferencias[i][j];
        }

    vector<int> tareasPorAlumno(a, 0);
    int mejorPuntuacion = -1;

    vector<pair<int, int>> solActual(n);
    vector<pair<int, int>> mejorSolVec(n);

    resolver(0, n, a, t, preferencias, tareasPorAlumno, 0, mejorPuntuacion, solActual, mejorSolVec);

    // Imprimir solucion
    cout << mejorPuntuacion << "\n";

    //Tupla solucion
    /*
    cout << "Asignacion optima (Tarea - Alumnos): ";
    for (int tarea = 0; tarea < n; ++tarea) {
        cout << "[" << tarea << ":(" << mejorSolVec[tarea].first
             << "," << mejorSolVec[tarea].second << ")] ";
    }
    cout << "\n\n";
    */

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
    //system("PAUSE");
#endif

    return 0;
}