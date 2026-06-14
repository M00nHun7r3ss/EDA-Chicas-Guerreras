/*
Indica y explica el formato de la tupla solución:

    sol = {s1, s2, s3...} donde cada s es +1 o -1 según si se suma o se resta.

¿Cuándo se da el caso peor?

    Ocurre cuando el resultado M no se puede obtener de ninguna manera, 
    o cuando la unica combinacion posible está en la última rama explorada del árbol. 
    En estas situaciones, el algoritmo tiene que exlporar todo el árbol entero.

Indica cuántas llamadas (en función de n) genera el algoritmo en dicho caso.

    Genera un total de 2^(n+1) - 1 llamadas. El coste en tiempo es O(2^n).
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (auto e : v) out << e << " ";
    return out;
}

// función que resuelve el problema y justificación del coste
// Devuelve true si encuentra una solucion
bool resolver(int k, 
    int n, int M, const vector<int>& v, 
    const vector<int>& sumaRestante,
    int sumaActual, 
    vector<char>& sol)
{
    // Caso base, todos los numeros han sido procesados
    if (k == n) {
        return (sumaActual == M);
    }

    // Poda por estimacion:
    // Si la distancia absoluta que nos falta para llegar a M es mayor que todo lo que queda 
    // por sumar en el vector, es imposible llegar, asi que podamos
    if (abs(M - sumaActual) > sumaRestante[k]) {
        return false;
    }

    // Probamos a sunar el elemento v[k]
    // Guardamos el operador en la tupla (v[0] no usa operador)
    sol[k - 1] = '+'; 
    if (resolver(k + 1, n, M, v, sumaRestante, sumaActual + v[k], sol)) {
        return true;
    }

    // Probamos a restar el elemento v[k]
    sol[k - 1] = '-';
    if (resolver(k + 1, n, M, v, sumaRestante, sumaActual - v[k], sol)) {
        return true;
    }

    // Si ninguna de las dos opciones funciona, esta subrama no tiene solucion
    return false;
}


void resuelveCaso() {
    int n = 0, M;
    cin >> M >> n;
    vector<int> v(n);
    for (int& e : v)
        cin >> e;

    // Si el vector esta vacio, evaluamos si M es 0
    if (n == 0) {
        if (M == 0) cout << "SI\n";
        else cout << "NO\n";
        return;
    }

    // Precalculamos las sumas acumuladas desde el final (para la poda)
    // sumaRestante[k] = v[k] + v[k+1] + ... + v[n-1]
    vector<int> sumaRestante(n);
    sumaRestante[n - 1] = v[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        sumaRestante[i] = v[i] + sumaRestante[i + 1];
    }

    // Tupla solucion
    vector<char> sol(n > 1 ? n - 1 : 0);

    // Empezamos en k = 1
    bool exito = resolver(1, n, M, v, sumaRestante, v[0], sol);

    if (exito) {
        cout << "SI\n";

        /*
        cout << "Tupla solucion: " << v[0] << " ";
        for(size_t i = 0; i < sol.size(); ++i) {
            cout << sol[i] << " " << v[i+1] << " ";
        }
        cout << "= " << M << "\n\n";
        */

    }
    else {
        cout << "NO\n";
    }
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