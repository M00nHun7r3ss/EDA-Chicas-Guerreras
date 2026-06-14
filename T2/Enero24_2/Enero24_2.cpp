#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

//Define solucion: si encontrado o no, donde, o entre que limites
struct Solution {
    bool encontrado;
    int pos;
    int l, r;
};

// función que resuelve el problema
//Busqueda binaria entre inicio y fin
//Complejidad de tiempo: O(log n), por la busqueda binaria
//Complejidad de espacio: O(1), ya que no se emplean estructuras auxiliares.
Solution resolver(vector<int> const& A, vector<int> const& B) {

    //De inicio hasta ultimo elemento
    int ini = 0, fin = A.size() - 1;

    //Vamos a avanzar en fin, asi que, hasta que inicio no sobrepase fin, seguimos
    while (ini <= fin) {

        //Buscamos medio
        int mid = (ini + fin) / 2;

        //Si coincide, perfecto
        if (A[mid] == B[mid]) {
            return { true, mid, 0, 0 };
        }
        //Si ya A es todavia menor, estara en lado derecho
        else if (A[mid] < B[mid]) {
            ini = mid + 1;
        }
        //Si B es ya mayor, estara en el lado izquierdo
        else {
            fin = mid - 1;
        }
    }

    // No encontrado
    return { false, -1, fin, ini };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    std::cin >> n;

    //Centinela acaba
    if (n == 0) return false;

    //2 vectores
    std::vector<int> A(n), B(n);

    //Lee los vectores
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];

    Solution sol = resolver(A, B);

    //Si encontrado decimos donde
    if (sol.encontrado) {
        cout << "SI " << sol.pos << endl;
    }
    //Si no, decimos entre que y que
    else {
        cout << "NO " << sol.l << " " << sol.r << endl;
    }

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
    system("PAUSE");
#endif

    return 0;
}
