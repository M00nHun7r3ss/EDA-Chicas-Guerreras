
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

//Define solucion: parcialmente ordenado, minimo y maximo
struct Solution {
    bool ok;
    int minimo;
    int maximo;
};

// función que resuelve el problema
Solution resolver(vector<int> const& v, int i, int j) {

    //Caso base: un solo elemento, ya esta ordenado
    if (i == j) {
        return { true, v[i], v[i] };
    }

    //Buscamos mitad
    int mid = (i + j) / 2;

    //Contemplamos cada lado
    Solution izq = resolver(v, i, mid);
    Solution der = resolver(v, mid + 1, j);

    //La solucion es
    Solution res;
    //si valido a un lado y otro, y la izquierda es menor que la derecha
    res.ok = izq.ok && der.ok && (izq.maximo <= der.maximo) && (izq.minimo <= der.minimo);
    //El minimo está en alguna de las dos mitades
    res.minimo = std::min(izq.minimo, der.minimo);
    //El maximo está en alguna de las dos mitades
    res.maximo = std::max(izq.maximo, der.maximo);

    return res;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    //leer
    vector<int> v;
    int x;

    while (cin >> x && x != 0) {
        v.push_back(x);
    }

    //centinela
    if (v.empty()) return false;

    //resolver con busqueda binaria
    cout << (resolver(v, 0, v.size() - 1).ok ? "SI" : "NO") << "\n";

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
