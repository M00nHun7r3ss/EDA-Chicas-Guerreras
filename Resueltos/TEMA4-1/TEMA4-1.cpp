// Carmen Gómez Becerra
// EDA - GDV29

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Set.h"
using namespace std;

// Complejidad lineal. O(n) -> el tiempo de ejecucion es directamente proporcional al tamanio de la entrada.
// calcula la suma de cada digito al cuadrado del numero
int calculaCuadrado(int num) {
    // la suma empieza siendo cero.
    int suma = 0;

    // va sumando digito a digito mientras el numero no se reduzca al maximo
    while (num > 0) {
        int aux = num % 10; // extraemos el ultimo digito y lo metemos en aux. Ej.: de num = 49, aux = 9
        suma = suma + (aux * aux); // suma = suma + (ultimo digito)^2. Ej.: suma = suma + 9^2
        num = num / 10; // eliminamos ultimo digito al original. Ej.: de num = 49, num = 4
    }

    return suma;
}

// Complejidad lineal. O(n) -> el tiempo de ejecucion es directamente proporcional al tamanio de la entrada.
Set1<int> esFeliz(int num) {

    // El set que retornas.
    Set1<int> setR;
    setR.add(num);

    // inicialmente asumimos que no es feliz ni esta repetido.
    bool feliz = false; 
    bool repetido = false;

    // si el numero es 1, automaticamente es feliz y no entra en el bucle.
    if (num == 1) feliz = true;

    // va iterando hasta que sea feliz siempre y cuando no se repita ningun numero.
    while (!feliz && !repetido) {
        int suma = calculaCuadrado(num);

        // si suma vale 1 es que hemos llegado al final y el numero es FELIZ.
        if (suma == 1) feliz = true;

        // si ya esta repetido en la lista, el numero NO es FELIZ
        if (setR.contains(suma)) repetido = true;

        // aniadimos el valor a la cadena y actualizamos num.
        setR.add(suma);
        num = suma;
    }

    if (feliz) setR.add(1); // 1 -> FELIZ
    else setR.add(0);       // 0 -> NO FELIZ

    return setR;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;

    cin >> n;
    if (!cin) return false;

    cout <<  esFeliz(n) << endl;

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