// Carmen Gómez Becerra 
// EDA - GDV29
// Complejidad lineal O(n): hay que recorrer todo el vector, a mas elems tenga el vector mas tiempo de ejecucion

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


bool parcialmenteOrdenado(const std::vector<int>& v, int i, int m, int min, int max) {

    // si ha llegado al final, todo perfecto, esta PARCIALMENTE ORDENADO.
	if (i >= m){
        return true;
    } // se pone esto lo primero para que no se salga del vector y no de excepcion

    // si hay algun valor de la izquierda mayor que maxRight || si hay algun valor de la derecha menor que minLeft para y NO PARCIALMENTE ORDENADO.
    if (v[i] > max || v[i + m] < min){
        return false;
    }

    // si nada de esto, otra vuelta del bucle.
    parcialmenteOrdenado(v, i + 1, m, min, max);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int e;
    std::cin >> e;
    if (e == 0) return false;
    std::vector<int> sec;
    while (e != 0) {
        sec.push_back(e);
        std::cin >> e;
    }

    // Diremos que un vector esta parcialmente ordenado si:
    // el valor maximo de su mitad derecha >= que todos los valores de la mitad izquierda
    // &&
    // el valor minimo de su mitad izquierda <= que todos los valores de su mitad derecha

    // buscamos el valor maximo y minimo.
    int maxRight = sec[sec.size() - 1]; // mayor de la derecha (ponemos cualquiera de la derecha, y si resulta que hay alguno mayor que se cambie en el bucle)
    int minLeft = sec[0]; // menor de la izquierda.

    // punto medio (par)
    int m = sec.size() / 2;

    // recorre de i hasta la mitad y de la mitad hasta el final.
    for (int i = 0; i < m; ++i) {
        if (sec[i] < minLeft) minLeft = sec[i]; // encuentra el menor de la izquierda
        if (sec[i + m] > maxRight) maxRight = sec[i + m]; // encuentra el mayor de la derecha.
    }

    /*// si hay algun valor de la izquierda mayor que maxRight || si hay algun valor de la derecha menor que minLeft para y NO PARCIALMENTE ORDENADO.
    bool ordenado = true; // asumimos inicialmente k esta ordenado.
    int i = 0;
    while (ordenado && i < m) { // mientras este ordenado va avanzando ambas mitades.
        if (sec[i] > maxRight || sec[i + m] < minLeft) ordenado = false;
        i++;
    }*/

    std::cout << (parcialmenteOrdenado(sec, 0, m, minLeft, maxRight) ? "SI" : "NO") << std::endl;
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
    //system("PAUSE");
#endif

    return 0;
}