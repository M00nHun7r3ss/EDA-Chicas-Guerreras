// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <fstream>
#include <cctype>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

/*
 Complejidad:
 Usare las siguientes variables para explicar la complejidad
 nAls (numero de alumnos)
 nDeps (numero de deportes)
 nAlsUnic (numero de alumnos unicos)

La complejidad seria en el peor caso O(nAls + nAlsUnic + nDeps * log nDeps)
Leer los alumnos tiene una complejidad O(nAls)
Revisar los alumnos validos (con una unica aparicion) tiene una complejidad O(nAlsUnic)
Ordenar los resultados tiene una complejidad O(nDeps * log nDeps)
Preparar el resultado tiene una complejidad O(nDeps)
 */

void resolver(string const& primerDeporte) {
    //Registro de deporte y alumno
    unordered_map<string, unordered_set<string>> deportesAlumnos;
    //Registro de apariciones de un alumno
    unordered_map<string, int> vecesAlumno;
    //Registro de numero de alumnos en cada deporte
    vector<pair<string, int>> resultado;

    //Deportes y alumnos
    //Complejidad O(1) por lectura
    string deporte = primerDeporte, alumno;

    //Si no ha llegado al final de la lista
	// Complejidad del while: O(n) siendo n el numero de alumnos
    while (deporte != "_FIN_") {
        //Todos los alumnos registrados en esta hoja
        unordered_set<string> alumnosHoja;

        // Leer alumnos de la hoja actual
        // (si la primera letra es minuscula y no hemos llegado al fin de la lista)
        //Obviara los duplicados en la misma hoja
        // Complejidad del while: O(n) siendo n el numero de alumnos
        while (cin >> alumno && !isupper(alumno[0]) && alumno != "_FIN_") {
            //Lo guarda en el set
            // Complejidad del insert: O(1) por unordered_map
            alumnosHoja.insert(alumno);
        }

        // Guardamos los alumnos en su deporte (todo el set)
        // Complejidad de la asignacion: O(n) siendo n el numero de deportes de la lista
        deportesAlumnos[deporte] = alumnosHoja;

        // Contamos las apariciones de los alumnos
        // Complejidad del for: O(n) siendo n el numero de alumnos
        for (const string& alumno : alumnosHoja) {
            vecesAlumno[alumno]++;
        }

        //Preparamos el siguiente deporte.
        //(Saldra del bucle si es fin o mayuscula)
        deporte = alumno;
    }

    // Vemos si los alumnos son validos
	// Complejidad del for: O(n) siendo n el numero de alumnos unicos por deporte
    for (pair<const string, unordered_set<string>>& p : deportesAlumnos) {
        //Contador
        int count = 0;
        //Miramos los alumnos, que son la segunda poarte del pair
        for (const string& a : p.second) {
            //Si solo tienen una aparicion, ese es el que nos vale
            if (vecesAlumno[a] == 1) count++;
        }
        //Lo guardamos bajo el resultado 
        resultado.push_back({ p.first, count });
    }

    // Ordenamos por numero de alumnas de mayor a menor y alfabeticamente
    // De principio a fin, comparamos dos a dos cada deporte y su numero de alumnos
	// Complejidad del sort: O(n log n) siendo n el numero de deportes de la lista
    sort(resultado.begin(), resultado.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
        });

    // Sacamos los resultados por consola (deporte y numero de alumnos)
    // Complejidad del for: O(n) siendo n el numero de deportes
    for (pair<string, int>& p : resultado) {
        cout << p.first << " " << p.second << "\n";
    }
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    //Leemos el deporte
    string primerDeporte;
    cin >> primerDeporte;
    if (!cin) return false;
    //Resolvemos para ese primer deporte
    resolver(primerDeporte);
    
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