// Carmen Gómez Becerra
// EDA - GDV29

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include <string>

#include "stack_eda.h"

// Complejidad O(n), n = line.size()
bool isBalanced(std::string line, std::stack<char> pila){
    int i = 0;
    bool balanced = true; // inicialmente asumimos como que los parentesis estan equilibrados.

    // mientras haya cadena y este equilibrado
	while (i < line.size() && balanced) {
        // cuando leamos uno de apertura lo aniadimos.
        if (line[i] == '(' || line[i] == '{' || line[i] == '[') {
            pila.push(line[i]); 
        }
        // cuando leamos uno de cierre lo analizamos.
        // ... si no esta vacio y la pila tiene el de apertura...
        else if (line[i] == ')') {
            if (!pila.empty() && pila.top() == '(') { pila.pop(); }
            else { balanced = false; }
        }
        else if (line[i] == '}') {
            if (!pila.empty() && pila.top() == '{') { pila.pop(); }
            else { balanced = false; }
        }
        else if (line[i] == ']') {
            if (!pila.empty() && pila.top() == '[') { pila.pop(); }
            else { balanced = false; }
        }
        i++;
    }

    // ademas de balanceado la pila tiene que estar vacia.
    return balanced && pila.empty();

    // cosas d stack: push O(1), top O(1), pop O(1), empty O(1).
    // bucle while O(n)
    // Conclusion: while(operaciones de O(1)) -> O(n) * O(1) = O(n).
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    std::string line;
    std::getline(std::cin, line);
    std::stack<char> pila;

    if (!std::cin)
        return false;

    if (isBalanced(line,pila)){ std::cout << "SI"; }
    else { std::cout << "NO"; }

    std::cout << std::endl;

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