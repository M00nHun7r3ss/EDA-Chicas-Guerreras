/*
Marcadores:
contadorPorAlumno[j]  // n tareas del alumno j
sumaActual            // puntuacion acumulada
mejorSuma             // mejor puntuacion encontrada

Poda:
Para cada tarea, calculamos la mejor puntuacion posible. Si aunque sumemos
lo maximo posible no superamos la mejor solucion, cortamos.

Tupla Solucion:
Para cada tarea i se asignan los 2 alumnos correspondientes
solucActual[i] = {alumno1, alumno2}

 */

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (auto e : v) out << e;
    return out;
}


// función que resuelve el problema
void resolver(int tarea,                        //Tarea actual
    int n, int a, int t, 
    const vector<vector<int>>& preferencias,    //Preferencias del alumno
    vector<int>& contadorPorAlumno,             //Tareas asignadas a cada alumno
    int sumaActual,                             //Puntuacion acumulada
	int& mejorSuma,                             //Puntuacion maxima
    vector<int>& maxRestante,                   //Poda
    vector<pair<int, int>>& solucActual,        //Tupla solucion
    vector<pair<int, int>>& solucMejor)
{
    //Caso base. Todas las tareas han sido asignadas a los alumnos
    if (tarea == n)
    {
	    //Es la mejor forma de asignarlo?
        if (sumaActual > mejorSuma)
        {
            mejorSuma = sumaActual;
            solucMejor = solucActual;
        }
        return;
    }

    //Poda
    //Si sumanod el maximo de tareas restantes no mejor la solucion, no seguimos por ahi
    if (sumaActual + maxRestante[tarea] <= mejorSuma) return;

    //Probamos combinaciones de alumnos para asignar a las tareas
    for (int i = 0; i < a; i++)
    {
        //El alumno i no puede coger mas tareas
        if (contadorPorAlumno[i] >= t) continue;

        //Miramos a partir del siguiente de i para buscar un compi
        for (int j = i + 1; j < a; j++)
        {
            //El alumno j no puede coger mas tareas
            if (contadorPorAlumno[j] >= t) continue;

            //Eligen tarea
            contadorPorAlumno[i]++;
            contadorPorAlumno[j]++;

            solucActual[tarea] = { i, j };

            //Se actualiza la suma de puntaciones
            int sumaNueva = sumaActual + preferencias[i][tarea] + preferencias[j][tarea];

            //Recursividad
            resolver(tarea + 1, n, a, t, preferencias,
                contadorPorAlumno, sumaNueva,
                mejorSuma, maxRestante,
                solucActual, solucMejor);

            //Regresamos
            contadorPorAlumno[i]--;
            contadorPorAlumno[j]--;
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

    vector<int> contadorPorAlumno(a, 0);

    // Calculamos maxRestante para poda
    vector<int> maxRestante(n, 0);
    for (int i = 0; i < n; ++i) {
        vector<int> prefTarea;

        //Para cada tarea cogemos las 2 preferencias mas grandes
        for (int j = 0; j < a; ++j) prefTarea.push_back(preferencias[j][i]);
        sort(prefTarea.rbegin(), prefTarea.rend());
        maxRestante[i] = prefTarea[0] + prefTarea[1]; 
    }

    // Acumulamos desde el final
    for (int i = n - 2; i >= 0; --i)
        maxRestante[i] += maxRestante[i + 1];

    int mejorSuma = 0;
    vector<pair<int, int>> solucActual(n, { -1,-1 });
    vector<pair<int, int>> solucMejor(n, { -1,-1 });

    int tarea = 0;

    resolver(tarea, n, a, t, preferencias, contadorPorAlumno, 0,
        mejorSuma, maxRestante, solucActual, solucMejor);

    // Imprimimos la mejor suma
    cout << mejorSuma << "\n";

    // Imprimir tupla solucion
    /*
    for (int i = 0; i < n; ++i)
        cout << "Tarea " << i << ": alumnos " << solucMejor[i].first
             << " y " << solucMejor[i].second << "\n";
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