// Carmen Gómez Becerra 
// EDA - GDV29
// Complejidad

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


/*
// función que resuelve el problema
TipoSolucion resolver(TipoDatos datos) {


}
*/

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int n;
    std::cin >> n;

    // si lee cero de primeras se para.
    if (n == 0) return false;

    // almacenamos en el vector la secuencia hasta que lea 0.
    std::vector<int> v;
    while (n != 0){
        v.push_back(n); // almacenamos
        std::cin >> n; // leemos.
    }

    // Diremos que un vector esta parcialmente ordenado si:
    // el valor maximo de su mitad derecha >= que todos los valores de la mitad izquierda
    // &&
    // el valor minimo de su mitad izquierda <= que todos los valores de su mitad derecha

    // buscamos el valor maximo y minimo.
    int maxRight = v[v.size()-1]; // mayor de la derecha (ponemos cualquiera de la derecha, y si resulta que hay alguno mayor que se cambie en el bucle)
    int minLeft = v[0]; // menor de la izquierda.

    // todo punto medio y lo demas recursividad blablabla...

    // escribir sol

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