
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//Define solucion: solucion normal, invertida, y el indice de por donde vamos dandole la vuelta al asunto
struct Solution {
    long normal;
    long inverso;
    long pot10; 
};

Solution resolver(long n) {

    //Caso base, un solo digito
    if (n < 10) {
        int complementario = 9 - n;
        return { complementario, complementario, 10 };
    }

    //Recursividad, pero quitando digitos
    Solution sol = resolver(n / 10);

    //El resto y el complementario
    int digitoFinal = n % 10;
    int complementario = 9 - digitoFinal;

    //A lo que ya habia le sumamos el complementario que acabamos de sacar
    long normal = sol.normal * 10 + complementario;
    //Al complementario le sumamos lo que habia de antes
    long inverso = complementario * sol.pot10 + sol.inverso;
    //Otra mas para pasar a la siguiente cifra
    long pot10 = sol.pot10 * 10;

    return { normal, inverso, pot10 };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    //Leemos
    long n;
    cin >> n;

    //Resolvemos con recursividad
    Solution sol = resolver(n);

    //Escribimos solucion
    cout << sol.normal << " " << sol.inverso << endl;

    return true;
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