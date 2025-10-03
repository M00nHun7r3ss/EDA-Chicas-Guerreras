// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/* Complejidad:
Si se da uno de los casos especiales, en el que el incremento es 0, o solo ha trabajado un anio, la complejidad sera O(1), en cambio,
si hay que entrar en la busqueda binaria, nos encontraremos con una complejidad O(log n),
debido a la recursividad y a que se divide el vector a la mitad en cada iteracion
*/

//Nota para Miki: en el examen, este lo hice lineal y me comi la cabeza un buen rato, pero haciendolo ahora, me he dado cuenta de que
//tampoco es tan complicado hacerlo por busqueda binaria, y que me parece hasta mas intuitivo

int resolver(const vector<int>& salarios, int incremento, int ini, int fin)
{
    //En caso de que no haya elementos para analizar,
    //no se ha encontrado el incremento buscado
    if (ini > fin) return -1;

    //Calculamos la mitad para buscar en cada una de ellas
    int mitad = (ini + fin) / 2;

    //Miraremos el incremento en la mitad para ver donde toca buscar,
    //dado que el incremento es estrictamente creciente de un anio a otro.
    int auxIncrementoMitad = salarios[mitad] - salarios[mitad - 1];

    //Si resulta que el incremento justo se da en la mitad,
    //devolvemos esta
    if (auxIncrementoMitad == incremento)
    {
	    return mitad;
    }
    //Si el incremento en la mitad es menor que el incremento buscado,
    //buscamos en la segunda mitad (desde mitad + 1, porque ya hemos contemplado el caso de la mitad)
    else if (auxIncrementoMitad < incremento) 
    {
        return resolver(salarios, incremento, mitad + 1, fin);
    }
    //Si el incremento en la mitad es mayor que el incremento buscado,
    //buscamos en la primera mitad (hasta mitad - 1, porque ya hemos contemplado el caso de la mitad)
    else
    {
        return resolver(salarios, incremento, ini, mitad - 1);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada (los anios del contrato y el incremento buscado)
    int nAnios, inc;
    cin >> inc >> nAnios;

    // guardamos en un vector todos los salarios de los diferentes anios
    vector<int> salarios(nAnios);
    for (int& e : salarios) cin >> e;

    //definimos ini y fin
    int ini = 1; //porque el anio 0 no cuenta
    int fin = salarios.size() - 1;

    //creamos la solucion y analizamos unos cuantos casos antes de nada
    int solucion = 0;
    //Si el incremento buscado es 0, 
	//porque desde el primer anio (anio 0) se da por hecho un incremento ficticio 0
    if (inc == 0) solucion = 0;
    //Si solo ha trabajado un anio es -1, 
    //porque no puede haber un incremento
    else if (salarios.size() == 1) solucion = -1;
    //Si no es ninguno de estos casos, hacemos la busqueda binaria
    else solucion = resolver(salarios, inc, ini, fin);

    // Llamada a función y escritura de la salida
    cout << solucion << endl;
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
