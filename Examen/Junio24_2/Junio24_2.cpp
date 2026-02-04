
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;


// función que resuelve el problema y justificación del coste
bool backtracking(int k, int suma, int M, const vector<int>& v, const vector<int>& resto, vector<char>& sol)
{
    // Caso base
    // Ya hemos usado todos los numeros
    if (k == v.size()) {
        if (suma == M) {
            //// TUPLA SOLUCION
            //
            //cout << "Solucion: ";
            //cout << v[0];
            //for (int i = 1; i < v.size(); ++i) {
            //    cout << " " << sol[i] << " " << v[i];
            //}
            //cout << endl;
            //
            return true;
        }
        return false;
    }

    // PODA
    // Si a lo actual le sumamos o le restamos lo que queda y no da M,
    // ignoramos la rama y seguimos con el resto
    if (suma - resto[k] > M || suma + resto[k] < M)
        return false;

    // Probamos sumando v[k]
    sol[k] = '+';
    if (backtracking(k + 1, suma + v[k], M, v, resto, sol))
    {
        return true;
    }

    // Si hemos llegadp aqui es que con la suma no es
    // Probamos restando v[k]
    sol[k] = '-';
    if (backtracking(k + 1, suma - v[k], M, v, resto, sol))
    {
        return true;
    }

    // Si hemos llegado aqui es que ninguna operacion funciona
    return false;
}

void resuelveCaso() {
    int M; //Resultado buscado
    int n = 0; //Tamanio vector
    cin >> M >> n;
    vector<int> v(n);
    for (int& e : v) cin >> e;

    //La tupla
    vector<char> sol(n);

    //Cosas para la poda
    vector<int> resto(n + 1);
    resto[n] = 0;
    //Calculamos la suma de lo que queda en la rama
    for (int i = n - 1; i >= 0; --i)
        resto[i] = resto[i + 1] + v[i];

    // llamada a función que resuelve el problema
    bool sePuede = false;
    if (n == 0) // caso 4, vector vacio
        sePuede = (M == 0);
    else
        sePuede = backtracking(1, v[0], M, v, resto, sol);

    // salida de datos
    if (sePuede) cout << "SI\n";
    else cout << "NO\n";

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