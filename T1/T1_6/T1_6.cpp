// Denisa Juarranz Berindea
// EDA-GDV36

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/* CUESTION:
En caso de no tener dos listas ordenadas, no podriamos comparar los datos en paralelo,
porque no podriamos saber si coinciden. La forma mas rapida de resolverlo seria ordenarlos primero
y hacer la misma comprobacion que hemos hecho al dar por hecho que estaban ordenados.
Por tanto, si ordenados la complejidad es O(n+m), y para ordenar cada uno por separado la complejidad es O(n * log(n)) y O(m * log(m))
La minima complejidad seria la suma de ambas, con ordenacion, es decir O(n * log (n) + m * log (m))

En caso de no ordenarlos, en el peor de los casos habria que comprobar todos los elementos de uno con todos los del otro,
dando una complejidad O(n * m);
*/


/* COMPLEJIDAD:
Complejidad O(n+m), dado que hacemos una busqueda en la que todos los elementos de las dos listas
se recorren una unica vez, y el metodo vector.push_back(...) tiene complejidad O(1) y por tanto,
no modifica la del resto del algoritmo.
En el peor de los casos, la lista de comunes tendra todos los elementos de la lista mas corta,
y las otras dos, como maximo el numero inicial de elementos que ya tuviesen
*/

// función que resuelve el problema
void comparaListados(vector<string> const& eda, vector<string> const& tpv,
    vector<string>& comunes, vector<string>& soloEda, vector<string>& soloTpv) {

    //Recorreremos los vectores eda y tpv al mismo tiempo, para ir comparando
    //dado que, al estar ordenados
    int i = 0, j = 0;
    while (i < eda.size() && j < tpv.size())
    {
        //si en esa posicion tenemos el mismo elemento,
        //entrara en la lista de comunes
        if (eda[i] == tpv[j])
        {
            comunes.push_back(eda[i]);
            //Y avanzamos al siguiente elemento en ambas listas
            i++;
            j++;
        }
        //si en esa posicion el valor de eda es menor que el de tpv,
		//significa que ese valor no puede estar en tpv porque estara mas avanzado,
        //por lo tanto solo estara en eda (y solo avanzamos eda)
        else if (eda[i] < tpv[j])
        {
            soloEda.push_back(eda[i]);
            i++;
        }
        //ahora haremos lo mismo, pero con tpv en lugar de eda
        //si en esa posicion el valor de tpv es menor que el de eda,
        //significa que ese valor no puede estar en eda porque estara mas avanzado,
        //por lo tanto solo estara en tpv (y solo avanzamos tpv)
        else if (eda[i] > tpv[j])
        {
	        soloTpv.push_back(tpv[j]);
	        j++;
        }
    }

    //ahora bien, si despues de esto siguen quedando elementos
    //en cualquiera de las listas, que no han sido contemplados
    //se aniadiran a su lista correspondiente porque solo podran estar en esa
    //ya que una de las dos se habra terminado ya.
    //Recorreremos la otra hasta el final.

    //aniadimos los restantes de eda en soloEda (en caso de que tpv se haya gastado ya)
    while (i < eda.size())
    {
        soloEda.push_back(eda[i]);
        i++;
    }

    //aniadimos los restantes de tpv en soloTpv (en caso de que eda se haya gastado ya)
    while (j < tpv.size())
    {
        soloTpv.push_back(tpv[j]);
        j++;
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    // numero de datos eda
    int n;
    cin >> n;

    //vector alumnos matriculados en eda
    vector<string> eda(n);

    //vectores solucion
    vector<string> comunes;
    vector<string> soloEda;
    vector<string> soloTpv;

    //rellenamos eda
    for (string& e : eda) cin >> e;

    // numero de datos tpv
    cin >> n;

    //vector alumnos matriculados en tpv
    vector<string> tpv(n);

    //rellenamos tpv
    for (string& e : tpv) cin >> e;

    //ordenamos
    comparaListados(eda, tpv, comunes, soloEda, soloTpv);

    //solucion en los 3 vectores
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
