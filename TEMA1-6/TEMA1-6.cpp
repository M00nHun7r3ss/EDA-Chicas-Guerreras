// Carmen Gómez Becerra
// EDA-GDV29
// Complejidad cuasi-lineal O(n.log n)
// Cuestion: si no estuvieran ordenados, el menor orden de complejidad seria cuadratica.
// Esto seria asi porque habria que comprobar todos los elementos de un vector con el otro, no como
// en este ejercicio que en cuanto se comprueba la condicion necesaria (ambos, tpv&&!eda, eda&&!tpv), se avanza y no se vuelve a mirar los
// elementos anteriores al que se esta comprobando ahora (variable aux que he usado en el ejercicio).

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// busqueda binaria
bool busquedaBinaria(int a[], int buscado) {


    int primero = 0;
    int ultimo = 100 - 1;
    bool encontrado = false;


    while (primero <= ultimo and !encontrado) {
        int medio = (primero + ultimo) / 2;
        if (a[medio] == buscado) {
            encontrado = true;
        }
        else if (buscado < a[medio]) {
            ultimo = medio - 1;
        }
        else {
            primero = medio + 1;
        }
    }


    return encontrado;
}

// A && !B:
vector<string> diferenciaVectores(vector<string> const A, vector<string> const B)
{
    vector<string> vec;
    int j;
    int aux = 0;
    for (int i = 0; i < A.size(); ++i) {
        bool ambos = false; // va viendo a ver si hay iguales, cuando los haya, para bucle.
        j = aux; // reinicia bucle.
        // si encuentra una que sea igual, avanza y no la guarda.
        // si llega al final y no hay ninguna igual, la guarda.
        while (j < B.size() && !ambos)
        {
            // si hay una igual se la salta 
            if (A[i] == B[j]) {
                ambos = true;
                aux++;
            }

            // si ha llegado al final sin que haya ninguna igual
            if ((j == B.size() - 1) && (A[i] != B[j])) {
                vec.push_back(A[i]);
            }

            j++;
        }
    }

    return vec;
}

// función que resuelve el problema
void comparaListados(vector<string> const& eda, vector<string> const& tpv,
    vector<string>& comunes, vector<string>& soloEda, vector<string>& soloTpv) {

    // AMBOS
    int j;
    int aux = 0;
    // comprueba todos los valores de la primera cadena
    for (int i = 0; i < eda.size(); ++i) {
        bool ambos = false;
        j = aux; // reinicia bucle.
        // cuando encuentra los que sean de ambos vectores para el bucle, aumenta aux y mete en el vector comunes
        while (j < tpv.size() && !ambos)
        {
            if (eda[i] == tpv[j])
            {
                ambos = true;
                comunes.push_back(eda[i]);
                aux++;
            }
            j++;
        }
    }

    // EDA && !TPV
    soloEda = diferenciaVectores(eda, tpv);

    // TPV && !EDA
    soloTpv = diferenciaVectores(tpv, eda);
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<string> eda(n);
    vector<string> comunes;
    vector<string> soloEda;
    vector<string> soloTpv;
    for (string& e : eda) cin >> e;
    cin >> n;
    vector<string> tpv(n);
    for (string& e : tpv) cin >> e;
    comparaListados(eda, tpv, comunes, soloEda, soloTpv);
    for (string& e : comunes) cout << e << " ";
    cout << endl;
    for (string& e : soloEda) cout << e << " ";
    cout << endl;
    for (string& e : soloTpv) cout << e << " ";
    cout << endl;
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
