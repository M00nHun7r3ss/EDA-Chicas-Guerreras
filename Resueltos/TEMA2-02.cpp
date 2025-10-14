// Carmen Gómez Becerra
// EDA - GDV29
// Complejidad lineal O(n): hay que recorrer cada cifra, a mas cifras mas tiempo de ejecucion, directamente proporcional.


#include <iostream>
#include <iomanip>
#include <fstream>

void bucleRecursivo(int& inv, int& n, int &rest)
{
	if (n > 0){
        // ej.: 1234
        inv = inv * 10 + (n % 10); // 4000 + 300 + 20 + 1
        n = n / 10; // 1234 -> 123
        rest = rest * 10 + 9; // el 999... que se le resta luego.
        bucleRecursivo(inv, n, rest);
    }
}
void resuelveCaso() {

    // lee el numero
    int n;
    std::cin >> n;

    // numeros
    int ordenado = n;
    int invertido = 0; // iremos montando
    int restador = 0; // lo que luego habra que restar para sacar el complementario

    if (n == 0) restador = 9;
    else{
        /* MODO ITERATIVO
        while (n > 0) { // ej.: 1234
            invertido = invertido * 10 + (n % 10); // 4000 + 300 + 20 + 1
            n = n / 10; // 1234 -> 123
            restador = restador * 10 + 9;
        }
		*/

        // MODO RECURSIVO
        bucleRecursivo(invertido, n, restador);
    }
    std::cout << restador - ordenado << " " << restador - invertido << std::endl;
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