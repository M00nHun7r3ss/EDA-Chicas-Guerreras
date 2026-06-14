
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
int resolver(vector<int> const& v) {

    int ini = 0;
    int fin = v.size() - 1;

    //Caso base, un elemento. es el ultimo valor válido 
    int res = v[0]; 

    //Recorremos
    while (ini <= fin) {

        //Mitad
        int mid = (ini + fin) / 2;

        //comprobamos si en mid el vector sigue la regla de consecutividad
        // busqueda en derecha
        if (v[mid] == v[0] + mid) {

            // si esto se cumple, significa que hasta mid la serie es correcta, y seguimos probando por la derecha para ver
            //si se sigue cumpliando
            res = v[mid];   
            ini = mid + 1;  
        }
        //Busqueda en izquierda
        else {
            //Nos hemos pasado la serie asi que retrocedemos, descartando la derecha
            fin = mid - 1;  
        }
    }

    return res;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;

    vector<int> v(n);

    for (int i = 0; i < n; i++)
        cin >> v[i];

    int sol = resolver(v);

    cout << sol << "\n";
}

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
    system("PAUSE");
#endif

    return 0;
}